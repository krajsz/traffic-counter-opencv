/***************************************************************************
    File                 : VideoSourceDock.h
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
#ifndef VIDEOSOURCEDOCK_H
#define VIDEOSOURCEDOCK_H

#include <QDockWidget>
#include "widgets/FileVideoSourceOptionsWidget.h"
#include "widgets/IPCameraVideoSourceOptionsWidget.h"
#include "ui_videosourcedock.h"
#include <QStackedWidget>

namespace Ui {
class VideoSourceDock;
}

class VideoSourceDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit VideoSourceDock(QWidget *parent = 0);
    ~VideoSourceDock();

private:
    Ui::VideoSourceDock *ui;

    FileVideoSourceOptionsWidget* m_fileVideoSourceOptionsWidget;
    IPCameraVideoSourceOptionsWidget* m_ipCameraVideoSourceOptionsWidget;

private Q_SLOTS:
    void sourceTypeChanged(bool checked);
};

#endif // VIDEOSOURCEDOCK_H
