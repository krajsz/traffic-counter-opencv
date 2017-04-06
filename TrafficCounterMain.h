#ifndef TRAFFICCOUNTERMAIN_H
#define TRAFFICCOUNTERMAIN_H

#include <QMainWindow>

namespace Ui {
class TrafficCounterMain;
}

class TrafficCounterMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrafficCounterMain(QWidget *parent = 0);
    ~TrafficCounterMain();

private:
    Ui::TrafficCounterMain *ui;
protected:
    void keyPressEvent(QKeyEvent*);
    void closeEvent(QCloseEvent*);
};

#endif // TRAFFICCOUNTERMAIN_H
