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

//!\file gradient_widget.cpp
//!Definition of GradientWidget class.

#include "gradient_widget.h"

GradientWidget::GradientWidget(QWidget *parent)
        : QWidget(parent)
{
        /* Initialize interpolation object. */
        interpolation = 0;
}

QSize
GradientWidget::minimumSizeHint() const
{
        /* Return minimum size. */
        return QSize(64, 8);
}

QSize
GradientWidget::sizeHint() const
{
        /* Return preferred size. */
        return QSize(128, 16);
}

void
GradientWidget::setInterpolation(const Interpolation *interpolation)
{
        /* Remember interpolation object and update color legend pixmap
           and widget. */
        this->interpolation = interpolation;
        updatePixmap();
        update();
}

void
GradientWidget::resizeEvent(QResizeEvent *)
{
        /* Update color legend pixmap. */
        updatePixmap();
}
 
void
GradientWidget::paintEvent(QPaintEvent *event)
{
        QPainter painter(this);

        /* Restore dirty regions from color legend pixmap. */
        QVector<QRect> rectangles = event->region().rects();
        int size = rectangles.size();
        for (int i = 0; i < size; i++)
                painter.drawPixmap(QRectF(rectangles[i]), pixmap, QRectF(rectangles[i]));

        painter.end();
}

void
GradientWidget::updatePixmap()
{
        /* Resize pixmap. */
        int w = width(), h = height();
        pixmap = QPixmap(w, h);

        /* Recreate pixmap. For each column of pixels, interpolate
           column index to appropriate color using interpolation object
           and then draw column pixels. */
        QPainter painter(&pixmap);
        if (interpolation)
                for (int x = 0; x < w; x++) {
                        Color color = interpolation->interpolate(x, 0, w - 1);
                        painter.setPen(QColor((int) (255 * color.getR()), (int) (255 * color.getG()), (int) (255 * color.getB())));
                        painter.drawLine(x, 0, x, h - 1);
                }
        else
                painter.fillRect(rect(), QBrush(Qt::darkGray));

        painter.end();
}
