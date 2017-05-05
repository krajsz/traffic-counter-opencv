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
#include <QVector>

#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent),
    m_databaseConnectionsFile(QApplication::applicationDirPath() + "/dbConnection.ini"),
    m_connection(new DatabaseManager::SQLConnection)
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

void DatabaseManager::setNodeId(const int id)
{
    m_nodeId = id;
}

DatabaseManager::SQLConnection * DatabaseManager::connection() const
{
    return m_connection;
}

void DatabaseManager::newObservation(const int cpm, const QDateTime &time)
{
    QSqlQuery q;
    q.prepare("insert into traffic_observations (cpm, date_of_observation, node_id) values (?, ?, ?)");
    q.addBindValue(cpm);
    q.addBindValue(time);
    q.addBindValue(m_nodeId);
    q.exec();
}

QSqlError DatabaseManager::connect()
{
    QStringList dbs = DatabaseManager::drivers();

    m_database = QSqlDatabase::addDatabase(dbs.at(m_connection->vendorIndex));
    m_database.setDatabaseName(m_connection->dbName);
    m_database.setHostName(m_connection->hostName);
    m_database.setPort(m_connection->port);
    qDebug() << "Connecting to database..";

    if (m_database.open())
    {
        if (initDb())
        {
            m_connected = true;
            qDebug() << "Connected to database!";
        }
        else
        {
            m_connected = false;
            qDebug() << "Unable to create traffic_observations table!";
        }
        return QSqlError();
    }
    else
    {
        m_connected = false;
        qDebug() << "Failed to connect to database!";

        return m_database.lastError();
    }
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

QString DatabaseManager::nodeId() const
{
    return m_nodeId;
}

bool DatabaseManager::connected() const
{
    return m_connected;
}

bool DatabaseManager::initDb()
{
    QStringList tables = m_database.tables();
    QSqlQuery q;

    if (!tables.contains("traffic_observations", Qt::CaseInsensitive))
    {
        bool ct = q.exec("create table traffic_observations (id integer primary key, cpm integer, date_of_observation date, node_id varchar2)");
        if (!ct)
            return false;
    }

    return true;
}

void DatabaseManager::saveConnection() const
{
    QSettings connectionSetting(m_databaseConnectionsFile, QSettings::NativeFormat);
    connectionSetting.setValue(QLatin1String("connectionName"), m_connection->name);
    connectionSetting.setValue(QLatin1String("dbName"), m_connection->dbName);
    connectionSetting.setValue(QLatin1String("driver"), m_connection->vendorIndex);
    connectionSetting.setValue(QLatin1String("port"), m_connection->port);
    connectionSetting.setValue(QLatin1String("hostName"), m_connection->hostName);
    connectionSetting.setValue(QLatin1String("userName"), m_connection->userName);
    connectionSetting.setValue(QLatin1String("password"), m_connection->password);
    connectionSetting.setValue(QLatin1String("wayId"), m_nodeId);

}

void DatabaseManager::loadConnection()
{
    QSettings connectionSetting(m_databaseConnectionsFile, QSettings::NativeFormat);

    qDebug() << "Loading database connection..";

    SQLConnection* conn = new SQLConnection;
    conn->name = connectionSetting.value(QLatin1String("connectionName")).toString();
    conn->dbName = connectionSetting.value(QLatin1String("dbName")).toString();
    conn->hostName = connectionSetting.value(QLatin1String("hostName")).toString();
    conn->port = connectionSetting.value(QLatin1String("port")).toInt();
    conn->vendorIndex = connectionSetting.value(QLatin1String("driver")).toInt();
    conn->userName = connectionSetting.value(QLatin1String("userName")).toString();
    conn->password = connectionSetting.value(QLatin1String("password")).toString();
    m_nodeId = connectionSetting.value(QLatin1String("wayId")).toString();


    qDebug() << conn->name << " " << conn->dbName;
    m_connection = conn;
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

void DatabaseManager::nodeIdChanged(const QString &newId)
{
    m_nodeId = newId;
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
