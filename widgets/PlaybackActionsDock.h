#ifndef PLAYBACKACTIONSDOCK_H
#define PLAYBACKACTIONSDOCK_H

#include <QDockWidget>

namespace Ui {
class PlaybackActionsDock;
}

class PlaybackActionsDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit PlaybackActionsDock(QWidget *parent = 0);
    ~PlaybackActionsDock();

private:
    Ui::PlaybackActionsDock *ui;
};

#endif // PLAYBACKACTIONSDOCK_H
