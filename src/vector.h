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

//!\file vector.h
//!Declaration of Vector class.

#ifndef VECTOR_H
#define VECTOR_H 1

//! 3D Cartesian space vector.
/*!
 * This class represents 3D Cartesian space vector.
 */
class Vector {
        /*!
         * Subtract two vectors.
         */
        friend Vector operator-(const Vector &, const Vector &);

 public:
        /*!
         * Construct an object of Vector class given 3 Cartesian space
         * coordinates.
         */
        Vector(const float, const float, const float);

        /*!
         * Return vector x coordinate.
         */
        float getX() const;

        /*!
         * Return vector y coordinate.
         */
        float getY() const;

        /*!
         * Return vector z coordinate.
         */
        float getZ() const;

        /*!
         * Calculate vector norm.
         */
        float norm() const;

        /*!
         * Normalize vector and return vector norm.
         */
        float normalize();

        /*!
         * Make each coordinate less or equal of corresponding
         * coordinate of other vector.
         */
        Vector &clampAbove(const Vector&);

        /*!
         * Make each coordinate greater or equal fo corresponding
         * coordinate of other vector.
         */
        Vector &clampBelow(const Vector&);

 private:
        /*!
         * Vector coordinates.
         */
        float x, y, z;
};

#endif
