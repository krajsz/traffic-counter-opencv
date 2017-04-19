/***************************************************************************
    File                 : PlaybackActionsDock.cpp
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
#include "src/widgets/PlaybackActionsDock.h"
#include "ui_playbackactionsdock.h"

PlaybackActionsDock::PlaybackActionsDock(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::PlaybackActionsDock)
{
    ui->setupUi(this);
    ui->pauseButton->setEnabled(false);
    ui->recordButton->setEnabled(false);
    ui->saveScreenshotButton->setEnabled(false);
    ui->startButton->setEnabled(false);

    connect(ui->startButton, &QPushButton::clicked, this,
            [=] {
        ui->pauseButton->setEnabled(true);
        ui->recordButton->setEnabled(true);
        ui->saveScreenshotButton->setEnabled(true);
    });
}

PlaybackActionsDock::~PlaybackActionsDock()
{
    delete ui;
}

QPushButton* PlaybackActionsDock::pauseButton()
{
    return ui->pauseButton;
}

QPushButton* PlaybackActionsDock::startButton()
{
    return ui->startButton;
}

QPushButton* PlaybackActionsDock::recordButton()
{
    return ui->recordButton;
}

QPushButton* PlaybackActionsDock::saveScreenshotButton()
{
    return ui->saveScreenshotButton;
}
