#include "IPCameraVideoSourceOptionsWidget.h"

IPCameraVideoSourceOptions::IPCameraVideoSourceOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IPCameraVideoSourceOptions)
{
    ui->setupUi(this);
}

IPCameraVideoSourceOptions::~IPCameraVideoSourceOptions()
{
    delete ui;
}
