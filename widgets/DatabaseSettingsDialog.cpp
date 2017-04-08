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
#include "DatabaseSettingsDialog.h"
#include "ui_databasesettingsdialog.h"

DatabaseSettingsDialog::DatabaseSettingsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseSettingsDialog), m_dbManager(new DatabaseManager)
{
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    initSlots();
}

DatabaseSettingsDialog::~DatabaseSettingsDialog()
{
    delete ui;
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
}

void DatabaseSettingsDialog::addConnection()
{

}

void DatabaseSettingsDialog::driverChanged(const int index)
{

}

void DatabaseSettingsDialog::removeConnection()
{

}

void DatabaseSettingsDialog::testConnection()
{

}

void DatabaseSettingsDialog::connectionSelectionChanged(const int index)
{

}

void DatabaseSettingsDialog::hostChanged(const QString& newHost)
{

}

void DatabaseSettingsDialog::portChanged(const QString &newPort)
{

}

void DatabaseSettingsDialog::connectionNameChanged(const QString &newName)
{

}

void DatabaseSettingsDialog::userNameChanged(const QString &newUserName)
{

}

void DatabaseSettingsDialog::passwordChanged(const QString &newPassword)
{

}
