#-------------------------------------------------
#
# Project created by QtCreator 2017-03-07T23:18:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrafficCounter
TEMPLATE = app


SOURCES += main.cpp\
        TrafficCounterMain.cpp \
    DatabaseSettingsDialog.cpp \
    AbstractVideoSource.cpp \
    FileVideoSource.cpp \
    LiveIPCameraVideoSource.cpp \
    VehicleBlob.cpp

HEADERS  += TrafficCounterMain.h \
    DatabaseSettingsDialog.h \
    AbstractVideoSource.h \
    FileVideoSource.h \
    LiveIPCameraVideoSource.h \
    VehicleBlob.h

FORMS    += trafficcountermain.ui \
    databasesettingsdialog.ui
LIBS += `pkg-config opencv --libs --cflags`
