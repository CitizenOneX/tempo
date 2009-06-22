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

//!\file rotation.cpp
//!Definition of Rotation class.

#include <cmath>
#include "rotation.h"

Rotation::Rotation(const Vector &axis, const float angle)
        : axis(axis), angle(angle)
{
        /* Normalize axis. */
        this->axis.normalize();
}

const Vector &
Rotation::getAxis() const
{
        /* Return axis. */
        return axis;
}

float
Rotation::getAngle() const
{
        /* Return angle. */
        return angle;
}

