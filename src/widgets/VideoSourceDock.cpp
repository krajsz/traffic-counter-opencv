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
#include "src/widgets/VideoSourceDock.h"
#include <QGroupBox>
#include <QDebug>

VideoSourceDock::VideoSourceDock(QWidget *parent) :
    QDockWidget(parent),
    m_fileVideoSourceOptionsWidget(new FileVideoSourceOptionsWidget),
    m_ipCameraVideoSourceOptionsWidget(new IPCameraVideoSourceOptionsWidget),
    m_cameraVideoSourceOptionsWidget(new CameraVideoSourceOptionsWidget),
    ui(new Ui::VideoSourceDock)
{
    ui->setupUi(this);

    ui->sourceOptionsStackedWidget->insertWidget(0, m_fileVideoSourceOptionsWidget);
    ui->sourceOptionsStackedWidget->insertWidget(1, m_ipCameraVideoSourceOptionsWidget);
    ui->sourceOptionsStackedWidget->insertWidget(2, m_cameraVideoSourceOptionsWidget);

    ui->sourceOptionsStackedWidget->setCurrentIndex(0);

    connect(ui->ipCameraSourceRadioButton, &QRadioButton::toggled, this, &VideoSourceDock::sourceTypeChanged);
    connect(ui->webcamSourceRadioButton, &QRadioButton::toggled, this, &VideoSourceDock::sourceTypeChanged);
    connect(ui->fileSourceRadioButton, &QRadioButton::toggled, this, &VideoSourceDock::sourceTypeChanged);

    connect(ui->sourceOptionsStackedWidget, &QStackedWidget::currentChanged, this, &VideoSourceDock::currentFileSourceTypeChanged);
}

int VideoSourceDock::type() const
{
    return ui->sourceOptionsStackedWidget->currentIndex();
}

FileVideoSourceOptionsWidget* VideoSourceDock::fileVideoSourceOptions() const
{
    return m_fileVideoSourceOptionsWidget;
}

IPCameraVideoSourceOptionsWidget* VideoSourceDock::ipCameraSourceOptions() const
{
    return m_ipCameraVideoSourceOptionsWidget;
}

CameraVideoSourceOptionsWidget* VideoSourceDock::cameraSourceOptions() const
{
    return m_cameraVideoSourceOptionsWidget;
}

VideoSourceDock::~VideoSourceDock()
{
    delete m_cameraVideoSourceOptionsWidget;
    delete m_fileVideoSourceOptionsWidget;
    delete m_ipCameraVideoSourceOptionsWidget;
    delete ui;
}

void VideoSourceDock::sourceTypeChanged(bool checked)
{
    Q_UNUSED(checked)
    if (ui->fileSourceRadioButton->isChecked())
    {
        ui->sourceOptionsStackedWidget->setCurrentIndex(0);
    }
    else if (ui->ipCameraSourceRadioButton->isChecked())
    {
        ui->sourceOptionsStackedWidget->setCurrentIndex(1);
    }
    else
    {
        ui->sourceOptionsStackedWidget->setCurrentIndex(2);
    }
}
