/***************************************************************************
    File                 : CommandLineParser.h
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
#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QObject>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QVector>
#include <QSocketNotifier>

namespace Cli
{
class CommandLineParser : public QObject
{
    Q_OBJECT
public:
    explicit CommandLineParser(QObject *parent = 0);
    bool showGui() const;
    bool fileNameSet() const;
    bool record() const;
    bool webcamSourceSet() const;

    QString fileName() const;
    int webcamIdx() const;
    void parse(const QCoreApplication &app);
private:
    QCommandLineParser m_optionsParser;

    bool m_fileNameSet;
    bool m_webcamIdxSet;
    bool m_record;
    bool m_showGui;

    int m_webcamIdx;

    QString m_previousCommand;

    const QLatin1String COMMAND_START = QLatin1String("start");
    const QLatin1String COMMAND_PAUSE = QLatin1String("pause");
    const QLatin1String COMMAND_STOP = QLatin1String("stop");
    const QLatin1String COMMAND_NEW_SOURCE = QLatin1String("new");
    const QLatin1String COMMAND_CAMERA = QLatin1String("camera");
    const QLatin1String COMMAND_FILE = QLatin1String("file");

    QSocketNotifier m_stdinNotifier;

Q_SIGNALS:

    void start();
    void stop();
    void pause();
    void resume();
    void newFileSource(const QString& path);
    void newCameraSource(const int idx);

public Q_SLOTS:

private Q_SLOTS:
    void stdinInputReceived();
};
}
#endif // COMMANDLINEPARSER_H
