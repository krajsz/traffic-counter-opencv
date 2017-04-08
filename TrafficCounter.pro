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
    database/DatabaseManager.cpp \
    videosources/AbstractVideoSource.cpp \
    videosources/FileVideoSource.cpp \
    videosources/LiveIPCameraVideoSource.cpp \
    widgets/DatabaseSettingsDialog.cpp \
    widgets/TrafficCounterMainWindow.cpp \
    widgets/VideoSourceDock.cpp \
    widgets/PlaybackActionsDock.cpp

HEADERS  += backend/CommandLineParser.h \
    backend/FrameProcessor.h \
    backend/Utils.h \
    backend/VideoProcessor.h \
    backend/VehicleBlob.h \
    database/DatabaseManager.h \
    videosources/AbstractVideoSource.h \
    videosources/FileVideoSource.h \
    videosources/LiveIPCameraVideoSource.h \
    widgets/DatabaseSettingsDialog.h \
    widgets/TrafficCounterMainWindow.h \
    widgets/VideoSourceDock.h \
    widgets/PlaybackActionsDock.h

FORMS    += ui/databasesettingsdialog.ui \
    ui/trafficcountermainwindow.ui \
    ui/videosourcedock.ui \
    ui/playbackactionsdock.ui
LIBS += `pkg-config opencv --libs --cflags`

DISTFILES += \
    README.md \
    INSTALL

