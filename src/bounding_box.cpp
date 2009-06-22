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

//!\file bounding_box.cpp
//!Definition of BoundingBox class.

#include <algorithm>
#include <limits>
#include "bounding_box.h"

BoundingBox::BoundingBox()
        : lo(Vector(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max())), hi(Vector(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max(), -std::numeric_limits<float>::max()))
{
}

BoundingBox::BoundingBox(const Vector &lo, const Vector &hi)
        : lo(lo), hi(hi)
{
}

const Vector &
BoundingBox::getLo() const
{
        /* Return lower coordinates corner point. */
        return lo;
}

const Vector &
BoundingBox::getHi() const
{
        /* Return upper coordinates corner point. */
        return hi;
}

BoundingBox &
BoundingBox::operator+=(const Vector &v)
{
        /* Extend bounding box if necessary in order to incorporate
           given point. */
        lo.clampAbove(v);
        hi.clampBelow(v);

        return *this;
}

BoundingBox
operator+(const BoundingBox &b0, const BoundingBox &b1)
{
        /* Calculate union of given bounding boxes. */
        Vector lo = b0.getLo();
        lo.clampAbove(b1.getLo());
        Vector hi = b0.getHi();
        hi.clampBelow(b1.getHi());

        return BoundingBox(lo, hi);
}
