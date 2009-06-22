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

//!\file visualization_widget.cpp
//!Definition of VisualizationWidget class.

#include <cmath>
#include "rotation.h"
#include "quaternion.h"
#include "vector.h"
#include "visualization_widget.h"

VisualizationWidget::VisualizationWidget(Scene *scene, QWidget *parent, const QGLWidget *shareWidget)
        : QGLWidget(QGLFormat(QGL::DepthBuffer | QGL::DoubleBuffer | QGL::Rgba), parent, shareWidget), scene(scene)
{
}

QSize
VisualizationWidget::minimumSizeHint() const
{
        /* Return mimimum size. */
        return QSize(320, 320);
}

QSize
VisualizationWidget::sizeHint() const
{
        /* Return preferred size. */
        return QSize(480, 480);
}

void
VisualizationWidget::mousePressEvent(QMouseEvent *event)
{
        /* Handle right button pressed event only. */
        if (!(event->buttons() & Qt::LeftButton))
                return;

        /* Remember mouse position. */
        mousePosition = event->pos();
}

void
VisualizationWidget::mouseMoveEvent(QMouseEvent *event)
{
        /* Handle move event when right button pressed only. */
        if (!(event->buttons() & Qt::LeftButton))
                return;

        /* Calculate mouse pointer position increments and remember new
           mouse pointer position. */
        int deltaX = event->pos().x() - mousePosition.x();
        int deltaY = event->pos().y() - mousePosition.y();
        mousePosition = event->pos();

        /* Calculate rotations around eye x- and y-axis that are
           proportional to mouse pointer position increments around
           widget y- and x-axis. Add these rotations to cumulative scene
           rotation. */
        Rotation rotationY(Vector(0, 1, 0), M_PI * deltaX / width());
        Quaternion quaternion(rotationY);
        Rotation rotationX(Vector(1, 0, 0), M_PI * deltaY / height());
        quaternion *= Quaternion(rotationX);
        quaternion *= Quaternion(scene->getRotation());
        scene->setRotation((Rotation) quaternion);

        /* Force visualization widget repaint. */
        QTimer::singleShot(0, this, SLOT(updateGL()));
}

void
VisualizationWidget::paintGL()
{
        /* Render scene. */
        scene->render(width(), height());
}
