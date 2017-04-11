/***************************************************************************
    File                 : TrafficCounterController.h
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
#ifndef TRAFFICCOUNTERCONTROLLER_H
#define TRAFFICCOUNTERCONTROLLER_H

#include "backend/VideoProcessor.h"
#include "backend/VideoRecorder.h"
#include "backend/database/DatabaseManager.h"
#include <QObject>

class TrafficCounterController : public QObject
{
    Q_OBJECT
public:
    explicit TrafficCounterController(QObject *parent = 0);

private:

    DatabaseManager* m_databaseManager;
    VideoProcessor* m_videoProcessor;
    VideoRecorder* m_videoRecorder;

signals:

public slots:
    void startProcessing();
    void pauseProcessing();
    void resumeProcessing();
    void stopProcessing();

    void startRecording();
    void stopRecording();
};

#endif // TRAFFICCOUNTERCONTROLLER_H
