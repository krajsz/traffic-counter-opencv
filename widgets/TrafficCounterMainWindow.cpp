#include "widgets/TrafficCounterMainWindow.h"

#include "ui_trafficcountermainwindow.h"

#include <QKeyEvent>
#include <QMessageBox>

TrafficCounterMainWindow::TrafficCounterMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrafficCounterMainWindow)
{
    ui->setupUi(this);
}

TrafficCounterMainWindow::~TrafficCounterMainWindow()
{
    delete ui;
}

void TrafficCounterMainWindow::keyPressEvent(QKeyEvent * event)
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

void TrafficCounterMainWindow::closeEvent(QCloseEvent * event)
{
    if (event->spontaneous())
    {
        event->ignore();
    }
}
