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
#include <QDebug>

VideoProcessor::VideoProcessor(QObject *parent) : QObject(parent),
    m_processing(false),
    m_paused(false),
    m_readyForProcessing(false)
{

}

void VideoProcessor::start()
{
    m_processing = true;

    while (m_processing)
    {
        process();
    }
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

VideoProcessor::FileVideoInfo VideoProcessor::videoInfos(const QString& filename)
{
    FileVideoInfo infos;


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
    if (dynamic_cast<FileVideoSource*>(m_source))
    {
        qDebug() << "file";
    }

    if (dynamic_cast<LiveIPCameraVideoSource*>(m_source))
    {
        qDebug() << "ipcam";
    }

}

void VideoProcessor::pauseResume(bool pause)
{
    m_paused = pause;
}

void VideoProcessor::stop()
{
    m_processing = false;
}

void VideoProcessor::setSource(AbstractVideoSource *source)
{
    m_source = source;
}
