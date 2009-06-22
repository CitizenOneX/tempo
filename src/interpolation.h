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

//!\file interpolation.h
//!Declaration of Interpolation class.

#ifndef INTERPOLATION_H
#define INTERPOLATION_H 1

#include <vector>
#include "input.h"
#include "vertex.h"

//! Interpolation of sampled values.
/*!
 * This class represents interpolation of sampled values over set of 3D
 * vertices and mapping these interpolated values into vertices colors.
 */
class Interpolation {
 public:
        /*!
         * Construct an object of Interpolation class given array of
         * vertices and input dataset.
         */
        Interpolation(std::vector<Vertex> &, const Input &);

        /*!
         * Interpolate given value from given interval to color.
         */
        Color interpolate(const float, const float, const float) const;

        /*! 
         * For given set of score values, perform interpolation across
         * all vertices.
         */
        void process(const std::vector<float> &, const float, const float) const;

 private:
        /*!
         * Vertices to interpolate score values over.
         */
        std::vector<Vertex> &vertices;

        /*!
         * Count of vertices.
         */
        int count;

        /*!
         * Indices of nearest sensors for each vertex.
         */
        std::vector<int> indices;

        /* Interpolation coefficients for nearest sensors for each
           vertex. */
        std::vector<float> coefficients;

        /*!
         * Number of expected input values for interpolation.
         */
        int expectedSize;
};

#endif
