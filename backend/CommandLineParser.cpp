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
#include "CommandLineParser.h"
#include <QDir>

CommandLineParser::CommandLineParser(QObject *parent) : QObject(parent),
    m_fileNameSet(false), m_showGui(true), m_record(false)
{
    m_optionsParser.addHelpOption();
    m_optionsParser.addVersionOption();

    QCommandLineOption noGuiOption(QLatin1String("nogui"),
                             "Don't show the GUI.");

    QCommandLineOption recordOption(QStringList() << QLatin1String("r") << QLatin1String("record"),
                                    "Record the video.");


    QCommandLineOption fileNameOption(QStringList() << QLatin1String("f") <<
                                        QLatin1String("filename"),"Input file name");

    m_optionsParser.addOption(noGuiOption);
    m_optionsParser.addOption(recordOption);
    m_optionsParser.addOption(fileNameOption);
}

void CommandLineParser::parse(const QCoreApplication& app)
{
    m_optionsParser.process(app);

    //noGui
    if(m_optionsParser.isSet(QLatin1String("nogui")))
    {
        m_showGui = false;
    }

    //record
    if (m_optionsParser.isSet(QLatin1String("record")))
    {
        m_record = true;
    }

    //filename

    if (m_optionsParser.isSet(QLatin1String("filename")))
    {
        const QString path = m_optionsParser.value(QLatin1String("filename"));
        const QString dir = path.left(path.lastIndexOf('\\'));
        if(QDir(dir).exists())
        {
            m_fileNameSet = true;
        }
    }

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
