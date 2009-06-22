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

//!\file legend_widget.h
//!Declaration of LegendWidget class.

#ifndef LEGEND_WIDGET_H
#define LEGEND_WIDGET_H 1

#include "interpolation.h"
#include "gradient_widget.h"
#include <QtCore>
#include <QtGui>

//! Mapping legend widget.
/*!
 * This class represents widget displaying and controlling mapping color
 * legend.
 */
class LegendWidget : public QGroupBox
{
        Q_OBJECT

 public:
        /*!
         * Construct an object of LegendWidget class given parent widget.
         */
        LegendWidget(QWidget * = 0);

        /*!
         * Reinitialize widget contents when new interpolation supplied.
         */
        void reinitialize(const Interpolation *);

        /*!
         * Return range of score values represented by color spectrum.
         */
        void getRange(float *, float *) const;

        /*!
         * Set total range of score values and range of these values
         * represented by color spectrum.
         */
        void setRange(const float, const float, const float, const float);

 signals:
        /*!
         * Signal emitted when some of color mapping parameters changed.
         */
        void changed();

 private:
        /*!
         * Lowest score value represented by color spectrum selection
         * widget.
         */
        QDoubleSpinBox *lowSpinBox;

        /*!
         * Widget displaying color spectrum.
         */
        GradientWidget *gradientWidget;

        /*!
         * Highest score value represented by color spectrum selection
         * widget.
         */
        QDoubleSpinBox *highSpinBox;

 private slots:
        /*!
         * Handle change of lowest mapped score value selection widget.
         */
        void slotLowValueChanged(double);

        /*!
         * Handle change of highest mapped score value selection widget.
         */
        void slotHighValueChanged(double);
};

#endif
