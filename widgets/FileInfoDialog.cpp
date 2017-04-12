/***************************************************************************
    File                 : FileInfoDialog.cpp
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
#include "FileInfoDialog.h"
#include "ui_fileinfodialog.h"

#include <QProcess>
#include <QFileInfo>
#include <QDateTime>

FileInfoDialog::FileInfoDialog(const QString &fileName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileInfoDialog)
{
    ui->setupUi(this);

    QIODevice* file = new QFile(fileName);

    if (file->open(QIODevice::ReadOnly))
    {
        QFileInfo infos;
        infos.setFile(fileName);

        ui->createdLabel->setText(QLatin1String("Created: ") + infos.created().toString());
        ui->fileNameLabel->setText(QLatin1String("File name: ") + infos.fileName());
        ui->lastModifiedLabel->setText(QLatin1String("Last modified: ") + infos.lastModified().toString());
        ui->ownerLabel->setText(QLatin1String("Owner: ") + infos.owner());

        ui->readableLabel->setText(QLatin1String("Readable") + (infos.isReadable() ? QLatin1String("yes") : QLatin1String("no")));
    }
}

FileInfoDialog::~FileInfoDialog()
{
    delete ui;
}
