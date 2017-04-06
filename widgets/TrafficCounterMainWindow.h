/***************************************************************************
    File                 : TrafficCounterMainWindow.h
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
#ifndef TRAFFICCOUNTERMAIN_H
#define TRAFFICCOUNTERMAIN_H

#include <QMainWindow>

namespace Ui {
class TrafficCounterMainWindow;
}

class TrafficCounterMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrafficCounterMainWindow(QWidget *parent = 0);
    ~TrafficCounterMainWindow();

private:
    Ui::TrafficCounterMainWindow *ui;
protected:
    void keyPressEvent(QKeyEvent*);
    void closeEvent(QCloseEvent*);
};

#endif // TRAFFICCOUNTERMAIN_H
