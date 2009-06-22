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

//!\file triangle.h
//! Declaration of Triangle class.

#ifndef TRIANGLE_H
#define TRIANGLE_H 1

//! Triangle in 3D space.
/*!
 * This class represents triangle.  Vertices, normals and materials data
 * are kept outside this class, this class is only holding pointers to
 * these.
 */
class Triangle {
 public:
        /*!
         * Construct an object of Triangle class given indices of
         * triangle vertices into vertices array, indices of normals
         * into normals array and index of material into materials
         * array.
         */
        Triangle(const int, const int, const int, const int, const int, const int, const int);

        /*!
         * Return index of first triangle vertex in vertices array.
         */
        int getV0() const;

        /*!
         * Return index of second triangle vertex in vertices array.
         */
        int getV1() const;

        /*!
         * Return index of third triangle vertex in vertices array.
         */
        int getV2() const;

        /*!
         * Return index of first triangle vertex normal in normals
         * array.
         */
        int getN0() const;

        /*!
         * Return index of second triangle vertex normal in normals
         * array.
         */
        int getN1() const;

        /*!
         * Return index of third triangle vertex normal in normals
         * array.
         */
        int getN2() const;

        /*!
         * Return index of triangle material in materials array.
         */
        int getM() const;

 private:
        /*!
         * Triangle vertices indices.
         */
        int v0, v1, v2;

        /*!
         * Triangle normals indices.
         */
        int n0, n1, n2;

        /*!
         * Triangle material index.
         */
        int m;
};

#endif
