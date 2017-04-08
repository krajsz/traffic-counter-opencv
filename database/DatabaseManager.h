/***************************************************************************
    File                 : DatabaseManager.h
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
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSettings>
#include <QVector>
#include <QtSql/QSqlDatabase>
class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();
    struct SQLConnection {
        int vendorIndex;
        int port;
        QString name;
        QString hostName;
        QString dbName;
        QString userName;
        QString password;
    };

    static QStringList drivers();

    QSqlError connect(const int connectionIndex);

    QSqlError initDb();

    QVector<SQLConnection> connections() const;
private:
    QVector<SQLConnection> m_connections;
    QString m_databaseConnectionsFile;
    void saveConnections() const;
    void loadConnections();

signals:

public slots:
};

#endif // DATABASEMANAGER_H
