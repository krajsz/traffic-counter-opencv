/***************************************************************************
    File                 : FileVideoSource.h
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
#ifndef FILEVIDEOSOURCE_H
#define FILEVIDEOSOURCE_H

#include "src/videosources/AbstractVideoSource.h"

class FileVideoSource : public AbstractVideoSource
{
    Q_OBJECT
public:
    FileVideoSource(const QString& path, QObject* parent = nullptr);

    struct VideoInfo
    {
        double fps;
        int frameCount;
        QString lenghtFormatted;
        QSize frameSize;
    };

    VideoInfo infos() const;
    void setInfos(const VideoInfo& info);
private:

    VideoInfo m_infos;

};

#endif // FILEVIDEOSOURCE_H
