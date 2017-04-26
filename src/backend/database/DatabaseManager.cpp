/***************************************************************************
    File                 : DatabaseManager.cpp
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
#include "src/backend/database/DatabaseManager.h"
#include <QApplication>
#include <QtSql>
#include <QDebug>
#include <QVector>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent),
    m_databaseConnectionsFile(QApplication::applicationDirPath() + "/dbConnections.ini")
{
    loadConnection();
}

DatabaseManager::~DatabaseManager()
{
    saveConnection();
}

QStringList DatabaseManager::drivers()
{
    return QSqlDatabase::drivers();
}

DatabaseManager::SQLConnection * DatabaseManager::connection() const
{
    return m_connection;
}

QSqlError DatabaseManager::connect()
{
    return QSqlError();
}

void DatabaseManager::testConnection(SQLConnection* conn)
{
    QStringList drivers = DatabaseManager::drivers();

    QSqlDatabase database = QSqlDatabase::addDatabase(drivers.at(conn->vendorIndex));
    database.setDatabaseName(conn->dbName);

    if (database.isValid())
    {
        if (database.open())
        {
            if (database.isOpen())
            {
                database.close();
                emit testDatabaseOk();
            }
        }
        else
        {
            qDebug() << database.lastError().text();
            emit testDatabaseNotOpened();
        }
    }
    else
    {
        emit testDatabaseNotValid();
    }
}

QSqlError DatabaseManager::initDb()
{

    QStringList drivers = DatabaseManager::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase(drivers.at(m_connection->vendorIndex));
    db.setDatabaseName(m_connection->name);

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("books", Qt::CaseInsensitive))
    {


        return QSqlError();
    }

    return QSqlError();
}

void DatabaseManager::saveConnection() const
{
    /*QSettings connectionSetting(m_databaseConnectionsFile, QSettings::NativeFormat);

    connectionSetting.begin(QLatin1String("Connections"));
    for(int i = 0; i < m_connections.size(); ++i)
    {
        connectionSetting.setArrayIndex(i);
        SQLConnection* conn = m_connections.at(i);
        connectionSetting.setValue(QLatin1String("connectionName"), conn->name);
        connectionSetting.setValue(QLatin1String("databaseName"), conn->dbName);
        connectionSetting.setValue(QLatin1String("driver"), conn->vendorIndex);
        connectionSetting.setValue(QLatin1String("port"), conn->port);
        connectionSetting.setValue(QLatin1String("hostName"), conn->hostName);
        connectionSetting.setValue(QLatin1String("userName"), conn->userName);
        connectionSetting.setValue(QLatin1String("password"), conn->password);
    }

    connectionSetting.endArray();*/
}

void DatabaseManager::loadConnection()
{
    /*QSettings connectionSetting(m_databaseConnectionsFile, QSettings::NativeFormat);

    const int savedConnectionsSize = connectionSetting.beginReadArray(QLatin1String("Connections"));

    m_connections.reserve(savedConnectionsSize);
    for(int i = 0; i < savedConnectionsSize; ++i)
    {
        connectionSetting.setArrayIndex(i);
        SQLConnection* conn = new SQLConnection;
        conn->name = connectionSetting.value(QLatin1String("connectionName"), QLatin1String("NoConnectionName")).toString();
        conn->dbName = connectionSetting.value(QLatin1String("databaseName"), QLatin1String("NoDatabaseName")).toString();
        conn->hostName = connectionSetting.value(QLatin1String("hostName"), QLatin1String("")).toString();
        conn->port = connectionSetting.value(QLatin1String("port")).toInt();
        conn->vendorIndex = connectionSetting.value(QLatin1String("driver")).toInt();
        conn->userName = connectionSetting.value(QLatin1String("userName")).toString();
        conn->password = connectionSetting.value(QLatin1String("password")).toString();

        m_connections.append(conn);
    }
    connectionSetting.endArray();*/
}

void DatabaseManager::driverChanged(const int index)
{
    m_connection->vendorIndex = index;
}

void DatabaseManager::hostChanged(const QString& newHost)
{
    m_connection->hostName = newHost;
}

void DatabaseManager::portChanged(const int& newPort)
{
    m_connection->port = newPort;
}

void DatabaseManager::connectionNameChanged(const QString &newName)
{
    m_connection->name = newName;
}

void DatabaseManager::userNameChanged(const QString &newUserName)
{
    m_connection->userName = newUserName;
}

void DatabaseManager::passwordChanged(const QString &newPassword)
{
    m_connection->password = newPassword;
}

void DatabaseManager::dbNameChanged(const QString &newName)
{
    m_connection->dbName = newName;
}

DatabaseManager* DatabaseManager::ptr = 0;

DatabaseManager* DatabaseManager::instance()
{
    if (ptr == nullptr)
    {
        ptr = new DatabaseManager;
    }

    return ptr;
}
