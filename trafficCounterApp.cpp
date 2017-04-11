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
#include "widgets/TrafficCounterMainWindow.h"
#include "backend/CommandLineParser.h"

#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("TrafficCounter");
    QCoreApplication::setOrganizationName("University of Debrecen");
    QCoreApplication::setApplicationVersion("1.0");
    QCoreApplication::setOrganizationDomain("http://inf.unideb.hu");

    CommandLineParser commandLineParser;
    commandLineParser.parse(a);

    TrafficCounterMainWindow* win;
    if (commandLineParser.showGui())
    {
        //show gui
        win =  new TrafficCounterMainWindow;
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
