/***************************************************************************
    File                 : FrameProcessor.cpp
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
#include "src/backend/FrameProcessor.h"
#include "src/backend/Utils.h"

#include "3rdparty/package_bgs/FrameDifference.h"

#include <QDebug>

FrameProcessor::FrameProcessor(QObject *parent) : QObject(parent),
    m_backgroundSubstractor(new FrameDifference)
{
    m_backgroundSubstractor->setShowOutput(false);
}

void FrameProcessor::process(const cv::Mat &frame)
{
    cv::Mat fr;
    m_backgroundSubstractor->process(frame, fr, m_background);
    fr.copyTo(m_foreground);
    fr.release();

    emit frameProcessed(m_foreground);

    postProcess();
}

void FrameProcessor::postProcess()
{

}

cv::Mat FrameProcessor::backgroundMat() const
{
    return m_background;
}

QImage FrameProcessor::foregroundQImage() const
{
    return Utils::Mat2QImage(m_foreground);
}

cv::Mat FrameProcessor::foregroundMat() const
{
    return m_foreground;
}
