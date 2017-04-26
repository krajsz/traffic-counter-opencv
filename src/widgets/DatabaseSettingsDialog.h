/***************************************************************************
    File                 : DatabaseSettingsDialog.h
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
#ifndef DATABASESETTINGSDIALOG_H
#define DATABASESETTINGSDIALOG_H

#include <QWidget>
#include "src/backend/database/DatabaseManager.h"

namespace Ui {
class DatabaseSettingsDialog;
}

class DatabaseSettingsDialog : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseSettingsDialog(QWidget *parent = 0);
    ~DatabaseSettingsDialog();

    void setConnectedAlready(bool connected);

private:
    Ui::DatabaseSettingsDialog *ui;

    void initSlots();
    bool m_connecedAlready;

    DatabaseManager* m_dbManager;
private Q_SLOTS:
    void testConnection();
    void connectToDatabase();

    void testDatabaseNotOpened();
    void testDatabaseNotValid();
    void testDatabaseOk();

    void driverChanged(const int index);
    void dbNameChanged(const QString& newName);
    void hostChanged(const QString& newHost);
    void portChanged(const QString& newPort);
    void connectionNameChanged(const QString &newName);
    void userNameChanged(const QString &newUserName);
    void passwordChanged(const QString &newPassword);
};

#endif // DATABASESETTINGSDIALOG_H
