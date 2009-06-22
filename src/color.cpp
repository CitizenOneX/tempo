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

//!\file color.cpp
//!Definition of Color class.

#include "color.h"
#include "exception.h"

Color::Color(const float r, const float g, const float b)
        : r(r), g(g), b(b)
{
        /* Check if given components in valid range. */
        if (r < 0 || r > 1 || g < 0 || g > 1 || g < 0 || g > 1)
                throw Exception(Exception::INVALID_COLOR_COMPONENT);
}

float
Color::getR() const
{
        /* Return red component. */
        return r;
}

float
Color::getG() const
{
        /* Return green component. */
        return g;
}

float
Color::getB() const
{
        /* Return blue component. */
        return b;
}

