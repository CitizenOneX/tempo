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

//!\file rotation.h
//!Declaration of Rotation class.

#ifndef ROTATION_H
#define ROTATION_H 1

#include "vector.h"

//! 3D rotation.
/*!
 * This class represents rotation in 3D Cartesian space.
 */
class Rotation {
 public:
        /*!
         * Construct an object of Vector class given rotation axis and
         * angle.
         */
        Rotation(const Vector&, const float);

        /*!
         * Get rotation axis.
         */
        const Vector &getAxis() const;

        /*!
         * Get rotation angle.
         */
        float getAngle() const;

 private:
        /*!
         * Rotation axis.
         */
        Vector axis;

        /*!
         * Rotation angle.
         */
        float angle;
};

#endif
