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
#include "TrafficCounterController.h"

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
}

void TrafficCounterController::stopRecording()
{
    m_videoRecorder->stopRecording();
}

void TrafficCounterController::saveScreenshot()
{

}
