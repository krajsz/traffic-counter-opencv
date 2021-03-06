/***************************************************************************
    File                 : IPCameraVideoSourceOptionsWidget.cpp
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
#include "src/widgets/IPCameraVideoSourceOptionsWidget.h"
#include <QMessageBox>
#include <opencv2/opencv.hpp>

#include <QDebug>

IPCameraVideoSourceOptionsWidget::IPCameraVideoSourceOptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IPCameraVideoSourceOptions)
{
    ui->setupUi(this);
    connect(ui->urlContainsEverythingCheckBox, &QCheckBox::toggled,
            this, &IPCameraVideoSourceOptionsWidget::urlContainsEverythingChecked);

    connect(ui->testConnectionButton, &QPushButton::clicked, this, &IPCameraVideoSourceOptionsWidget::testButtonClicked);
    connect(ui->urlLineEdit, &QLineEdit::textEdited, this, &IPCameraVideoSourceOptionsWidget::enableButtonTest);
}

IPCameraVideoSourceOptionsWidget::~IPCameraVideoSourceOptionsWidget()
{
    delete ui;
}

void IPCameraVideoSourceOptionsWidget::urlContainsEverythingChecked(bool checked)
{
    if (checked)
    {
        ui->portLineEdit->setEnabled(false);
        ui->userNameLineEdit->setEnabled(false);
        ui->passwordLineEdit->setEnabled(false);
    }
    else
    {
        ui->portLineEdit->setEnabled(true);
        ui->userNameLineEdit->setEnabled(true);
        ui->passwordLineEdit->setEnabled(true);
    }
}

bool IPCameraVideoSourceOptionsWidget::testButtonClicked()
{
    if (ui->urlLineEdit->text().isEmpty())
    {
        QMessageBox::warning(0, QLatin1String("Error"), QLatin1String("Error, url not set!"));
        return false;

    }
    else
    {
        cv::VideoCapture cap;
        cap.open(ui->urlLineEdit->text().toStdString());
        if (cap.isOpened())
        {
            cap.release();
            QMessageBox::information(0, QLatin1String("Success"), QLatin1String("Successfully connected to the camera!"));

            return true;
        }
        QMessageBox::warning(0, QLatin1String("Error"), QLatin1String("Error, unable to connect to camera!"));

        return false;
    }
}

bool IPCameraVideoSourceOptionsWidget::ok()
{
    //todo
    return true;
}

void IPCameraVideoSourceOptionsWidget::enableButtonTest(const QString &newUrl)
{
    ui->testConnectionButton->setEnabled(!newUrl.isEmpty());
}

QString IPCameraVideoSourceOptionsWidget::url() const
{
    return ui->urlLineEdit->text();
}

QString IPCameraVideoSourceOptionsWidget::userName() const
{
    return ui->userNameLineEdit->text();
}

bool IPCameraVideoSourceOptionsWidget::urlContainsEverything() const
{
    return ui->urlContainsEverythingCheckBox->isChecked();
}

QString IPCameraVideoSourceOptionsWidget::password() const
{
    return ui->passwordLineEdit->text();;
}

int IPCameraVideoSourceOptionsWidget::port() const
{
    return ui->portLineEdit->text().toInt();
}
