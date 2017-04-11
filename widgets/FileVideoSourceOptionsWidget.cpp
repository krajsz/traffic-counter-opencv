#include "FileVideoSourceOptionsWidget.h"

FileVideoSourceOptionsWidget::FileVideoSourceOptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileVideoSourceOptionsWidget)
{
    ui->setupUi(this);
}

FileVideoSourceOptionsWidget::~FileVideoSourceOptionsWidget()
{
    delete ui;
}
