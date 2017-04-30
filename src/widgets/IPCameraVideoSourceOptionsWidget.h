/***************************************************************************
    File                 : IPCameraVideoSourceOptionsWidget.h
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
#ifndef IPCAMERAVIDEOSOURCEOPTIONS_H
#define IPCAMERAVIDEOSOURCEOPTIONS_H

#include <QWidget>
#include "ui_ipcameravideosourceoptions.h"

class IPCameraVideoSourceOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IPCameraVideoSourceOptionsWidget(QWidget *parent = 0);
    ~IPCameraVideoSourceOptionsWidget();

    QString url() const;
    QString userName() const;
    QString password() const;
    int port() const;

    bool ok();

    bool urlContainsEverything() const;

private:
    Ui::IPCameraVideoSourceOptions *ui;
private Q_SLOTS:
    void urlContainsEverythingChecked(bool checked);
    bool testButtonClicked();
    void enableButtonTest(const QString& newUrl);
};

#endif // IPCAMERAVIDEOSOURCEOPTIONS_H
