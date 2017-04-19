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
#ifndef FILEVIDEOSOURCEPROGRESSBAR_H
#define FILEVIDEOSOURCEPROGRESSBAR_H

#include <QTimer>
#include <QProgressBar>

class FileVideoSourceProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    /*!
     * \brief FileVideoSourceProgressBar's construcor.
     * Constructs a FileVideoSourceProgressBar.
     * \param parent
     */
    explicit FileVideoSourceProgressBar(QWidget *parent = 0);

    /*!
     * \brief FileVideoSourceProgressBar's destructor.
     * Destructs this object.
     */
    ~FileVideoSourceProgressBar();
signals:

public Q_SLOTS:
    /*!
     * \brief setText
     * Sets the QProgressBar's display text to text.
     * \param text the text to be set as the QProgressBar's text.
     * \sa text()
     */
    void setText(const QString& text);

protected:

    /*!
     * \brief FileVideoSourceProgressBar::text
     *  Returns m_text as the QProgressBar's text, this is used by the QProgressBar itself.
     * \return
     */
    QString text() const;
private:
    /*!
     * \brief The text to be shown on the QProgressBar.
     */
    QString m_text;

    /*!
     * \brief QTimer which updates the QProgressBar.
     */
    QTimer* m_updateProgressTimer;
};

#endif // FILEVIDEOSOURCEPROGRESSBAR_H
