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
#include "videosources/LiveIPCameraVideoSource.h"
#include "videosources/CameraVideoSource.h"

#include "ui_trafficcountermainwindow.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTimer>

#include <QDebug>

TrafficCounterMainWindow::TrafficCounterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrafficCounterMainWindow),
    m_playbackActionsDock(new PlaybackActionsDock),
    m_databaseSettingsDialog(new DatabaseSettingsDialog),
    m_videoSourceDock(new VideoSourceDock),
    m_updateImageTimer(new QTimer)
{
    ui->setupUi(this);

    m_fileVideoSourceProgressBar = ui->playbackProgressProgressBar;

    setAttribute(Qt::WA_DeleteOnClose);

    m_updateImageTimer->setInterval(30);

    ui->videoFrameDisplayLabel->setPixmap(QPixmap(":/images/noSource.png"));
    addDockWidget(Qt::BottomDockWidgetArea, m_playbackActionsDock);
    addDockWidget(Qt::RightDockWidgetArea, m_videoSourceDock);
    connect(ui->aboutAction, &QAction::triggered, this, &TrafficCounterMainWindow::showAbout);
    connect(ui->databaseSettingsAction, &QAction::triggered, this, &TrafficCounterMainWindow::databaseSettingsActionClicked);
    connect(ui->playbackActionsAction, &QAction::triggered, this, &TrafficCounterMainWindow::playActionsChecked);
    connect(ui->sourceSettingsAction, &QAction::triggered, this, &TrafficCounterMainWindow::sourceSettingsActionChecked);

    connect(m_playbackActionsDock, &PlaybackActionsDock::visibilityChanged, this, &TrafficCounterMainWindow::playbackDockClosed);
    connect(m_videoSourceDock, &VideoSourceDock::visibilityChanged, this, &TrafficCounterMainWindow::videoSourceDockClosed);

    connect(m_playbackActionsDock->startButton(), &QPushButton::clicked, this, &TrafficCounterMainWindow::startProcessing);
    connect(m_playbackActionsDock->pauseButton(), &QPushButton::clicked, this, &TrafficCounterMainWindow::pauseProcessing);
    connect(m_playbackActionsDock->recordButton(), &QPushButton::clicked, this, &TrafficCounterMainWindow::record);
    connect(m_playbackActionsDock->saveScreenshotButton(), &QPushButton::clicked, this, &TrafficCounterMainWindow::saveScreenshot);

    connect(m_videoSourceDock, &VideoSourceDock::currentFileSourceTypeChanged, this, &TrafficCounterMainWindow::enableButtonStart);

}

void TrafficCounterMainWindow::setController(TrafficCounterController *controller)
{
    m_controller = controller;

    connect(m_controller->videoProcessor(), &VideoProcessor::progress,
            m_fileVideoSourceProgressBar, &FileVideoSourceProgressBar::setValue, Qt::DirectConnection);
    connect(m_controller->videoProcessor(), &VideoProcessor::currentProgressInTime,
            m_fileVideoSourceProgressBar, &FileVideoSourceProgressBar::setText, Qt::DirectConnection);
}

TrafficCounterMainWindow::~TrafficCounterMainWindow()
{
    delete ui;
    delete m_playbackActionsDock;
    delete m_databaseSettingsDialog;
    delete m_videoSourceDock;
    delete m_controller;
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
    Q_UNUSED(event)
}

void TrafficCounterMainWindow::showAbout()
{
    QMessageBox::about(0, tr("About"), "TrafficCounter v1.0");
}

void TrafficCounterMainWindow::openFileActionClicked()
{
    const QString fileName = QFileDialog::getOpenFileName(0, QLatin1String("Select a video"), QDir::homePath());

    QFile* pathOfFileSelectedFile = new QFile(fileName);
    if (pathOfFileSelectedFile->exists())
    {
        delete pathOfFileSelectedFile;
        FileVideoSource* newSource = new FileVideoSource(fileName);

        m_controller->setSource(newSource);
    }
}

void TrafficCounterMainWindow::databaseSettingsActionClicked()
{
    if (!m_databaseSettingsDialog->isVisible())
    {
        m_databaseSettingsDialog->show();
    }
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

void TrafficCounterMainWindow::startProcessing()
{
    AbstractVideoSource* source;
    if (m_videoSourceDock->type() == 0)
    {
        //file
        FileVideoSource* fsource = new FileVideoSource(m_videoSourceDock->fileVideoSourceOptions()->filePath());

        fsource->setInfos(VideoProcessor::videoInfos(fsource->path()));
        qDebug() << "fileSourceStartProcessing";
        source = fsource;
    }
    else if (m_videoSourceDock->type() == 1)
    {
        //ip

        LiveIPCameraVideoSource* ipsource = new LiveIPCameraVideoSource(m_videoSourceDock->ipCameraSourceOptions()->url());

        if (!m_videoSourceDock->ipCameraSourceOptions()->urlContainsEverything())
        {
            ipsource->setPort(m_videoSourceDock->ipCameraSourceOptions()->port());
            ipsource->setUserName(m_videoSourceDock->ipCameraSourceOptions()->userName());
            ipsource->setPassword(m_videoSourceDock->ipCameraSourceOptions()->password());
        }
        qDebug() << "ipSourceStartProcessing";

        source = ipsource;
    }
    else
    {
        //camera
        CameraVideoSource* csource = new CameraVideoSource(m_videoSourceDock->cameraSourceOptions()->cameraName());
        qDebug() << "camSourceStartProcessing";

        source = csource;
    }

    connect(m_updateImageTimer, &QTimer::timeout, this, &TrafficCounterMainWindow::updateImageLabel);
    m_updateImageTimer->start(30);

    m_controller->setSource(source);
    m_controller->startProcessing();
}

void TrafficCounterMainWindow::pauseProcessing()
{
    m_controller->pauseProcessing();
}

void TrafficCounterMainWindow::saveScreenshot()
{
    m_controller->saveScreenshot();
}

void TrafficCounterMainWindow::stopProcessing()
{
    disconnect(m_updateImageTimer, &QTimer::timeout, this, &TrafficCounterMainWindow::updateImageLabel);

    m_controller->stopProcessing();
}

void TrafficCounterMainWindow::record()
{
    m_controller->startRecording();
}

void TrafficCounterMainWindow::enableButtonStart(int newSourceType)
{
    if (newSourceType == 0)
    {
        FileVideoSourceOptionsWidget* fsow = m_videoSourceDock->fileVideoSourceOptions();
        m_playbackActionsDock->startButton()->setEnabled(fsow->ok());
    }
    else if (newSourceType == 1)
    {
        IPCameraVideoSourceOptionsWidget* ipcvsow = m_videoSourceDock->ipCameraSourceOptions();
        m_playbackActionsDock->startButton()->setEnabled(ipcvsow->ok());
    }
    else
    {
        CameraVideoSourceOptionsWidget* cvsow = m_videoSourceDock->cameraSourceOptions();
        m_playbackActionsDock->startButton()->setEnabled(cvsow->ok());

    }
}

void TrafficCounterMainWindow::updateImageLabel()
{
    ui->videoFrameDisplayLabel->setPixmap(QPixmap::fromImage(m_controller->currentFrame()));
}
