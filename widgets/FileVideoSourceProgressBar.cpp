/***************************************************************************
    File                 : FileVideoSourceProgressBar.cpp
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
#include "FileVideoSourceProgressBar.h"
#include <QDebug>

FileVideoSourceProgressBar::FileVideoSourceProgressBar(QWidget *parent) : QProgressBar(parent),
    m_updateProgressTimer(new QTimer)
{
    setRange(0, 1000);
    connect(m_updateProgressTimer, SIGNAL(timeout()), this, SLOT(update()));

    m_updateProgressTimer->start(50);
}

void FileVideoSourceProgressBar::setText(const QString &text)
{
    m_text = text;
}

QString FileVideoSourceProgressBar::text() const
{
    return m_text;
}
