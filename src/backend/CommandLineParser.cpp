/***************************************************************************
    File                 : CommandLineParser.cpp
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
#include "src/backend/CommandLineParser.h"
#include <unistd.h>

#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QTextStream>
namespace Cli
{

CommandLineParser::CommandLineParser(QObject *parent) : QObject(parent),
    m_fileNameSet(false), m_showGui(true), m_record(false),
    m_stdinNotifier(STDIN_FILENO, QSocketNotifier::Read)
{
    m_optionsParser.addHelpOption();
    m_optionsParser.addVersionOption();

    QCommandLineOption noGuiOption(QLatin1String("nogui"),
                                   "Don't show the GUI.");

    QCommandLineOption recordOption(QStringList() << QLatin1String("r") << QLatin1String("record"),
                                    "Record the video.");

    QCommandLineOption cameraOption(QStringList() << QLatin1String("w") << QLatin1String("webcam"),
                                    "Set the input camera.");


    QCommandLineOption fileNameOption(QStringList() << QLatin1String("f") <<
                                      QLatin1String("filename"),"Input file name",
                                      QLatin1String("filename"));

    m_optionsParser.addOption(noGuiOption);
    m_optionsParser.addOption(recordOption);
    m_optionsParser.addOption(fileNameOption);
    m_optionsParser.addOption(cameraOption);

}

void CommandLineParser::parse(const QCoreApplication& app)
{
    m_optionsParser.process(app);

    //noGui
    if(m_optionsParser.isSet(QLatin1String("nogui")))
    {
        m_showGui = false;
        connect(&m_stdinNotifier, &QSocketNotifier::activated, this, &CommandLineParser::stdinInputReceived);
        m_stdinNotifier.setEnabled(true);
    }

    //record
    if (m_optionsParser.isSet(QLatin1String("record")))
    {
        m_record = true;
    }

    //filename

    if (m_optionsParser.isSet(QLatin1String("filename")))
    {
        const QString filepath = m_optionsParser.value(QLatin1String("filename"));

        if(QFileInfo(filepath).exists())
        {
            m_fileNameSet = true;
        }
        else
        {
            qDebug() << "Incorrect file path!";

            m_optionsParser.showHelp(1);
        }
    }

}

void CommandLineParser::stdinInputReceived()
{
    QTextStream strin(stdin);
    qDebug() << "command: " << strin.readLine();

    //pause, resume, new file, show gui
}

int CommandLineParser::webcamIdx() const
{
    return m_webcamIdx;
}

bool CommandLineParser::webcamSourceSet() const
{

}

QString CommandLineParser::fileName() const
{
    if (fileNameSet())
    {
        return m_optionsParser.value(QLatin1String("filename"));
    }
    else
    {
        return QString();
    }
}

bool CommandLineParser::showGui() const
{
    return m_showGui;
}

bool CommandLineParser::fileNameSet() const
{
    return m_fileNameSet;
}

bool CommandLineParser::record() const
{
    return m_record;
}

}
