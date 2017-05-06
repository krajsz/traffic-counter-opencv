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
#include "3rdparty/package_bgs/bgslibrary.h"
#include "src/backend/database/DatabaseManager.h"
#include <vector>
#include <QDateTime>

#include <QDebug>

FrameProcessor::FrameProcessor(QObject *parent) : QObject(parent),
    m_backgroundSubstractor(new FrameDifference),
    m_emitOriginal(false),
    m_vehicleCount(0),
    m_skipFrame(false),
    m_frames(0)
{
    m_backgroundSubstractor->setShowOutput(false);
}

void FrameProcessor::process(const cv::Mat &frame)
{
    frame.copyTo(m_currentFrame);

    cv::resize(m_currentFrame, m_currentFrame, cv::Size(640, 480));

    m_frames++;
    if (false)
    {
        m_skipFrame = false;
        return;
    }
    else
    {
        m_backgroundSubstractor->apply(m_currentFrame).copyTo(m_foreground);

        postProcess();
        m_skipFrame = true;
    }

#ifndef NOGUI

    if (m_emitOriginal)
    {
        emit frameProcessed(m_currentFrame);
    }
    else
    {
        emit frameProcessed(m_foreground);
    }
#endif

}

void FrameProcessor::setEmitOriginal(bool original)
{
    m_emitOriginal = original;

    if (original)
    {
        emit frameProcessed(m_currentFrame);
    }
    else
    {
        emit frameProcessed(m_foreground);
    }
}

bool FrameProcessor::emitOriginal() const
{
    return m_emitOriginal;
}

void FrameProcessor::postProcess()
{
    cv::Mat strel5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    cv::Mat strel15 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(25, 25));

    for (int i = 1; i < 5;++i)
    {
        cv::Mat strel5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(i+1, i+1));

        cv::morphologyEx(m_foreground, m_foreground, cv::MORPH_OPEN, strel5);
        cv::morphologyEx(m_foreground, m_foreground, cv::MORPH_CLOSE, strel5);

    }
    cv::blur(m_foreground, m_foreground, cv::Size(5, 5));

    cv::erode(m_foreground, m_foreground,strel5);

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

        bool okAsNewBlob  = vblob.boundingRect().area() > 2000 &&
                vblob.boundingRect().area() < 7000 &&
                (cv::contourArea(convHull) / (double)vblob.boundingRect().area()) > 0.2 &&
                vblob.aspectRatio() > 0.2 &&
                vblob.aspectRatio() < 2 &&
                vblob.diagonalSize() > 60;

        if (okAsNewBlob)
        {
           // qDebug() << "new blob ";

            currentBlobs.push_back(vblob);
        }
    }

    if (m_frames < 5)
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
            double leastDistance = 100000;

            for (int i = 0; i < m_blobs.size(); ++i)
            {
                if (m_blobs[i].isTracked())
                {
                    double distance = Utils::distance(cblob.previousCenterPositions().back(),
                                                      m_blobs[i].nextPosition());

                    if (distance < leastDistance)
                    {
                        leastDistance = distance;
                        idxOfClosestBlob = i;
                 //       qDebug() << "closest dist: " << leastDistance;
                    }
                }
            }

            if (leastDistance < cblob.diagonalSize() * 1.5)
            {
             //   qDebug() << "updating existing blob: " << idxOfClosestBlob;
                m_blobs[idxOfClosestBlob].setContour(cblob.contour());
                m_blobs[idxOfClosestBlob].setBoundingRect(cblob.boundingRect());
                m_blobs[idxOfClosestBlob].setAspectRatio(cblob.aspectRatio());
                m_blobs[idxOfClosestBlob].setDiagonalSize(cblob.diagonalSize());
                m_blobs[idxOfClosestBlob].addPreviousPosition(cblob.previousCenterPositions().back());

                m_blobs[idxOfClosestBlob].setTracked(true);
                m_blobs[idxOfClosestBlob].setNew(true);
            }
            else
            {
            //    qDebug() << "too far, new blob";

                cblob.setNew(true);
                m_blobs.push_back(cblob);
            }
        }
        std::vector<std::vector<cv::Point> > contoursToBeDrawn;

        for (VehicleBlob &blob : m_blobs)
        {

            if (blob.newOrExisting() == false)
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

       /* for (int i = 0; i < m_blobs.size(); ++i)
        {
            if (!m_blobs.at(i).isTracked())
            {
                m_blobs.removeAt(i);
            }
        }*/

        const int hLineHeight = m_currentFrame.rows * 0.3;

        bool atLeastOneBlobCrossed = false;

        for (VehicleBlob& blob : m_blobs)
        {
            if (blob.isTracked() && blob.previousCenterPositions().size() >= 2
                  &&  blob.counted())
            {
                int prevFrameIndex = (int)blob.previousCenterPositions().size() - 2;
                int currFrameIndex = (int)blob.previousCenterPositions().size() - 1;

                if ((blob.previousCenterPositions()[prevFrameIndex].y > hLineHeight &&
                        blob.previousCenterPositions()[currFrameIndex].y <= hLineHeight) ||
                        (blob.previousCenterPositions()[prevFrameIndex].y < hLineHeight &&
                         blob.previousCenterPositions()[currFrameIndex].y >= hLineHeight))
                {
                    //db

                    m_vehicleCount++;
                    qDebug () << "Vehicle count: " << m_vehicleCount;

                  /*  DatabaseManager* dbmgr = DatabaseManager::instance();
                    dbmgr->newObservation(m_vehicleCount, QDateTime::currentDateTime());
*/
                    blob.setCounted(true);
                    atLeastOneBlobCrossed = true;
                }
            }
        }

        cv::Point lp1 (0, hLineHeight);
        cv::Point lp2 (m_currentFrame.cols -1, hLineHeight);

        if (atLeastOneBlobCrossed)
        {
            cv::line(m_currentFrame, lp1, lp2, cv::Scalar(0,255,0), 2);
        }
        else
        {
            cv::line(m_currentFrame, lp1, lp2, cv::Scalar(255,0,0), 2);
        }

      //  qDebug () << "m_blobs size: " << m_blobs.size();


        /*qDebug() << "contoursToBeDrawn: " << contoursToBeDrawn.size();
        qDebug() << "m_blobs size: " << m_blobs.size();*/


#ifndef NOGUI
        const cv::Scalar red = cv::Scalar(0.0, 0.0, 255.0);
        cv::drawContours(m_currentFrame, contoursToBeDrawn, -1 , red);

        cv::putText(m_currentFrame, QString::number(m_vehicleCount).toStdString(), cv::Point(40, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0,255,0), 2);
#endif
        m_firstFrame = false;
    }
}

void FrameProcessor::resetVehicleCount()
{
    m_vehicleCount = 0;
}

void FrameProcessor::originalFrameRequested()
{
    emit frameProcessed(m_currentFrame);
}

void FrameProcessor::foregroundFrameRequested()
{
    emit frameProcessed(m_foreground);
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
