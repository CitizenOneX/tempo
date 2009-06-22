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

//!\file gradient_widget.h
//!Declaration of GradientWidget class.

#ifndef GRADIENT_WIDGET_H
#define GRADIENT_WIDGET_H 1

#include "interpolation.h"
#include <QtCore>
#include <QtGui>

//! Gradient of colors widget.
/*!
 * This class represents widget displaying colors spectrum.
 */
class GradientWidget : public QWidget
{
        Q_OBJECT

 public:
        /*!
         * Construct an object of GradientWidget class given parent
         * widget.
         */
        GradientWidget(QWidget * = 0);

        /*!
         * Return minimum size for the widget.
         */
        QSize minimumSizeHint() const;

        /*!
         * Return preferred size for the widget.
         */
        QSize sizeHint() const;

        /*!
         * Set interpolation object.
         */
        void setInterpolation(const Interpolation *);

 protected:
        /*!
         * Event handler for widget resize event.
         */
        void resizeEvent(QResizeEvent *);

        /*!
         * Event handler for widget repaint event.
         */
        void paintEvent(QPaintEvent *);

 private:
        /*!
         * Interpolation object.
         */
        const Interpolation *interpolation;

        /*!
         * Pixmap containing color legend.
         */
        QPixmap pixmap;

        /*!
         * Update color legend pixmap.
         */
        void updatePixmap();
};

#endif
