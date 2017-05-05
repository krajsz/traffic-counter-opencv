/***************************************************************************
    File                 : FrameProcessor.h
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
#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include "src/backend/VehicleBlob.h"
#include "3rdparty/package_bgs/bgslibrary.h"

class FrameProcessor : public QObject
{
    Q_OBJECT
public:
    explicit FrameProcessor(QObject *parent = 0);
    cv::Mat backgroundMat() const;
    cv::Mat foregroundMat() const;

    QImage foregroundQImage() const;

    void originalFrameRequested();
    void foregroundFrameRequested();

    bool emitOriginal() const;
    void setEmitOriginal(bool original);

Q_SIGNALS:
    void frameProcessed(const cv::Mat& frame);
    void newCar();
public Q_SLOTS:
    void process(const cv::Mat& frame);

private:
    IBGS* m_backgroundSubstractor;
    cv::Mat m_background;
    cv::Mat m_foreground;


    bool m_skipFrame;
    int m_vehicleCount;

    int m_frames;
    cv::Mat m_currentFrame;
    QVector<VehicleBlob> m_blobs;

    bool m_emitOriginal;
    bool m_firstFrame;

    void postProcess();
};

#endif // FRAMEPROCESSOR_H
