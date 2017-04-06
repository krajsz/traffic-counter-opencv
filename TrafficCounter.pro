#-------------------------------------------------
#
# Project created by QtCreator 2017-03-07T23:18:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrafficCounter
TEMPLATE = app

CONFIG += C++11

SOURCES += trafficCounterApp.cpp\
    backend/CommandLineParser.cpp \
    backend/FrameProcessor.cpp \
    backend/VehicleBlob.cpp \
    backend/VideoProcessor.cpp \
    database/DatabaseManager.cpp \
    videosources/AbstractVideoSource.cpp \
    videosources/FileVideoSource.cpp \
    videosources/LiveIPCameraVideoSource.cpp \
    widgets/DatabaseSettingsDialog.cpp \
    widgets/DatabaseSettingsWidget.cpp \
    widgets/TrafficCounterMainWindow.cpp \
    widgets/VideoSourceDock.cpp \
    backend/Utils.cpp


HEADERS  += backend/CommandLineParser.h \
    backend/FrameProcessor.h \
    backend/VideoProcessor.h \
    backend/VehicleBlob.h \
    database/DatabaseManager.h \
    videosources/AbstractVideoSource.h \
    videosources/FileVideoSource.h \
    videosources/LiveIPCameraVideoSource.h \
    widgets/DatabaseSettingsDialog.h \
    widgets/DatabaseSettingsWidget.h \
    widgets/TrafficCounterMainWindow.h \
    widgets/VideoSourceDock.h \
    backend/Utils.h


FORMS    += ui/databasesettingsdialog.ui \
    ui/trafficcountermainwindow.ui \
    ui/videosourcedock.ui
LIBS += `pkg-config opencv --libs --cflags`

DISTFILES += \
    README.md \
    package_bgs/LBSP/LBSP_16bits_dbcross_1ch.i \
    package_bgs/LBSP/LBSP_16bits_dbcross_3ch1t.i \
    package_bgs/LBSP/LBSP_16bits_dbcross_3ch3t.i \
    package_bgs/LBSP/LBSP_16bits_dbcross_s3ch.i \
    package_bgs/ViBe/LICENSE
