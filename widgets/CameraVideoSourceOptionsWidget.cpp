/***************************************************************************
    File                 : CameraVideoSourceOptionsWidget.cpp
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
#include "CameraVideoSourceOptionsWidget.h"
#include "ui_cameravideosourceoptionswidget.h"
#include <QCamera>
#include <QCameraInfo>

#include <QDebug>
CameraVideoSourceOptionsWidget::CameraVideoSourceOptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraVideoSourceOptionsWidget)
{
    ui->setupUi(this);

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras) {
        QListWidgetItem* cameraDescription = new QListWidgetItem(cameraInfo.deviceName() +
                                                                 QLatin1String(" ") + cameraInfo.description());


        ui->availableCamerasListWidget->addItem(cameraDescription);
    }
    if (!ui->availableCamerasListWidget->count())
    {
        QListWidgetItem* noCamerasItem = new QListWidgetItem(QLatin1String("No cameras found."));
        noCamerasItem->setFlags(noCamerasItem->flags()& ~Qt::ItemIsSelectable);
        ui->availableCamerasListWidget->addItem(noCamerasItem);
        ui->selectCameraButton->setEnabled(false);
    }
}

QString CameraVideoSourceOptionsWidget::cameraName() const
{
    return ui->availableCamerasListWidget->currentItem()->text();
}

CameraVideoSourceOptionsWidget::~CameraVideoSourceOptionsWidget()
{
    delete ui;
}
