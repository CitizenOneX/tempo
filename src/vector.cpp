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

//!\file vector.cpp
//!Definition of Vector class.

#include <cmath>
#include "vector.h"

Vector::Vector(const float x, const float y, const float z)
        : x(x), y(y), z(z)
{
}

float
Vector::getX() const
{
        /* Return x coordinate. */
        return x;
}
 
float
Vector::getY() const
{
        /* Return y coordinate. */
        return y;
}

float
Vector::getZ() const
{
        /* Return z coordinate. */
        return z;
}

float
Vector::norm() const
{
        /* Calcualate vector norm. */
        return std::sqrt(x * x + y * y + z * z);
}

float
Vector::normalize()
{
        /* Calcualate vector norm and check is normalization
           possible. */
        float den = norm();
        if (den == 0)
                return 0;
        
        /* Normalize vector. */
        float mul = 1 / den;
        x *= mul;
        y *= mul;
        z *= mul;
        
        return den;
}

Vector &
Vector::clampAbove(const Vector &v)
{
        /* Make each coordinate less or equal to corresponding
           coordinate of other vector. */
        if (x > v.x)
                x = v.x;
        if (y > v.y)
                y = v.y;
        if (z > v.z)
                z = v.z;
                
                return *this;
}
 
Vector &
Vector::clampBelow(const Vector &v)
{
        /* Make each coordinate greater or equal to corresponding
           coordinate of other vector. */
        if (x < v.x)
                x = v.x;
        if (y < v.y)
                y = v.y;
        if (z < v.z)
                z = v.z;
                
        return *this;
}

Vector operator-(const Vector &v0, const Vector &v1)
{
        /* Calculate difference of two given vectors. */
        float x, y, z;
        x = v0.x - v1.x;
        y = v0.y - v1.y;
        z = v0.z - v1.z;
        
        return Vector(x, y, z);
}

