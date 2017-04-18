/***************************************************************************
    File                 : Utils.cpp
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
#include "Utils.h"

QImage Utils::Mat2QImage(const cv::Mat & src) {
  cv::Mat temp;
  cv::cvtColor(src, temp, CV_BGR2RGB);
  QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
  dest.bits();
  return dest;
}
cv::Mat Utils::QImage2Mat(const QImage & src) {
  cv::Mat tmp(src.height(), src.width(), CV_8UC3, (uchar*)src.bits(), src.bytesPerLine());
  cv::Mat result;
  cv::cvtColor(tmp, result, CV_RGB2BGR);
  return result;
}

QString Utils::videoLengthFormatted(int milliseconds)
{
    QString lengthFormatted;

    int seconds  = milliseconds/ 1000;
    milliseconds %= 1000;
    int minutes  = seconds / 60;
    seconds  %= 60;
    int hours  = minutes/ 60;
    minutes  %= 60;

    lengthFormatted.append(QString("%1").arg(hours, 2, 10, QLatin1Char('0')) + ":" +
                           QString( "%1" ).arg(minutes, 2, 10, QLatin1Char('0')) + ":" +
                           QString( "%1" ).arg(seconds, 2, 10, QLatin1Char('0')) + ":" +
                           QString( "%1" ).arg(milliseconds, 3, 10, QLatin1Char('0')));
    return lengthFormatted;
}


