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
#include "DatabaseManager.h"
#include <QApplication>
#include <QtSql>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent),
    m_databaseConnectionsFile(QApplication::applicationDirPath().left(1) + ":/dbConnections.ini")
{
    loadConnections();
}

DatabaseManager::~DatabaseManager()
{
    saveConnections();
}

QStringList DatabaseManager::drivers()
{
    return QSqlDatabase::drivers();
}

QVector<DatabaseManager::SQLConnection *> DatabaseManager::connections() const
{
    return m_connections;
}

QSqlError DatabaseManager::connect(const int connectionIndex)
{
    return QSqlError();
}

QSqlError DatabaseManager::testConnection(const int connectionIndex)
{
    return QSqlError();
}

QSqlError DatabaseManager::testConnection(SQLConnection* conn)
{
    return QSqlError();
}

QSqlError DatabaseManager::deleteConnection(const int connectionIndex)
{
    return QSqlError();
}

bool DatabaseManager::addConnection(const SQLConnection* conn)
{
    return false;
}

QSqlError DatabaseManager::initDb()
{
    return QSqlError();
}

void DatabaseManager::saveConnections() const
{
    QSettings connectionSetting(m_databaseConnectionsFile, QSettings::NativeFormat);

    connectionSetting.beginWriteArray(QLatin1String("Connections"));

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

    connectionSetting.endArray();

}

void DatabaseManager::loadConnections()
{
    QSettings connectionSetting(m_databaseConnectionsFile, QSettings::NativeFormat);

    const int savedConnectionsSize = connectionSetting.beginReadArray(QLatin1String("Connections"));
    m_connections.reserve(savedConnectionsSize);
    m_connections.resize(savedConnectionsSize);
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

        m_connections[i] = conn;
    }
    connectionSetting.endArray();;
}

void DatabaseManager::currentConnectionChanged(const int index)
{
    m_currentConnectionIndex = index;
}

void DatabaseManager::driverChanged(const int index)
{

}

void DatabaseManager::hostChanged(const QString& newHost)
{

}

void DatabaseManager::portChanged(const QString& newPort)
{

}

void DatabaseManager::connectionNameChanged(const QString &newName)
{

}

void DatabaseManager::userNameChanged(const QString &newUserName)
{

}

void DatabaseManager::passwordChanged(const QString &newPassword)
{

}