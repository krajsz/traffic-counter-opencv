/***************************************************************************
    File                 : FileVideoSourceOptionsWidget.cpp
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
#include "FileVideoSourceOptionsWidget.h"
#include <QFile>
#include <QFileDialog>

#include <QDebug>

FileVideoSourceOptionsWidget::FileVideoSourceOptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileVideoSourceOptionsWidget)
{
    ui->setupUi(this);

    connect(ui->openFileButton, &QPushButton::clicked, this, &FileVideoSourceOptionsWidget::openFile);
    connect(ui->fileInfoButton, &QPushButton::clicked, this, &FileVideoSourceOptionsWidget::showFileInfoDialog);
}

FileVideoSourceOptionsWidget::~FileVideoSourceOptionsWidget()
{
    delete ui;
}

void FileVideoSourceOptionsWidget::showFileInfoDialog()
{
    if (!ui->filePathLineEdit->text().isEmpty())
    {
        QFile* file = new QFile(ui->filePathLineEdit->text());
        if (file->open(QFile::ReadOnly))
        {
            delete file;
            FileInfoDialog* fileInfoDialog = new FileInfoDialog(ui->filePathLineEdit->text());

            fileInfoDialog->show();
        }
    }
}

void FileVideoSourceOptionsWidget::openFile()
{
    ui->filePathLineEdit->setText(QFileDialog::getOpenFileName(0, "Select your video", QDir::homePath()));
}
