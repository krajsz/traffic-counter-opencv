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
#include "src/widgets/TrafficCounterMainWindow.h"
#include "src/videosources/LiveIPCameraVideoSource.h"
#include "src/videosources/CameraVideoSource.h"
#include "src/backend/Utils.h"

#include "ui_trafficcountermainwindow.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTimer>
#include <QActionGroup>

#include <QDebug>

TrafficCounterMainWindow::TrafficCounterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrafficCounterMainWindow),
    m_playbackActionsDock(new PlaybackActionsDock),
    m_databaseSettingsDialog(new DatabaseSettingsDialog),
    m_videoSourceDock(new VideoSourceDock),
    m_guiSettingsFile(QApplication::applicationDirPath() + "/guiSettings.ini")
{
    ui->setupUi(this);

    m_fileVideoSourceProgressBar = ui->playbackProgressProgressBar;

    //QSettings guiSettingsFile(m_guiSettingsFile, QSettings::NativeFormat);

    QActionGroup* playbackModeAg = new QActionGroup(ui->menuPlayback_mode);
    playbackModeAg->setExclusive(true);

    playbackModeAg->addAction(ui->originalFrameAction);
    playbackModeAg->addAction(ui->processedFrameAction);

    ui->menuPlayback_mode->setEnabled(false);

    setAttribute(Qt::WA_DeleteOnClose);

    ui->videoFrameDisplayLabel->setPixmap(QPixmap(QLatin1String(":/images/noSource.png")));
    addDockWidget(Qt::BottomDockWidgetArea, m_playbackActionsDock);
    addDockWidget(Qt::RightDockWidgetArea, m_videoSourceDock);
    connect(ui->aboutAction, &QAction::triggered, this, &TrafficCounterMainWindow::showAbout);
    connect(ui->databaseSettingsAction, &QAction::triggered, this, &TrafficCounterMainWindow::databaseSettingsActionClicked);
    connect(ui->playbackActionsAction, &QAction::triggered, this, &TrafficCounterMainWindow::playActionsChecked);
    connect(ui->sourceSettingsAction, &QAction::triggered, this, &TrafficCounterMainWindow::sourceSettingsActionChecked);

    connect(m_playbackActionsDock, &PlaybackActionsDock::visibilityChanged, this, &TrafficCounterMainWindow::playbackDockClosed);
    connect(m_videoSourceDock, &VideoSourceDock::visibilityChanged, this, &TrafficCounterMainWindow::videoSourceDockClosed);

    connect(m_playbackActionsDock->startButton(), &QPushButton::clicked, this, &TrafficCounterMainWindow::startProcessing);
    connect(m_playbackActionsDock->pauseButton(), &QPushButton::clicked, this, &TrafficCounterMainWindow::pauseResumeButtonClicked);
    connect(m_playbackActionsDock->recordButton(), &QPushButton::clicked, this, &TrafficCounterMainWindow::startStopRecordingButtonClicked);
    connect(m_playbackActionsDock->saveScreenshotButton(), &QPushButton::clicked, this, &TrafficCounterMainWindow::saveScreenshot);

    connect(m_videoSourceDock, &VideoSourceDock::currentFileSourceTypeChanged, this, &TrafficCounterMainWindow::enableButtonStart);

    connect(m_videoSourceDock->fileVideoSourceOptions(), &FileVideoSourceOptionsWidget::fileOpened, m_playbackActionsDock->startButton(), &QPushButton::setEnabled);

    connect(playbackModeAg, &QActionGroup::triggered, this, &TrafficCounterMainWindow::playbackModeChanged);


}

void TrafficCounterMainWindow::setController(TrafficCounterController *controller)
{
    m_controller = controller;

    connect(m_controller->videoProcessor(), &VideoProcessor::progress,
            m_fileVideoSourceProgressBar, &FileVideoSourceProgressBar::setValue, Qt::DirectConnection);
    connect(m_controller->videoProcessor(), &VideoProcessor::currentProgressInTime,
            m_fileVideoSourceProgressBar, &FileVideoSourceProgressBar::setText, Qt::DirectConnection);
    connect(m_controller->videoProcessor()->frameProcessor(), &FrameProcessor::frameProcessed,
            this, &TrafficCounterMainWindow::updateImageLabel);

}

TrafficCounterMainWindow::~TrafficCounterMainWindow()
{
    delete m_databaseSettingsDialog;
    delete ui;

    delete m_videoSourceDock;

    delete m_controller;
    delete m_playbackActionsDock;

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

void TrafficCounterMainWindow::playbackModeChanged(QAction *action)
{
    if (action == ui->originalFrameAction)
    {
        m_controller->videoProcessor()->frameProcessor()->setEmitOriginal(true);
    }
    else
    {
        m_controller->videoProcessor()->frameProcessor()->setEmitOriginal(false);
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

    ui->menuPlayback_mode->setEnabled(true);

    m_controller->setSource(source);
    m_controller->startProcessing();
}

void TrafficCounterMainWindow::pauseProcessing()
{
    m_controller->pauseProcessing();
}

void TrafficCounterMainWindow::resumeProcessing()
{
    m_controller->resumeProcessing();
}

void TrafficCounterMainWindow::pauseResumeButtonClicked()
{
    if (m_playbackActionsDock->pauseButton()->text() == QLatin1String("&Pause"))
    {
        m_playbackActionsDock->pauseButton()->setText("&Resume");
        pauseProcessing();
    }
    else
    {
        m_playbackActionsDock->pauseButton()->setText("&Pause");
        resumeProcessing();
    }
}

void TrafficCounterMainWindow::startStopButtonClicked()
{
    if (m_playbackActionsDock->startButton()->text() == QLatin1String("&Start"))
    {
        startProcessing();
        m_playbackActionsDock->recordButton()->setEnabled(true);
        m_playbackActionsDock->startButton()->setText("&Stop");
    }
    else
    {
        stopProcessing();
        m_playbackActionsDock->recordButton()->setEnabled(false);
        m_playbackActionsDock->startButton()->setText("&Start");
    }
}

void TrafficCounterMainWindow::startStopRecordingButtonClicked()
{
    if (m_playbackActionsDock->recordButton()->text() == QLatin1String("&Record"))
    {
        m_controller->startRecording();
        m_playbackActionsDock->recordButton()->setText("&Stop recording");
    }
    else
    {
        m_controller->stopRecording();
        m_playbackActionsDock->recordButton()->setText("&Record");
    }
}

void TrafficCounterMainWindow::saveScreenshot()
{
    ui->mainStatusBar->showMessage("Screenshot saved!", 2000);
    m_controller->saveScreenshot();
}

void TrafficCounterMainWindow::stopProcessing()
{
    m_controller->stopProcessing();
}

void TrafficCounterMainWindow::enableButtonStart(int newSourceType)
{
    if (newSourceType == 0)
    {
        FileVideoSourceOptionsWidget* fsow = m_videoSourceDock->fileVideoSourceOptions();
        m_playbackActionsDock->startButton()->setEnabled(fsow->ok());
        ui->playbackProgressProgressBar->show();
    }
    else if (newSourceType == 1)
    {
        IPCameraVideoSourceOptionsWidget* ipcvsow = m_videoSourceDock->ipCameraSourceOptions();
        m_playbackActionsDock->startButton()->setEnabled(ipcvsow->ok());
        ui->playbackProgressProgressBar->hide();
    }
    else
    {
        CameraVideoSourceOptionsWidget* cvsow = m_videoSourceDock->cameraSourceOptions();
        m_playbackActionsDock->startButton()->setEnabled(cvsow->ok());
        ui->playbackProgressProgressBar->hide();
    }
}

void TrafficCounterMainWindow::updateImageLabel(const cv::Mat& img)
{
    m_imageLabelSize = cv::Size(ui->videoFrameDisplayLabel->size().width(),
                                ui->videoFrameDisplayLabel->size().height());
    // here
    QImage image;
    if (m_controller->videoProcessor()->frameProcessor()->emitOriginal())
    {
        image = Utils::Mat2QImage(img);
    }
    else
    {
        image = Utils::GrayMat2QImage(img);
    }

    ui->videoFrameDisplayLabel->setPixmap(QPixmap::fromImage(image));
}
