/***************************************************************************
    File                 : DatabaseSettingsDialog.cpp
    Project              : TrafficCounter
    Description          :
    --------------------------------------------------------------------
    Copyright            : (C) 2017 Fábián Kristóf - Szabolcs (fkristofszabolcs@gmail.com)
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/
#include "src/widgets/DatabaseSettingsDialog.h"
#include "ui_databasesettingsdialog.h"
#include <QMessageBox>
#include <QSqlError>

#include <QDebug>

DatabaseSettingsDialog::DatabaseSettingsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseSettingsDialog), m_dbManager(DatabaseManager::instance())
{
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    ui->sqlDriversComboBox->addItems(DatabaseManager::drivers());
    initSlots();

    ui->removeConnectionButton->setEnabled(false);

    foreach (DatabaseManager::SQLConnection* conn, m_dbManager->connections()) {
        QListWidgetItem* connectionNameItem = new QListWidgetItem(conn->name);
        ui->sqlConnectionsListWidget->addItem(connectionNameItem);
    }
}

DatabaseSettingsDialog::~DatabaseSettingsDialog()
{
    delete ui;
    delete m_dbManager;
}

bool DatabaseSettingsDialog::canAddNewConnection() const
{
    return !ui->userNameLineEdit->text().isEmpty() &&
            !ui->hostLineEdit->text().isEmpty() &&
            !ui->passwordLineEdit->text().isEmpty() &&
            !ui->portLineEdit->text().isEmpty() &&
            (ui->sqlDriversComboBox->currentIndex() != -1);
}

void DatabaseSettingsDialog::initSlots()
{
    connect(ui->addNewConnectionButton, &QPushButton::clicked, this, &DatabaseSettingsDialog::addConnection);
    connect(ui->removeConnectionButton, &QPushButton::clicked, this, &DatabaseSettingsDialog::removeConnection);
    connect(ui->testConnectionButton, &QPushButton::clicked, this, &DatabaseSettingsDialog::testConnection);

    connect(ui->connectionNameLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::connectionNameChanged);
    connect(ui->hostLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::hostChanged);
    connect(ui->portLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::portChanged);
    connect(ui->sqlDriversComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DatabaseSettingsDialog::driverChanged);
    connect(ui->userNameLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::userNameChanged);
    connect(ui->passwordLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::passwordChanged);

    connect(ui->sqlConnectionsListWidget, &QListWidget::currentRowChanged, this, &DatabaseSettingsDialog::connectionSelectionChanged);

    connect(m_dbManager, &DatabaseManager::testDatabaseNotOpened, this, &DatabaseSettingsDialog::testDatabaseNotOpened);
    connect(m_dbManager, &DatabaseManager::testDatabaseNotValid, this, &DatabaseSettingsDialog::testDatabaseNotValid);
    connect(m_dbManager, &DatabaseManager::testDatabaseOk, this, &DatabaseSettingsDialog::testDatabaseOk);
}

void DatabaseSettingsDialog::testDatabaseNotOpened()
{
    QMessageBox::warning(0, "Database testing error!", "Database not opened!");
}

void DatabaseSettingsDialog::testDatabaseNotValid()
{
    QMessageBox::warning(0, "Database testing error!", "Database not valid!");
}

void DatabaseSettingsDialog::testDatabaseOk()
{
    QMessageBox::information(0, "Database testing ok!", "Database opened!");
}

void DatabaseSettingsDialog::addConnection()
{
    if (!canAddNewConnection())
    {
        QMessageBox::warning(0, "Cannot add new connection!","Error, cannot add new connection!");
        return;
    }

    DatabaseManager::SQLConnection* conn = new DatabaseManager::SQLConnection;
    conn->name = ui->connectionNameLineEdit->text();
    conn->port = ui->portLineEdit->text().toInt();
    conn->password = ui->passwordLineEdit->text();
    conn->userName = ui->userNameLineEdit->text();
    conn->vendorIndex = ui->sqlDriversComboBox->currentIndex();
    conn->hostName = ui->hostLineEdit->text();

    //conn->dbName

    m_dbManager->addConnection(conn);
    QListWidgetItem* newConnectionItem = new QListWidgetItem(conn->name);
    newConnectionItem->setSelected(true);
    ui->sqlConnectionsListWidget->addItem(newConnectionItem);

    if (!ui->removeConnectionButton->isEnabled())
    {
        ui->removeConnectionButton->setEnabled(true);
    }

    m_dbManager->currentConnectionChanged(ui->sqlConnectionsListWidget->currentRow());
}

void DatabaseSettingsDialog::driverChanged(const int index)
{
    if (index != -1)
    {
        m_dbManager->driverChanged(index);
    }
}

void DatabaseSettingsDialog::removeConnection()
{
    const int index = ui->sqlConnectionsListWidget->currentRow();
    if (index != -1)
    {
        qDebug() << "indexToRemove: " << QString::number(index);
        m_dbManager->deleteConnection(index);
        qDebug() << "count: " << QString::number(ui->sqlConnectionsListWidget->count());
        qDebug() << "connectionsCountAfterDelete: " << QString::number(m_dbManager->connections().size());
        delete ui->sqlConnectionsListWidget->item(index);

        if (m_dbManager->connections().size() == 0)
        {
            ui->removeConnectionButton->setEnabled(false);
        }
    }
}

void DatabaseSettingsDialog::testConnection()
{
    if (!canAddNewConnection())
    {
        return;
    }

    if (ui->sqlConnectionsListWidget->count() == 0)
    {
        DatabaseManager::SQLConnection* connectionToTest = new DatabaseManager::SQLConnection;
        m_dbManager->testConnection(connectionToTest);
    }
    else
    {
        if (ui->sqlConnectionsListWidget->currentRow() != -1)
        {
            m_dbManager->testConnection(ui->sqlConnectionsListWidget->currentRow());
        }
    }
}

void DatabaseSettingsDialog::connectionSelectionChanged(int index)
{
    if (index != -1)
    {
        m_dbManager->currentConnectionChanged(index);

        DatabaseManager::SQLConnection* conn = m_dbManager->connections().at(index);

        ui->userNameLineEdit->setText(conn->userName);
        ui->passwordLineEdit->setText(conn->password);
        ui->sqlDriversComboBox->setCurrentIndex(conn->vendorIndex);
        ui->connectionNameLineEdit->setText(conn->name);
        ui->portLineEdit->setText(QString::number(conn->port));
        ui->hostLineEdit->setText(conn->hostName);
    }
}

void DatabaseSettingsDialog::hostChanged(const QString& newHost)
{
    m_dbManager->hostChanged(newHost);
}

void DatabaseSettingsDialog::portChanged(const QString &newPort)
{
    m_dbManager->portChanged(newPort.toInt());
}

void DatabaseSettingsDialog::connectionNameChanged(const QString &newName)
{
    m_dbManager->connectionNameChanged(newName);
}

void DatabaseSettingsDialog::userNameChanged(const QString &newUserName)
{
    m_dbManager->userNameChanged(newUserName);
}

void DatabaseSettingsDialog::passwordChanged(const QString &newPassword)
{
    m_dbManager->passwordChanged(newPassword);
}
