#include "TrafficCounterMain.h"
#include "ui_trafficcountermain.h"

#include <QKeyEvent>
#include <QMessageBox>

TrafficCounterMain::TrafficCounterMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrafficCounterMain)
{
    ui->setupUi(this);
}

TrafficCounterMain::~TrafficCounterMain()
{
    delete ui;
}

void TrafficCounterMain::keyPressEvent(QKeyEvent * event)
{
    if (event->matches(QKeySequence::Quit))
    {
        if (QMessageBox::warning(0, tr("Warning"),
                                 tr("Are you sure you want to quit?"),
                                 QMessageBox::Ok,
                                 QMessageBox::Cancel) == QMessageBox::Ok) {}
        //close();
    }
}

void TrafficCounterMain::closeEvent(QCloseEvent * event)
{
    if (event->spontaneous())
    {
        event->ignore();
    }
}
