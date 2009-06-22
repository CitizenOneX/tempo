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

//!\file bounding_box.h
//!Declaration of BoundingBox class.

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H 1

#include "vector.h"

//! Axis-aligned bounding box.
/*!
 * This class represents axis-aligned bounding box.
 */
class BoundingBox {
        /*!
         * Add two bounding boxes.
         */
        friend BoundingBox operator+(const BoundingBox &, const BoundingBox &);

 public:
        /*!
         * Construct an object of BoundingBox class with invalid bounds.
         */
        BoundingBox();

        /*!
         * Construct an object of BoundingBox class with given bounds.
         */
        BoundingBox(const Vector &, const Vector &);

        /*!
         * Return lower coordinates bounding box corner point.
         */
        const Vector &getLo() const;

        /*!
         * Return higher coordinates bounding box corner point.
         */
        const Vector &getHi() const;

        /*!
         * Adjust bounding box to include given point.
         */
        BoundingBox &operator+=(const Vector &);

 private:
        /*!
         * Bounding box corner points.
         */
        Vector lo, hi;
};

#endif

