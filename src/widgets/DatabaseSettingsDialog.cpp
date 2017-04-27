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

    const DatabaseManager::SQLConnection* conn = m_dbManager->connection();
    ui->dbNameLineEdit->setText(conn->dbName);
    ui->connectionNameLineEdit->setText(conn->name);
    ui->portLineEdit->setText(QString::number(conn->port));
    ui->hostLineEdit->setText(conn->hostName);
    ui->passwordLineEdit->setText(conn->password);
    ui->userNameLineEdit->setText(conn->userName);
    ui->sqlDriversComboBox->setCurrentIndex(conn->vendorIndex);

    initSlots();
}

void DatabaseSettingsDialog::setConnectedAlready(bool connected)
{
    m_connecedAlready = connected;
}

DatabaseSettingsDialog::~DatabaseSettingsDialog()
{
    delete ui;
    delete m_dbManager;
}

void DatabaseSettingsDialog::initSlots()
{
    connect(ui->testConnectionButton, &QPushButton::clicked, this, &DatabaseSettingsDialog::testConnection);
    connect(ui->connectToDatabaseButton, &QPushButton::clicked, this, &DatabaseSettingsDialog::connectToDatabase);

    connect(ui->connectionNameLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::connectionNameChanged);
    connect(ui->hostLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::hostChanged);
    connect(ui->portLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::portChanged);
    connect(ui->sqlDriversComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DatabaseSettingsDialog::driverChanged);
    connect(ui->userNameLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::userNameChanged);
    connect(ui->passwordLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::passwordChanged);
    connect(ui->dbNameLineEdit, &QLineEdit::textEdited, this, &DatabaseSettingsDialog::dbNameChanged);

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

void DatabaseSettingsDialog::driverChanged(const int index)
{
    if (index != -1)
    {
        m_dbManager->driverChanged(index);
    }
}

void DatabaseSettingsDialog::dbNameChanged(const QString &newName)
{
    m_dbManager->dbNameChanged(newName);
}

void DatabaseSettingsDialog::connectToDatabase()
{
    QPalette palette;


    if (m_dbManager->connect().type() == QSqlError::NoError)
    {
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
    }
    else
    {
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
    }

    QBrush brush1(QColor(0, 0, 0, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);

    ui->connectionStatusButton->setText(QLatin1String("Connected"));
    ui->connectionStatusButton->setPalette(palette);
}

void DatabaseSettingsDialog::testConnection()
{
    DatabaseManager::SQLConnection* connectionToTest = new DatabaseManager::SQLConnection;
    connectionToTest->dbName = ui->dbNameLineEdit->text();
    connectionToTest->vendorIndex = ui->sqlDriversComboBox->currentIndex();

    m_dbManager->testConnection(connectionToTest);
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
