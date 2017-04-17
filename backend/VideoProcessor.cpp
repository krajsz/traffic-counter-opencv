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
#include "VideoProcessor.h"
#include "Utils.h"
#include "videosources/FileVideoSource.h"
#include "videosources/LiveIPCameraVideoSource.h"
#include "videosources/CameraVideoSource.h"

#include <QTimer>

#include <QDebug>

VideoProcessor::VideoProcessor(QObject *parent) : QThread(parent),
    m_processing(false),
    m_paused(false),
    m_readyForProcessing(false)
{

}

void VideoProcessor::run()
{
    process();

}

void VideoProcessor::initialize()
{
    if (dynamic_cast<FileVideoSource*>(m_source))
    {
        qDebug() << "file";
        m_videoReader.open(m_source->path().toStdString());
        if (m_videoReader.isOpened())
        {
            m_readyForProcessing = true;
        }
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
        m_videoReader.open(path.toStdString());

        if(m_videoReader.isOpened())
        {
            m_readyForProcessing = true;
        }
    }

    if (dynamic_cast<CameraVideoSource*>(m_source))
    {
        qDebug() << "webcam";
        CameraVideoSource* source = dynamic_cast<CameraVideoSource*>(m_source);
        int camIdx = source->infos().deviceName().toInt();
        m_videoReader.open(camIdx);
        if (m_videoReader.isOpened())
        {
            m_readyForProcessing = true;
        }
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

    //new thread needed for this
    /*while (m_processing)
    {
       // process();
    }*/
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

        QString lengthFormatted;

        int seconds  = milliseconds/ 1000;
        milliseconds %= 1000;
        int minutes  = seconds / 60;
        seconds  %= 60;
        int hours  = minutes/ 60;
        minutes  %= 60;

        lengthFormatted.append(QString("%1").arg(hours, 2, 10, QLatin1Char('0')) + ":" +
                               QString( "%1" ).arg(minutes, 2, 10, QLatin1Char('0')) + ":" +
                               QString( "%1" ).arg(seconds, 2, 10, QLatin1Char('0')) + ":" +
                               QString( "%1" ).arg(milliseconds, 3, 10, QLatin1Char('0')));

        infos.lenghtFormatted = lengthFormatted;

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


        cv::waitKey(30);
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
