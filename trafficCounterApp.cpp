/***************************************************************************
    File                 : trafficCounterApp.cpp
    Project              : TrafficCounter
    Description          : Main function
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

#include <QApplication>
#include "src/widgets/TrafficCounterMainWindow.h"
#include "src/backend/CommandLineParser.h"
#include <QDir>

#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qRegisterMetaType<cv::Mat>("cv::Mat");


    // config directory needed by BGSLib
    QDir configDirForBGS (QDir::current().path() + QLatin1String("/config"));

    if (!configDirForBGS.exists())
    {
        QDir createConfigDir (QDir::current().path());
        createConfigDir.mkdir(QLatin1String("./config"));
    }

    QCoreApplication::setApplicationName("TrafficCounter");
    QCoreApplication::setOrganizationName("University of Debrecen");
    QCoreApplication::setApplicationVersion("0.1");
    QCoreApplication::setOrganizationDomain("http://inf.unideb.hu");

    Cli::CommandLineParser commandLineParser;
    commandLineParser.parse(a);

    TrafficCounterMainWindow* win;
    TrafficCounterController* trafficCounterController = new TrafficCounterController;
    if (commandLineParser.showGui())
    {
        //show gui
        win =  new TrafficCounterMainWindow;
        win->setController(trafficCounterController);
        win->show();
    }
    else
    {
        //nogui, controller
    }

    if (commandLineParser.fileNameSet())
    {

    }

    if (commandLineParser.record())
    {

    }

    return a.exec();
}
