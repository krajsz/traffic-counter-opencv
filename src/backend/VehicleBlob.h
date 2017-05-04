/***************************************************************************
    File                 : VehicleBlob.h
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
#ifndef VEHICLEBLOB_H
#define VEHICLEBLOB_H

#include <opencv2/features2d.hpp>
#include <QVector>

class VehicleBlob
{
public:
    VehicleBlob() = default;

    VehicleBlob(const std::vector<cv::Point>& blobContour);

    void update();

    int framesWithoutMatching() const;

    double diagonalSize() const;
    double aspectRatio() const;

    bool newOrExisting() const;
    bool isTracked() const;
    bool counted() const;

    cv::Rect boundingRect() const;
    QVector<cv::Point> previousCenterPositions() const;
    std::vector<cv::Point> contour() const;
    cv::Point nextPosition() const;

    void frameWithoutMatching();

    void addPreviousPosition(const cv::Point& position);

    void setNew(const bool neww);
    void setCounted(const bool counted);
    void setTracked(const bool tracked);
    void setContour(const std::vector<cv::Point>& newContour);
    void setBoundingRect(const cv::Rect& newRect);
    void setAspectRatio(const int aspratio);
    void setDiagonalSize(const int diagonalSize);

private:
    void calculateNextPosition();

    std::vector<cv::Point> m_contour;
    QVector<cv::Point> m_previousCenterPositions;

    cv::Point m_nextPosition;

    bool m_tracked;
    bool m_newOrExisting;
    bool m_counted;

    int m_framesWithoutMatch;

    double m_diagonalSize;
    double m_aspectRatio;

    cv::Rect m_boundingRect;
};

#endif // VEHICLEBLOB_H
