/***************************************************************************
    File                 : VideoProcessor.h
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
#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <QObject>
#include "backend/FrameProcessor.h"
#include "videosources/AbstractVideoSource.h"

class VideoProcessor : public QObject
{
    Q_OBJECT
public:
    explicit VideoProcessor(QObject *parent = 0);
    void start();
    void stop();

    void setSource(AbstractVideoSource* source);
    void process();

    bool isPaused() const;
    bool isProcessing() const;
    bool isReadyForProcessing() const;

    cv::VideoCapture reader() const;

    QImage currentFrameQImage() const;
    cv::Mat currentFrameMat() const;

    struct FileVideoInfo
    {
        double fps;
        int frameCount;
        QString lenghtFormatted;
        QSize frameSize;
    };

    static FileVideoInfo videoInfos(const QString& filename);

private:
    AbstractVideoSource* m_source;
    FrameProcessor* m_frameProcessor;
    cv::VideoCapture m_videoReader;
    cv::Mat m_currentFrame;

    bool m_processing;
    bool m_paused;
    bool m_readyForProcessing;

public Q_SLOTS:
    void pauseResume(bool pause);

signals:
    void progress(int value);
public slots:

};

#endif // VIDEOPROCESSOR_H
