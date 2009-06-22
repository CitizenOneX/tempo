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

//!\file quaternion.h
//!Declaration of Quaternion class.

#ifndef QUATERNION_H
#define QUATERNION_H 1

#include "rotation.h"

//! Alternate description of 3D rotation.
/*!
 * This class represents quaternion-based rotation description.
 */
class Quaternion {
 public:
        /*!
         * Construct an object of Quaternion class given axis-angle
         * rotation description.
         */
        Quaternion(const Rotation &);

        /*!
         * Return quaternion w component.
         */
        float getW() const;

        /*!
         * Return quaternion x component.
         */
        float getX() const;

        /*!
         * Return quaternion y component.
         */
        float getY() const;

        /*!
         * Return quaternion z component.
         */
        float getZ() const;

        /*!
         * Compose with rotation described by given quaternion.
         */
        Quaternion &operator*=(const Quaternion &);

        /*!
         * Convert quaternion to axis-angle rotation description.
         */
        operator Rotation() const;

 private:
        /*!
         * Quaternion components.
         */
        float w, x, y, z;
};

#endif
