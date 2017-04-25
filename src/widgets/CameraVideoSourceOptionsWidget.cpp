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
#include "src/widgets/CameraVideoSourceOptionsWidget.h"
#include "ui_cameravideosourceoptionswidget.h"
#include <QCamera>
#include <QCameraInfo>
#include <QDir>

#include <QDebug>
CameraVideoSourceOptionsWidget::CameraVideoSourceOptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraVideoSourceOptionsWidget)
{
    ui->setupUi(this);

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras(QCamera::FrontFace);
    foreach (const QCameraInfo &cameraInfo, cameras) {
        QListWidgetItem* cameraDescription = new QListWidgetItem(cameraInfo.deviceName() +
                                                                 QLatin1String(" ") + cameraInfo.description());


        ui->availableCamerasListWidget->addItem(cameraDescription);
    }
    if (!ui->availableCamerasListWidget->count())
    {
        //maybe Qt can't see them somehow, let's check it again
#ifdef Q_OS_LINUX
        qDebug() << "dir";

        QDir lsDevDir("/dev/");
        lsDevDir.setNameFilters(QStringList() << "video*");
        QStringList devVids = lsDevDir.entryList(QDir::System);

        foreach (const QString& devv, devVids)
        {
            QListWidgetItem* devItem = new QListWidgetItem("Device /dev/" + devv);
            ui->availableCamerasListWidget->addItem(devItem);
        }
#endif
        if (ui->availableCamerasListWidget->count() == 0)
        {
            QListWidgetItem* noCamerasItem = new QListWidgetItem(QLatin1String("No cameras found."));
            noCamerasItem->setFlags(noCamerasItem->flags()& ~Qt::ItemIsSelectable);
            ui->availableCamerasListWidget->addItem(noCamerasItem);
            ui->selectCameraButton->setEnabled(false);
        }
    }
}

bool CameraVideoSourceOptionsWidget::ok() const
{
    return ui->selectCameraButton->isEnabled();
}
QString CameraVideoSourceOptionsWidget::cameraName() const
{
    return ui->availableCamerasListWidget->currentItem()->text();
}

CameraVideoSourceOptionsWidget::~CameraVideoSourceOptionsWidget()
{
    delete ui;
}
