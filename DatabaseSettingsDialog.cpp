#include "DatabaseSettingsDialog.h"
#include "ui_databasesettingsdialog.h"

DatabaseSettingsDialog::DatabaseSettingsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseSettingsDialog)
{
    ui->setupUi(this);
}

DatabaseSettingsDialog::~DatabaseSettingsDialog()
{
    delete ui;
}
