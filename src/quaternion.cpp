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

//!\file quaternion.cpp
//!Definition of Quaternion class.

#include <cmath>
#include "quaternion.h"
#include "vector.h"

Quaternion::Quaternion(const Rotation &rotation)
        : w(1), x(0), y(0), z(0)
{
        /* Normalize rotation axis. */
        Vector v = rotation.getAxis();
        v.normalize();

        /* Calculate components from given rotation axis and angle. */
        float angle = rotation.getAngle();
        float sinHalfAngle = std::sin(angle / 2);
        w = std::cos(angle / 2);
        x = v.getX() * sinHalfAngle;
        y = v.getY() * sinHalfAngle;
        z = v.getZ() * sinHalfAngle;
}

float
Quaternion::getW() const
{
        /* Return w component. */
        return w;
}

float
Quaternion::getX() const
{
        /* Return x component. */
        return x;
}

float
Quaternion::getY() const
{
        /* Return y component. */
        return y;
}

float
Quaternion::getZ() const
{
        /* Return z component. */
        return z;
}

Quaternion &
Quaternion::operator*=(const Quaternion &q)
{
        /* Multiply with given quaternion. */
        float w, x, y, z;
        w = this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z;
        x = this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y;
        y = this->w * q.y + this->y * q.w + this->z * q.x - this->x * q.z;
        z = this->w * q.z + this->z * q.w + this->x * q.y - this->y * q.x;
        this->w = w, this->x = x, this->y = y, this->z = z;

        return *this;
}

Quaternion::operator Rotation() const
{
        /* Handle null rotation as special case. */
        float den = std::sqrt(x * x + y * y + z * z);
        if (den == 0)
                return Rotation(Vector(0, 0, 1), 0);

        /* Calculate axis and angle of rotation represented by current
           components values. */
        float mul = 1 / den;
        Vector axis = Vector(mul * x, mul * y, mul * z);
        float angle = 2 * std::acos(w);
        return Rotation(axis, angle);
}
