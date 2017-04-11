#ifndef FILEVIDEOSOURCEOPTIONSWIDGET_H
#define FILEVIDEOSOURCEOPTIONSWIDGET_H

#include <QWidget>
#include "ui_filevideosourceoptionswidget.h"

class FileVideoSourceOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileVideoSourceOptionsWidget(QWidget *parent = 0);
    ~FileVideoSourceOptionsWidget();

private:
    Ui::FileVideoSourceOptionsWidget *ui;
};

#endif // FILEVIDEOSOURCEOPTIONSWIDGET_H
