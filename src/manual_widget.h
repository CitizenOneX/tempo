/*
 * TEMPO - Topographic Eeg Mapping PrOgram.
 * 
 * Copyright (C) 1995, 1996, 2003, 2004, 2005, 2007 Aleksandar
 * Samardzic
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301
 * USA
 */

//!\file manual_widget.h
//!Declaration of ManualWidget class.

#ifndef MANUAL_WIDGET_H
#define MANUAL_WIDGET_H 1

#include <QtCore>
#include <QtGui>

//! On-line manual widget.
/*!
 * This class represents widget intended to display program manual.
 */
class ManualWidget : public QWidget
{
        Q_OBJECT

 public:
        /*!
         * Construct an object of ManualWidget class given parent
         * widget.
         */
        ManualWidget(QWidget * = 0);

        /*!
         * Return minimum size for the widget.
         */
        QSize minimumSizeHint() const;

        /*!
         * Return preferred size for the widget.
         */
        QSize sizeHint() const;

 private:
        /*!
         * Help browser widget.
         */
        QTextBrowser *textBrowser;
        
 private slots:
        /*!
         * Handle change of current manual page.
         */
        void slotUpdateCaption();
};

#endif
