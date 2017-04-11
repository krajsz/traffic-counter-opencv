#include "IPCameraVideoSourceOptionsWidget.h"
#include <QDebug>

IPCameraVideoSourceOptionsWidget::IPCameraVideoSourceOptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IPCameraVideoSourceOptions)
{
    ui->setupUi(this);
    connect(ui->urlContainsEverythingCheckBox, &QCheckBox::toggled,
            this, &IPCameraVideoSourceOptionsWidget::urlContainsEverythingChecked);
}

IPCameraVideoSourceOptionsWidget::~IPCameraVideoSourceOptionsWidget()
{
    delete ui;
}

void IPCameraVideoSourceOptionsWidget::urlContainsEverythingChecked(bool checked)
{
    if (checked)
    {
        ui->portLineEdit->setEnabled(false);
        ui->userNameLineEdit->setEnabled(false);
        ui->passwordLineEdit->setEnabled(false);
    }
    else
    {
        ui->portLineEdit->setEnabled(true);
        ui->userNameLineEdit->setEnabled(true);
        ui->passwordLineEdit->setEnabled(true);
    }
}
