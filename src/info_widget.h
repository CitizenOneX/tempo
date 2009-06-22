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

//!\file info_widget.h
//!Declaration of InfoWidget class.

#ifndef INFO_WIDGET_H
#define INFO_WIDGET_H 1

#include "input.h"
#include <QtCore>
#include <QtGui>

//! Recording informations widget.
/*!
 * This class represents widget displaying various recording information.
 */
class InfoWidget : public QGroupBox
{
        Q_OBJECT

 public:
        /*!
         * Construct an object of InfoWidget class given parent widget.
         */
        InfoWidget(QWidget * = 0);

        /*!
         * Reinitialize widget contents when new input supplied.
         */
        void reinitialize(const Input *);

 private:
        /*!
         * Widget with patient informations.
         */
        QLineEdit *patientLineEdit;

        /*!
         * Widget with recording informations.
         */
        QLineEdit *recordingLineEdit;

        /*!
         * Widget with starting date and time informations.
         */
        QLineEdit *startingLineEdit;
};

#endif
