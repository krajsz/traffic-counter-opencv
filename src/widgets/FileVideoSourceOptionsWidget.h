/***************************************************************************
    File                 : FileVideoSourceOptionsWidget.h
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
#ifndef FILEVIDEOSOURCEOPTIONSWIDGET_H
#define FILEVIDEOSOURCEOPTIONSWIDGET_H

#include <QWidget>
#include "ui_filevideosourceoptionswidget.h"
#include "src/widgets/FileInfoDialog.h"

class FileVideoSourceOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileVideoSourceOptionsWidget(QWidget *parent = 0);
    ~FileVideoSourceOptionsWidget();

    bool ok() const;

    void setFilePath(const QString& path);

    QString filePath() const;
Q_SIGNALS:
    void fileOpened(bool ok);
private:
    Ui::FileVideoSourceOptionsWidget *ui;

    QString m_guiSettingsFile;
public Q_SLOTS:
    void openFile();

private Q_SLOTS:
    void showFileInfoDialog();
};

#endif // FILEVIDEOSOURCEOPTIONSWIDGET_H
