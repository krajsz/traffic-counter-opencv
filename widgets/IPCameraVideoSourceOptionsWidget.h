#ifndef IPCAMERAVIDEOSOURCEOPTIONS_H
#define IPCAMERAVIDEOSOURCEOPTIONS_H

#include <QWidget>
#include "ui_ipcameravideosourceoptions.h"

class IPCameraVideoSourceOptions : public QWidget
{
    Q_OBJECT

public:
    explicit IPCameraVideoSourceOptions(QWidget *parent = 0);
    ~IPCameraVideoSourceOptions();

private:
    Ui::IPCameraVideoSourceOptions *ui;
};

#endif // IPCAMERAVIDEOSOURCEOPTIONS_H
