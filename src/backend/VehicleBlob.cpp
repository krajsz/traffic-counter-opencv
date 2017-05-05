/***************************************************************************
    File                 : VehicleBlob.cpp
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
#include "src/backend/VehicleBlob.h"
#include <vector>
#include <opencv2/opencv.hpp>

#include <QDebug>
VehicleBlob::VehicleBlob(const std::vector<cv::Point> &blobContour) : m_contour (blobContour),
    m_tracked(true),
    m_newOrExisting(true),
    m_framesWithoutMatch(0)
{
    m_boundingRect = cv::boundingRect(m_contour);

    cv::Point actualCenterPosition;

    actualCenterPosition.x = (m_boundingRect.x + m_boundingRect.x + m_boundingRect.width) / 2;
    actualCenterPosition.y = (m_boundingRect.y + m_boundingRect.y + m_boundingRect.height) / 2;
    m_previousCenterPositions.push_back(actualCenterPosition);

    m_diagonalSize = std::sqrt(std::pow(m_boundingRect.width, 2) + std::pow(m_boundingRect.height, 2));
    m_aspectRatio = static_cast<float>(m_boundingRect.width) / static_cast<float>(m_boundingRect.height);
}

void VehicleBlob::calculateNextPosition()
{
    int previousCenterPositionsCount = m_previousCenterPositions.size();

    if (previousCenterPositionsCount == 1)
    {
        m_nextPosition = cv::Point(m_previousCenterPositions.back().x,
                                   m_previousCenterPositions.back().y);
    }
    else if (previousCenterPositionsCount == 2)
    {

        int deltaX = m_previousCenterPositions[1].x - m_previousCenterPositions[0].x;
        int deltaY = m_previousCenterPositions[1].y - m_previousCenterPositions[0].y;

        m_nextPosition = cv::Point(m_previousCenterPositions.back().x + deltaX,
                                   m_previousCenterPositions.back().y + deltaY);
    }
    else if (previousCenterPositionsCount == 3)
    {

        int sumOfXChanges = ((m_previousCenterPositions[2].x - m_previousCenterPositions[1].x) * 2) +
                ((m_previousCenterPositions[1].x - m_previousCenterPositions[0].x) * 1);

        int deltaX = std::round(static_cast<float>(sumOfXChanges) / 3.0);

        int sumOfYChanges = ((m_previousCenterPositions[2].y - m_previousCenterPositions[1].y) * 2) +
                ((m_previousCenterPositions[1].y - m_previousCenterPositions[0].y) * 1);

        int deltaY = std::round(static_cast<float>(sumOfYChanges) / 3.0);

        m_nextPosition = cv::Point(m_previousCenterPositions.back().x + deltaX,
                                   m_previousCenterPositions.back().y + deltaY);
    }
    else if (previousCenterPositionsCount == 4)
    {

        int sumOfXChanges = ((m_previousCenterPositions[3].x - m_previousCenterPositions[2].x) * 3) +
                ((m_previousCenterPositions[2].x - m_previousCenterPositions[1].x) * 2) +
                ((m_previousCenterPositions[1].x - m_previousCenterPositions[0].x) * 1);

        int deltaX = std::round(static_cast<float>(sumOfXChanges) / 6.0);

        int sumOfYChanges = ((m_previousCenterPositions[3].y - m_previousCenterPositions[2].y) * 3) +
                ((m_previousCenterPositions[2].y - m_previousCenterPositions[1].y) * 2) +
                ((m_previousCenterPositions[1].y - m_previousCenterPositions[0].y) * 1);

        int deltaY = std::round(static_cast<float>(sumOfYChanges) / 6.0);
        m_nextPosition = cv::Point(m_previousCenterPositions.back().x + deltaX,
                                   m_previousCenterPositions.back().y + deltaY);

    }
    else if (previousCenterPositionsCount >= 5)
    {

        int sumOfXChanges = ((m_previousCenterPositions[previousCenterPositionsCount - 1].x - m_previousCenterPositions[previousCenterPositionsCount - 2].x) * 4) +
                ((m_previousCenterPositions[previousCenterPositionsCount - 2].x - m_previousCenterPositions[previousCenterPositionsCount - 3].x) * 3) +
                ((m_previousCenterPositions[previousCenterPositionsCount - 3].x - m_previousCenterPositions[previousCenterPositionsCount - 4].x) * 2) +
                ((m_previousCenterPositions[previousCenterPositionsCount - 4].x - m_previousCenterPositions[previousCenterPositionsCount - 5].x) * 1);

        int deltaX = std::round(static_cast<float>(sumOfXChanges) / 10.0);

        int sumOfYChanges = ((m_previousCenterPositions[previousCenterPositionsCount - 1].y - m_previousCenterPositions[previousCenterPositionsCount - 2].y) * 4) +
                ((m_previousCenterPositions[previousCenterPositionsCount - 2].y - m_previousCenterPositions[previousCenterPositionsCount - 3].y) * 3) +
                ((m_previousCenterPositions[previousCenterPositionsCount - 3].y - m_previousCenterPositions[previousCenterPositionsCount - 4].y) * 2) +
                ((m_previousCenterPositions[previousCenterPositionsCount - 4].y - m_previousCenterPositions[previousCenterPositionsCount - 5].y) * 1);

        int deltaY = std::round(static_cast<float>(sumOfYChanges) / 10.0);

        m_nextPosition = cv::Point(m_previousCenterPositions.back().x + deltaX,
                                   m_previousCenterPositions.back().y + deltaY);


        /*qDebug() << "Previous pos: " << m_previousCenterPositions.last().x << " "
                 << m_previousCenterPositions.last().y << " "
                 << " next: " << m_nextPosition.x << " " << m_nextPosition.y;
       /* while (m_previousCenterPositions.size() >= 5)
        {
            m_previousCenterPositions.removeFirst();
        }*/
    }

   // qDebug() << "Previous positions: " << m_previousCenterPositions.size();
}

QVector<cv::Point> VehicleBlob::previousCenterPositions() const
{
    return m_previousCenterPositions;
}

std::vector<cv::Point> VehicleBlob::contour() const
{
    return m_contour;
}

cv::Point VehicleBlob::nextPosition() const
{
    return m_nextPosition;
}

void VehicleBlob::update()
{
    m_newOrExisting = false; // existing
    calculateNextPosition();
}

cv::Rect VehicleBlob::boundingRect() const
{
    return m_boundingRect;
}

bool VehicleBlob::isTracked() const
{
    return m_tracked;
}

bool VehicleBlob::newOrExisting() const
{
    return m_newOrExisting;
}

void VehicleBlob::setNew(const bool neww)
{
    m_newOrExisting = neww;
}

bool VehicleBlob::counted() const
{
    return m_counted;
}

void VehicleBlob::setCounted(const bool counted)
{
    m_counted = counted;
}

void VehicleBlob::setContour(const std::vector<cv::Point> &newContour)
{
    m_contour = newContour;
}

void VehicleBlob::setTracked(const bool tracked)
{
    m_tracked = tracked;
}

int VehicleBlob::framesWithoutMatching() const
{
    return m_framesWithoutMatch;
}

double VehicleBlob::diagonalSize() const
{
    return m_diagonalSize;
}

double VehicleBlob::aspectRatio() const
{
    return m_aspectRatio;
}

void VehicleBlob::frameWithoutMatching()
{
    m_framesWithoutMatch++;
}

void VehicleBlob::addPreviousPosition(const cv::Point &position)
{
    m_previousCenterPositions.push_back(position);
}

void VehicleBlob::setBoundingRect(const cv::Rect &newRect)
{
    m_boundingRect = newRect;
}

void VehicleBlob::setDiagonalSize(const int diagonalSize)
{
    m_diagonalSize = diagonalSize;
}

void VehicleBlob::setAspectRatio(const int aspratio)
{
    m_aspectRatio = aspratio;
}
