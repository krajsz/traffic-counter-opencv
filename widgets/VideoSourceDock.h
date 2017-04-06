#ifndef VIDEOSOURCEDOCK_H
#define VIDEOSOURCEDOCK_H

#include <QDockWidget>

namespace Ui {
class VideoSourceDock;
}

class VideoSourceDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit VideoSourceDock(QWidget *parent = 0);
    ~VideoSourceDock();

private:
    Ui::VideoSourceDock *ui;
};

#endif // VIDEOSOURCEDOCK_H
