#ifndef TRAFFICCOUNTERMAIN_H
#define TRAFFICCOUNTERMAIN_H

#include <QMainWindow>

namespace Ui {
class TrafficCounterMainWindow;
}

class TrafficCounterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrafficCounterMainWindow(QWidget *parent = 0);
    ~TrafficCounterMainWindow();

private:
    Ui::TrafficCounterMainWindow *ui;
protected:
    void keyPressEvent(QKeyEvent*);
    void closeEvent(QCloseEvent*);
};

#endif // TRAFFICCOUNTERMAIN_H
