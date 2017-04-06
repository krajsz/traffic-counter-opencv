#ifndef DATABASESETTINGSDIALOG_H
#define DATABASESETTINGSDIALOG_H

#include <QWidget>

namespace Ui {
class DatabaseSettingsDialog;
}

class DatabaseSettingsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseSettingsDialog(QWidget *parent = 0);
    ~DatabaseSettingsDialog();

private:
    Ui::DatabaseSettingsDialog *ui;
};

#endif // DATABASESETTINGSDIALOG_H
