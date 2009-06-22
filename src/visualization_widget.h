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

//!\file visualization_widget.h
//!Declaration of VisualizationWidget class.

#ifndef VISUALIZATION_WIDGET_H
#define VISUALIZATION_WIDGET_H 1

#include "scene.h"
#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

//! Score visualization.
/*!
 * This class represents visualization of given score.
 */
class VisualizationWidget : public QGLWidget
{
        Q_OBJECT

 public:
        /*!
         * Construct an object of VisualizationWidget class given scene
         * description, parent widget and widget to share OpenGL context
         * with.
         */
        VisualizationWidget(Scene *, QWidget * = 0, const QGLWidget * = 0);

        /*!
         * Return minimum size for the widget.
         */
        QSize minimumSizeHint() const;

        /*!
         * Return preferred size for the widget.
         */
        QSize sizeHint() const;

 protected:
        /*!
         * Event handler for widget mouse press event.
         */
        void mousePressEvent(QMouseEvent *);

        /*!
         * Event handler for widget mouse move event.
         */
        void mouseMoveEvent(QMouseEvent *);

        /*!
         * Widget repaint function.
         */
        void paintGL();

 private:
        /*!
         * Scene description
         */
        Scene *scene;

        /*!
         * Previous mouse position.
         */
        QPoint mousePosition;
};

#endif
