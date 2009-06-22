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

//!\file vertex.cpp
//! Definition of Vertex class.

#include "vertex.h"

Vertex::Vertex(const Vector &point, const Color &color)
        : point(point), color(color)
{
}

const Vector &
Vertex::getPoint() const
{
        /* Return coordinates. */
        return point;
}

const Color &
Vertex::getColor() const
{
        /* Return color. */
        return color;
}

void
Vertex::setColor(const Color &color)
{
        /* Remember new color. */
        this->color = color;
}
