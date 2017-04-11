/***************************************************************************
    File                 : VideoSourceDock.cpp
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
#include "VideoSourceDock.h"

VideoSourceDock::VideoSourceDock(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VideoSourceDock)
{
    ui->setupUi(this);

    QWidget* fileSourceWidget = new QWidget;
    m_fileVideoSourceOptions.setupUi(fileSourceWidget);

    ui->sourceOptionsStackedWidget->insertWidget(0, fileSourceWidget);

    QWidget* ipCameraSourceWidget = new QWidget;
    m_ipCameraVideoSourceOptions.setupUi(ipCameraSourceWidget);

    ui->sourceOptionsStackedWidget->insertWidget(1, ipCameraSourceWidget);

    ui->sourceOptionsStackedWidget->setCurrentIndex(0);
    connect(ui->fileSourceRadioButton, &QRadioButton::toggled, this, &VideoSourceDock::sourceTypeChanged);
}

VideoSourceDock::~VideoSourceDock()
{
    delete ui;
}

void VideoSourceDock::sourceTypeChanged(bool checked)
{
    if (checked)
    {
        ui->sourceOptionsStackedWidget->setCurrentIndex(0);
    }
    else
    {
        ui->sourceOptionsStackedWidget->setCurrentIndex(1);
    }
}
