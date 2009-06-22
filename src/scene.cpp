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

//!\file scene.cpp
//!Definition of Scene class.

#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include "scene.h"

Scene::Scene(const std::string &mappedName, const std::string &notMappedName)
        : mapped(mappedName), notMapped(notMappedName), rotation(Vector(0, 0, 1), M_PI)
{
}

Object &
Scene::getMapped()
{
        /* Return mapped object. */
        return mapped;
}
 
const Object &
Scene::getNotMapped() const
{
        /* Return not mapped object. */
        return notMapped;
}

const Rotation &
Scene::getRotation() const
{
        /* Return cumulative rotation. */
        return rotation;
}

void
Scene::setRotation(const Rotation &rotation)
{
        /* Remember new cumulative rotation. */
        this->rotation = rotation;
}

void
Scene::render(const int width, const int height) const
{
        /* Calculate viewing parameters from scene bounding box. */
        BoundingBox boundingBox = mapped.getBoundingBox() + notMapped.getBoundingBox();
        const Vector &lo = boundingBox.getLo(), &hi= boundingBox.getHi();
        float angle = M_PI / 12;
        float aspect = (float) width / height;
        Vector from(0, 0, (hi.getX() - lo.getX() > hi.getY() - lo.getY()) ? (hi.getX() - lo.getX()) / 2 / tan(angle / 2 * ((aspect < 1) ? aspect : 1)) + (hi.getZ() - lo.getZ()) : (hi.getY() - lo.getY()) / 2 / tan(angle / 2 * ((aspect < 1) ? aspect : 1)) + (hi.getZ() - lo.getZ()));
        Vector to(0, 0, 0);
        Vector up(0, 1, 0);

        /* Initialize OpenGL state. */
        glEnable(GL_DEPTH_TEST);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Setup viewing parameters. */
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(angle * 180 / M_PI, aspect, from.getZ() / 5, 5 * from.getZ());

        /* Initialize scene transformation. */
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        /* Setup light. */
        GLfloat lightAmbient[] = {0.8, 0.8, 0.8, 1};
        GLfloat lightDiffuse[] = {0.8, 0.8, 0.8, 1};
        GLfloat lightSpecular[] = {0.8, 0.8, 0.8, 1};
        GLfloat lightPosition[] = {0, 0, 0, 1};
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        /* Setup viewer. */
        gluLookAt(from.getX(), from.getY(), from.getZ(), to.getX(), to.getY(), to.getZ(), up.getX(), up.getY(), up.getZ());

        /* Apply cumulative rotation. */
        glRotatef(rotation.getAngle() * 180 / M_PI, rotation.getAxis().getX(), rotation.getAxis().getY(), rotation.getAxis().getZ());

        /* Draw mapped and not mapped scene objects. */
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
        mapped.render();
        notMapped.render();
}
