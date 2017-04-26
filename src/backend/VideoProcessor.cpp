/***************************************************************************
    File                 : VideoProcessor.cpp
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
#include "src/backend/VideoProcessor.h"
#include "src/backend/Utils.h"
#include "src/videosources/FileVideoSource.h"
#include "src/videosources/LiveIPCameraVideoSource.h"
#include "src/videosources/CameraVideoSource.h"

#include <QTimer>

#include <QDebug>

VideoProcessor::VideoProcessor(QObject *parent) : QThread(parent),
    m_processing(false),
    m_paused(false),
    m_readyForProcessing(false),
    m_frameProcessor(new FrameProcessor)
{
    connect(this, &VideoProcessor::frameReadyForProcessing, m_frameProcessor, &FrameProcessor::process);
}

void VideoProcessor::run()
{
    while (m_processing)
    {
        process();
    }
}

void VideoProcessor::msleep(unsigned long msleep)
{
    QThread::msleep(msleep);
}

void VideoProcessor::initialize()
{
    if (dynamic_cast<FileVideoSource*>(m_source))
    {
        qDebug() << "file";
        m_videoReader.open(m_source->path().toStdString());
    }

    if (dynamic_cast<LiveIPCameraVideoSource*>(m_source))
    {
        qDebug() << "ipcam";
        LiveIPCameraVideoSource* ipCamSource = dynamic_cast<LiveIPCameraVideoSource*>(m_source);
        QString path;

        if (ipCamSource->pathContainsInfos())
        {
            path = ipCamSource->path();
        }
        else
        {
            //path = ipCamSource->infos().
        }
        qDebug() << path;

        m_videoReader.open(path.toStdString());
    }

    if (dynamic_cast<CameraVideoSource*>(m_source))
    {
        qDebug() << "webcam";
        CameraVideoSource* source = dynamic_cast<CameraVideoSource*>(m_source);
        int camIdx = source->path().toInt();
        m_videoReader.open(camIdx);
    }

    if(m_videoReader.isOpened())
    {
        m_readyForProcessing = true;
    }
    else
    {
        qDebug() << "Not opened";
    }
}

void VideoProcessor::startProcessing()
{

    if (dynamic_cast<FileVideoSource*>(m_source))
    {
        qDebug() << "file";
    }

    if (dynamic_cast<LiveIPCameraVideoSource*>(m_source))
    {
        qDebug() << "ipcam";
    }

    m_processing = true;

    //start the thread
    start();
}

cv::VideoCapture VideoProcessor::reader() const
{
    return m_videoReader;
}

QImage VideoProcessor::currentFrameQImage() const
{
    return Utils::Mat2QImage(m_currentFrame);
}

cv::Mat VideoProcessor::currentFrameMat() const
{
    return m_currentFrame;
}

FileVideoSource::VideoInfo VideoProcessor::videoInfos(const QString& filename)
{
    FileVideoSource::VideoInfo infos;

    cv::VideoCapture cap;

    cap.open(filename.toStdString());

    if (cap.isOpened())
    {
        cap.set(CV_CAP_PROP_POS_AVI_RATIO,1);

        int milliseconds = cap.get(CV_CAP_PROP_POS_MSEC);

        infos.lenghtFormatted = Utils::videoLengthFormatted(milliseconds);

        infos.fps = cap.get(CV_CAP_PROP_FPS);
        infos.frameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);
        infos.frameSize.setHeight(cap.get(CV_CAP_PROP_FRAME_HEIGHT));
        infos.frameSize.setWidth(cap.get(CV_CAP_PROP_FRAME_WIDTH));

        cap.set(CV_CAP_PROP_POS_FRAMES,1);
        cap.release();
    }

    return infos;
}

bool VideoProcessor::isPaused() const
{
    return m_paused;
}

bool VideoProcessor::isProcessing() const
{
    return m_processing;
}

bool VideoProcessor::isReadyForProcessing() const
{
    return m_readyForProcessing;
}

void VideoProcessor::process()
{
    if (!m_paused)
    {
        // read

        m_videoReader.read(m_currentFrame);

        if (!m_currentFrame.empty())
        {
            emit frameReadyForProcessing(m_currentFrame);
        }
        if (dynamic_cast<FileVideoSource*>(m_source))
        {
            FileVideoSource* source = dynamic_cast<FileVideoSource*>(m_source);
            int ms = static_cast<int>(1000 / source->infos().fps);
            int progressValue = (1000 * m_videoReader.get(CV_CAP_PROP_POS_FRAMES)) / source->infos().frameCount;

            emit progress(progressValue);
            QString currentTime = Utils::videoLengthFormatted(m_videoReader.get(CV_CAP_PROP_POS_MSEC));

            emit currentProgressInTime(currentTime);
            msleep(ms);
        }
        if (dynamic_cast<CameraVideoSource*>(m_source))
        {

        }
    }
}

void VideoProcessor::pauseResume(bool pause)
{
    m_paused = pause;
}

void VideoProcessor::stopProcessing()
{
    m_processing = false;

    if (wait(2000))
    {
        terminate();
        wait();
    }
}

void VideoProcessor::setSource(AbstractVideoSource *source)
{
    m_source = source;
}

FrameProcessor* VideoProcessor::frameProcessor() const
{
    return m_frameProcessor;
}

AbstractVideoSource* VideoProcessor::source() const
{
    return m_source;
}
