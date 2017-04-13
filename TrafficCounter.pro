#-------------------------------------------------
#
# Project created by QtCreator 2017-03-07T23:18:56
#
#-------------------------------------------------

QT       += core gui sql multimedia

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
    backend/database/DatabaseManager.cpp \
    videosources/AbstractVideoSource.cpp \
    videosources/FileVideoSource.cpp \
    videosources/LiveIPCameraVideoSource.cpp \
    widgets/DatabaseSettingsDialog.cpp \
    widgets/TrafficCounterMainWindow.cpp \
    widgets/VideoSourceDock.cpp \
    widgets/PlaybackActionsDock.cpp \
    widgets/FileVideoSourceOptionsWidget.cpp \
    widgets/IPCameraVideoSourceOptionsWidget.cpp \
    widgets/FileInfoDialog.cpp \
    widgets/CameraVideoSourceOptionsWidget.cpp \
    videosources/CameraVideoSource.cpp

HEADERS  += backend/CommandLineParser.h \
    backend/FrameProcessor.h \
    backend/Utils.h \
    backend/VideoProcessor.h \
    backend/VehicleBlob.h \
    backend/VideoRecorder.h \
    backend/TrafficCounterController.h \
    backend/database/DatabaseManager.h \
    videosources/AbstractVideoSource.h \
    videosources/FileVideoSource.h \
    videosources/LiveIPCameraVideoSource.h \
    widgets/DatabaseSettingsDialog.h \
    widgets/TrafficCounterMainWindow.h \
    widgets/VideoSourceDock.h \
    widgets/PlaybackActionsDock.h \
    widgets/FileVideoSourceOptionsWidget.h \
    widgets/IPCameraVideoSourceOptionsWidget.h \
    widgets/FileInfoDialog.h \
    widgets/CameraVideoSourceOptionsWidget.h \
    videosources/CameraVideoSource.h

FORMS    += ui/databasesettingsdialog.ui \
    ui/trafficcountermainwindow.ui \
    ui/videosourcedock.ui \
    ui/playbackactionsdock.ui \
    ui/filevideosourceoptionswidget.ui \
    ui/ipcameravideosourceoptions.ui \
    ui/fileinfodialog.ui \
    ui/cameravideosourceoptionswidget.ui
LIBS += `pkg-config opencv --libs --cflags`

DISTFILES += \
    README.md \
    INSTALL

RESOURCES += \
    resources.qrc

