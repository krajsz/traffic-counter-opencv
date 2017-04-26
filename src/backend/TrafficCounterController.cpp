/***************************************************************************
    File                 : TrafficCounterController.cpp
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
#include "src/backend/TrafficCounterController.h"
#include "src/backend/Utils.h"
#include "src/videosources/CameraVideoSource.h"

#include <QDateTime>
#include <QDebug>
#include <QImage>

TrafficCounterController::TrafficCounterController(QObject *parent) : QObject(parent),
    m_videoProcessor(new VideoProcessor),
    m_videoRecorder(new VideoRecorder)
{
}

TrafficCounterController::~TrafficCounterController()
{
    delete m_videoProcessor;
    delete m_videoRecorder;
}

void TrafficCounterController::setSource(AbstractVideoSource *source)
{
    m_videoProcessor->setSource(source);
    m_videoProcessor->initialize();
}

QImage TrafficCounterController::currentFrame() const
{
    return m_videoProcessor->currentFrameQImage();
}

QImage TrafficCounterController::foregroundFrame() const
{
    return m_videoProcessor->frameProcessor()->foregroundQImage();
}

VideoProcessor* TrafficCounterController::videoProcessor() const
{
    return m_videoProcessor;
}

void TrafficCounterController::startProcessing()
{
    m_videoProcessor->startProcessing();
}

void TrafficCounterController::pauseProcessing()
{
    m_videoProcessor->pauseResume(true);
}

void TrafficCounterController::resumeProcessing()
{
    m_videoProcessor->pauseResume(false);
}

void TrafficCounterController::stopProcessing()
{
    m_videoProcessor->stopProcessing();
}

void TrafficCounterController::startRecording()
{
    m_videoRecorder->startRecording();
    connect(m_videoProcessor, &VideoProcessor::frameReadyForProcessing, m_videoRecorder, &VideoRecorder::write);
}

void TrafficCounterController::stopRecording()
{
    m_videoRecorder->stopRecording();
    disconnect(m_videoProcessor, &VideoProcessor::frameReadyForProcessing, m_videoRecorder, &VideoRecorder::write);
}

void TrafficCounterController::saveScreenshot()
{
    QString fileName;
    if (dynamic_cast<CameraVideoSource*> (m_videoProcessor->source()))
    {
        fileName = QLatin1String("webcam_") + m_videoProcessor->source()->path() + QLatin1String("_") +
                QDateTime::currentDateTime().toString()+ QLatin1String(".jpg");
    }
    else
    {
        fileName = m_videoProcessor->source()->path()+ QLatin1String("_") +
                QDateTime::currentDateTime().toString()+ QLatin1String(".jpg");
    }

    m_videoProcessor->currentFrameQImage().save(fileName);
}
