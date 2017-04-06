#include "VideoSourceDock.h"
#include "ui_videosourcedock.h"

VideoSourceDock::VideoSourceDock(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VideoSourceDock)
{
    ui->setupUi(this);
}

VideoSourceDock::~VideoSourceDock()
{
    delete ui;
}
