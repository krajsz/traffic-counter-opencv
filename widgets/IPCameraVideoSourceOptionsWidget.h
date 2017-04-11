#ifndef IPCAMERAVIDEOSOURCEOPTIONS_H
#define IPCAMERAVIDEOSOURCEOPTIONS_H

#include <QWidget>
#include "ui_ipcameravideosourceoptions.h"

class IPCameraVideoSourceOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IPCameraVideoSourceOptionsWidget(QWidget *parent = 0);
    ~IPCameraVideoSourceOptionsWidget();

private:
    Ui::IPCameraVideoSourceOptions *ui;
private Q_SLOTS:
    void urlContainsEverythingChecked(bool checked);
};

#endif // IPCAMERAVIDEOSOURCEOPTIONS_H
