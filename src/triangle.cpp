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

//!\file triangle.cpp
//! Definition of Triangle class.

#include "exception.h"
#include "triangle.h"

Triangle::Triangle(const int v0, const int v1, const int v2, const int n0, const int n1, const int n2, const int m)
        : v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2), m(m)
{
        /* Check if vertices indices in valid range. */
        if (v0 < 0 || v1 < 0 || v2 < 0)
                throw Exception(Exception::INVALID_VERTEX_INDEX);

        /* Check if normals indices in valid range. */
        if (n0 < 0 || n1 < 0 || n2 < 0)
                throw Exception(Exception::INVALID_NORMAL_INDEX);

        /* Check if material index in valid range. */
        if (m < 0)
                throw Exception(Exception::INVALID_MATERIAL_INDEX);
}

int
Triangle::getV0() const
{
        /* Return first vertex index. */
        return v0;
}

int
Triangle::getV1() const
{
        /* Return second vertex index. */
        return v1;
}

int
Triangle::getV2() const
{
        /* Return third vertex index. */
        return v2;
}

int
Triangle::getN0() const
{
        /* Return first vertex normal index. */
        return n0;
}

int
Triangle::getN1() const
{
        /* Return second vertex normal index. */
        return n1;
}

int
Triangle::getN2() const
{
        /* Return third vertex normal index. */
        return n2;
}

int
Triangle::getM() const
{
        /* Return material index. */
        return m;
}
