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

//!\file color.h
//!Declaration of Color class.

#ifndef COLOR_H
#define COLOR_H 1

//! RGB space color.
/*!
 * This class represents RGB space color.
 */
class Color {
 public:
        /*!
         * Construct an object of Color class given 3 color components.
         */
        Color(const float, const float, const float);

        /*!
         * Return red color component.
         */
        float getR() const;

        /*!
         * Return green color component.
         */
        float getG() const;

        /*!
         * Return blue color component.
         */
        float getB() const;

 private:
        /*!
         * Color components.
         */
        float r, g, b;
};

#endif
