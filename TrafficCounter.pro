#-------------------------------------------------
#
# Project created by QtCreator 2017-03-07T23:18:56
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrafficCounter
TEMPLATE = app

CONFIG += C++11

SOURCES += trafficCounterApp.cpp\
    backend/CommandLineParser.cpp \
    backend/FrameProcessor.cpp \
    backend/Utils.cpp \
    backend/VehicleBlob.cpp \
    backend/VideoProcessor.cpp \
    backend/VideoRecorder.cpp \
    backend/TrafficCounterController.cpp \
    database/DatabaseManager.cpp \
    videosources/AbstractVideoSource.cpp \
    videosources/FileVideoSource.cpp \
    videosources/LiveIPCameraVideoSource.cpp \
    widgets/DatabaseSettingsDialog.cpp \
    widgets/TrafficCounterMainWindow.cpp \
    widgets/VideoSourceDock.cpp \
    widgets/PlaybackActionsDock.cpp \
    widgets/FileVideoSourceOptionsWidget.cpp \
    widgets/IPCameraVideoSourceOptionsWidget.cpp

HEADERS  += backend/CommandLineParser.h \
    backend/FrameProcessor.h \
    backend/Utils.h \
    backend/VideoProcessor.h \
    backend/VehicleBlob.h \
    backend/VideoRecorder.h \
    backend/TrafficCounterController.h \
    database/DatabaseManager.h \
    videosources/AbstractVideoSource.h \
    videosources/FileVideoSource.h \
    videosources/LiveIPCameraVideoSource.h \
    widgets/DatabaseSettingsDialog.h \
    widgets/TrafficCounterMainWindow.h \
    widgets/VideoSourceDock.h \
    widgets/PlaybackActionsDock.h \
    widgets/FileVideoSourceOptionsWidget.h \
    widgets/IPCameraVideoSourceOptionsWidget.h

FORMS    += ui/databasesettingsdialog.ui \
    ui/trafficcountermainwindow.ui \
    ui/videosourcedock.ui \
    ui/playbackactionsdock.ui \
    ui/filevideosourceoptionswidget.ui \
    ui/ipcameravideosourceoptions.ui
LIBS += `pkg-config opencv --libs --cflags`

DISTFILES += \
    README.md \
    INSTALL

