/***************************************************************************
    File                 : VideoRecorder.cpp
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
#include "VideoRecorder.h"
#include <QStandardPaths>
#include <QDir>

VideoRecorder::VideoRecorder(QObject *parent) : QThread(parent),
    m_filePath(QStandardPaths::writableLocation(QStandardPaths::PicturesLocation))
{
}

void VideoRecorder::setFilePath(const QString &path)
{
    m_filePath = path;
}

void VideoRecorder::stopRecording()
{

}

void VideoRecorder::startRecording()
{
    const QString dir = m_filePath.left(m_filePath.lastIndexOf('\\'));
    if(QDir(dir).exists())
    {

    }
}
