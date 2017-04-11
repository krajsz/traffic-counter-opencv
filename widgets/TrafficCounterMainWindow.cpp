/***************************************************************************
    File                 : TrafficCounterMainWindow.cpp
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
#include "widgets/TrafficCounterMainWindow.h"
#include "ui_trafficcountermainwindow.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

TrafficCounterMainWindow::TrafficCounterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrafficCounterMainWindow),
    m_playbackActionsDock(new PlaybackActionsDock),
    m_databaseSettingsDialog(new DatabaseSettingsDialog),
    m_videoSourceDock(new VideoSourceDock)
{
    ui->setupUi(this);
    addDockWidget(Qt::BottomDockWidgetArea, m_playbackActionsDock);
    addDockWidget(Qt::RightDockWidgetArea, m_videoSourceDock);
    connect(ui->aboutAction, &QAction::triggered, this, &TrafficCounterMainWindow::showAbout);
    connect(ui->databaseSettingsAction, &QAction::triggered, this, &TrafficCounterMainWindow::databaseSettingsActionClicked);
    connect(ui->playbackActionsAction, &QAction::triggered, this, &TrafficCounterMainWindow::playActionsChecked);
    connect(ui->sourceSettingsAction, &QAction::triggered, this, &TrafficCounterMainWindow::sourceSettingsActionChecked);

    connect(m_playbackActionsDock, &PlaybackActionsDock::visibilityChanged, this, &TrafficCounterMainWindow::playbackDockClosed);
    connect(m_videoSourceDock, &VideoSourceDock::visibilityChanged, this, &TrafficCounterMainWindow::videoSourceDockClosed);
}

TrafficCounterMainWindow::~TrafficCounterMainWindow()
{
    delete ui;
}

void TrafficCounterMainWindow::keyPressEvent(QKeyEvent * event)
{
    if (event->matches(QKeySequence::Quit))
    {
        if (QMessageBox::warning(0, tr("Warning"),
                                 tr("Are you sure you want to quit?"),
                                 QMessageBox::Ok,
                                 QMessageBox::Cancel) == QMessageBox::Ok)
        {
            close();
        }
    }
}

void TrafficCounterMainWindow::closeEvent(QCloseEvent * event)
{

}

void TrafficCounterMainWindow::showAbout()
{
    QMessageBox::about(0, tr("About"), "TrafficCounter v1.0");
}

void TrafficCounterMainWindow::openFileActionClicked()
{

}

void TrafficCounterMainWindow::databaseSettingsActionClicked()
{
    if (m_databaseSettingsDialog->isHidden())
    {
        m_databaseSettingsDialog->show();
    }

    qDebug() << "ddd";
}

void TrafficCounterMainWindow::sourceSettingsActionChecked(bool checked)
{
    if (checked)
    {
        m_videoSourceDock->show();
    }
    else
    {
        m_videoSourceDock->hide();
    }
}

void TrafficCounterMainWindow::playActionsChecked(bool checked)
{
    if (checked)
    {
        m_playbackActionsDock->show();
    }
    else
    {
        m_playbackActionsDock->hide();
    }
}

void TrafficCounterMainWindow::playbackDockClosed()
{
    if (!m_playbackActionsDock->isVisible())
    {
        ui->playbackActionsAction->setChecked(false);
    }
}

void TrafficCounterMainWindow::videoSourceDockClosed()
{
    if (!m_videoSourceDock->isVisible())
    {
        ui->sourceSettingsAction->setChecked(false);
    }
}
