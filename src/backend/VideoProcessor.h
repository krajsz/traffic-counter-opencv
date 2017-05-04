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

#include <QThread>

#include "src/backend/FrameProcessor.h"
#include "src/videosources/FileVideoSource.h"

class QTimer;

class VideoProcessor : public QThread
{
    Q_OBJECT
public:
    explicit VideoProcessor(QObject *parent = 0);
    void startProcessing();
    void stopProcessing();

    void setSource(AbstractVideoSource* source);
    void process();

    AbstractVideoSource* source() const;
    FrameProcessor* frameProcessor() const;

    void initialize();

    bool isPaused() const;
    bool isProcessing() const;
    bool isReadyForProcessing() const;

    cv::VideoCapture reader() const;

    QImage currentFrameQImage() const;
    cv::Mat currentFrameMat() const;

    static FileVideoSource::VideoInfo videoInfos(const QString& filename);

private:
    AbstractVideoSource* m_source;
    FrameProcessor* m_frameProcessor;

    bool m_emitOriginal;

    cv::VideoCapture m_videoReader;
    cv::Mat m_currentFrame;

    bool m_processing;
    bool m_paused;
    bool m_readyForProcessing;

protected:
    void run() override;
    static void msleep(unsigned long msecs);

public Q_SLOTS:
    void pauseResume(bool pause);

Q_SIGNALS:
    void progress(int value);
    void frameReadyForProcessing(const cv::Mat& frame);
    void currentProgressInTime(const QString& time);
    void stopRecordRequested();
public slots:

};

#endif // VIDEOPROCESSOR_H
