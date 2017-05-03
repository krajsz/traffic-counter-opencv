/***************************************************************************
    File                 : FrameProcessor.cpp
    Project              : TrafficCounter
    Description          :
    --------------------------------------------------------------------
    Copyright            : (C) 2017 Fábián Kristóf - Szabolcs (fkristofszabolcs@gmail.com)
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/
#include "src/backend/FrameProcessor.h"
#include "src/backend/Utils.h"

#include "3rdparty/package_bgs/FrameDifference.h"
#include "3rdparty/package_bgs/AdaptiveBackgroundLearning.h"
#include "3rdparty/package_bgs/StaticFrameDifference.h"
#include "3rdparty/package_bgs/PBAS/PBAS.h"
#include "3rdparty/package_bgs/AdaptiveSelectiveBackgroundLearning.h"
#include <vector>

#include <QDebug>

FrameProcessor::FrameProcessor(QObject *parent) : QObject(parent),
    m_backgroundSubstractor(new AdaptiveSelectiveBackgroundLearning),
    m_emitOriginal(false)
{
    m_backgroundSubstractor->setShowOutput(false);
}

void FrameProcessor::process(const cv::Mat &frame)
{
    frame.copyTo(m_currentFrame);

    cv::resize(m_currentFrame, m_currentFrame, cv::Size(640, 480));

    cv::Mat fr;

    m_backgroundSubstractor->apply(m_currentFrame).copyTo(m_foreground);

    //m_backgroundSubstractor->process(frame, m_foreground, m_background);
    //fr.copyTo(m_foreground);
    cv::resize(m_foreground, m_foreground, cv::Size(640, 480));

    postProcess();

    if (m_emitOriginal)
    {
        emit frameProcessed(m_currentFrame);
    }
    else
    {
        emit frameProcessed(m_foreground);
    }
}

void FrameProcessor::setEmitOriginal(bool original)
{
    m_emitOriginal = original;
}

bool FrameProcessor::emitOriginal() const
{
    return m_emitOriginal;
}

void FrameProcessor::postProcess()
{
    cv::Mat strel5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));

    cv::GaussianBlur(m_foreground, m_foreground, cv::Size(5, 5), 0);
    cv::threshold(m_foreground, m_foreground, 30, 255.0, CV_THRESH_BINARY);
    for (int i = 0; i < 2; i++)
    {
        cv::dilate(m_foreground, m_foreground, strel5);
        cv::dilate(m_foreground, m_foreground, strel5);
        cv::erode(m_foreground, m_foreground, strel5);
    }
    std::vector<std::vector<cv::Point> > contours;

    cv::findContours(m_foreground, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> convexHulls(contours.size());

    for (int i = 0; i < contours.size(); ++i)
    {
        cv::convexHull(contours[i], convexHulls[i]);
    }

    std::vector<VehicleBlob> currentBlobs;

    for(const auto& convHull : convexHulls)
    {
        VehicleBlob vblob (convHull);

        bool okAsNewBlob  = vblob.boundingRect().area() > 1000 &&
                vblob.boundingRect().area() < 15000 &&
                (cv::contourArea(convHull) / (double)vblob.boundingRect().area()) > 0.5 &&
                vblob.aspectRatio() > 0.2 &&
                vblob.aspectRatio() < 2 &&
                vblob.diagonalSize() > 60;

        if (okAsNewBlob)
        {
            currentBlobs.push_back(vblob);
        }
    }

    if (m_firstFrame)
    {
        for(const VehicleBlob& blob : currentBlobs)
        {
            m_blobs.push_back(blob);
        }
    }
    else
    {
        for(VehicleBlob& blob : m_blobs)
        {
            blob.update();
        }
        for (VehicleBlob &cblob : currentBlobs) {

            int idxOfClosestBlob = 0;
            double leastDistance = std::numeric_limits<double>::max();

            for (int i = 0; i < m_blobs.size(); i++)
            {
                if (m_blobs[i].isTracked() == true)
                {
                    double distance = Utils::distance(cblob.previousCenterPositions().back(),
                                                      m_blobs[i].nextPosition());

                    if (distance < leastDistance)
                    {
                        leastDistance = distance;
                        idxOfClosestBlob = i;
                    }
                }
            }

            if (leastDistance < cblob.diagonalSize() * 0.5)
            {
                m_blobs[idxOfClosestBlob].setContour(cblob.contour());
                m_blobs[idxOfClosestBlob].setBoundingRect(cblob.boundingRect());
                m_blobs[idxOfClosestBlob].setAspectRatio(cblob.aspectRatio());
                m_blobs[idxOfClosestBlob].setDiagonalSize(cblob.diagonalSize());
                m_blobs[idxOfClosestBlob].addPreviousPosition(cblob.previousCenterPositions().back());

                m_blobs[idxOfClosestBlob].setTracked(true);
                m_blobs[idxOfClosestBlob].setNew(false);
            }
            else
            {
                cblob.setNew(true);
                m_blobs.push_back(cblob);
            }
        }
        std::vector<std::vector<cv::Point> > contoursToBeDrawn;

        for (VehicleBlob &blob : m_blobs)
        {

            if (blob.newOrExisting() == false) // ???
            {
                blob.frameWithoutMatching();
            }

            if (blob.framesWithoutMatching() >= 10)
            {
                blob.setTracked(false);
            }

            if (blob.isTracked())
            {
                contoursToBeDrawn.push_back(blob.contour());
            }
        }

        /*if (m_blobs.size() > 300)
        {
            m_blobs.clear();
        }*/

        /*qDebug() << "contoursToBeDrawn: " << contoursToBeDrawn.size();
        qDebug() << "m_blobs size: " << m_blobs.size();*/

        const cv::Scalar red = cv::Scalar(0.0, 0.0, 255.0);
        cv::drawContours(m_currentFrame, contoursToBeDrawn, -1 , red);

        m_firstFrame = false;
    }
}

cv::Mat FrameProcessor::backgroundMat() const
{
    return m_background;
}

QImage FrameProcessor::foregroundQImage() const
{
    return Utils::Mat2QImage(m_foreground);
}

cv::Mat FrameProcessor::foregroundMat() const
{
    return m_foreground;
}
