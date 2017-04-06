#include <QApplication>
#include "widgets/TrafficCounterMainWindow.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*TrafficCounterMain w;
    w.show();*/

    return a.exec();
}
