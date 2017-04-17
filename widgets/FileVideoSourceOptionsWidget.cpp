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
#include <QMessageBox>

#include <QDebug>

FileVideoSourceOptionsWidget::FileVideoSourceOptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileVideoSourceOptionsWidget)
{
    ui->setupUi(this);

    ui->fileInfoButton->setEnabled(false);
    connect(ui->openFileButton, &QPushButton::clicked, this, &FileVideoSourceOptionsWidget::openFile);
    connect(ui->fileInfoButton, &QPushButton::clicked, this, &FileVideoSourceOptionsWidget::showFileInfoDialog);
    connect(ui->filePathLineEdit, &QLineEdit::textChanged, this,
            [=]{
        bool exists = QFile::exists(ui->filePathLineEdit->text());
        ui->fileInfoButton->setEnabled(exists);
    });
}

QString FileVideoSourceOptionsWidget::filePath() const
{
    return ui->filePathLineEdit->text();
}

FileVideoSourceOptionsWidget::~FileVideoSourceOptionsWidget()
{
    delete ui;
}

bool FileVideoSourceOptionsWidget::ok() const
{
    //this means that the file exists and it's a video (at least the extension says so)
    return ui->fileInfoButton->isEnabled();
}

void FileVideoSourceOptionsWidget::showFileInfoDialog()
{

    QFile* file = new QFile(ui->filePathLineEdit->text());
    if (file->open(QFile::ReadOnly))
    {
        delete file;
        FileInfoDialog* fileInfoDialog = new FileInfoDialog(ui->filePathLineEdit->text());

        fileInfoDialog->show();
    }
    else
    {
        QMessageBox::warning(0, "Error opening file", "Couldn't open file: " + file->fileName());
    }

}

void FileVideoSourceOptionsWidget::openFile()
{
    ui->filePathLineEdit->setText(QFileDialog::getOpenFileName(0, "Select your video",
                                                               QDir::homePath(), "Video files [ *.avi , *.mp4 , *.MP4 , *.MKV *.mkv]"));
}
