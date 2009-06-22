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

//!\file interpolation.cpp
//!Definition of Interpolation class.

#include <limits>
#include "exception.h"
#include "interpolation.h"

Interpolation::Interpolation(std::vector<Vertex> &vertices, const Input &input)
        : vertices(vertices)
{
        /* Rememember count of vertices. */
        count = vertices.size();

        /* For each vertex... */
        int i, j, k;
        for (i = 0; i < count; i++) {
                /* ...calculate distance from each sensor,... */
                const std::vector<Vector> &points = input.getPoints();
                std::vector<float> distances;
                for (j = 0; j < input.getCount(); j++) {
                        Vector v = vertices[i].getPoint() - points[j];
                        distances.push_back(v.norm());
                }

                /* ...find nearest sensors and initialize corresponding
                   interpolation coefficients... */
                for (j = 0; j < Input::COUNT_MIN; j++) {
                        int index = 0;
                        float distance = distances[index];
                        for (k = index + 1; k < input.getCount(); k++)
                                if (distance > distances[k]) {
                                        distance = distances[k];
                                        index = k;
                                }
                        indices.push_back(index);
                        coefficients.push_back(distance);
                        distances[index] = std::numeric_limits<float>::max();
                }

                /* ...and then calculate final interpolation
                   coefficients values. */
                float den = 0;
                for (j = 0; j < Input::COUNT_MIN; j++) {
                        if (coefficients[Input::COUNT_MIN * i + j] == 0) {
                                for (k = 0; k < Input::COUNT_MIN; k++)
                                        coefficients[Input::COUNT_MIN * i + k] = 0;
                                coefficients[Input::COUNT_MIN * i + j] = 1;
                                break;
                        }
                        coefficients[Input::COUNT_MIN * i + j] = 1 / coefficients[Input::COUNT_MIN * i + j];
                        den += coefficients[Input::COUNT_MIN * i + j];
                }
                if (j == Input::COUNT_MIN) {
                        float mul = 1 / den;
                        for (j = 0; j < Input::COUNT_MIN; j++)
                                coefficients[Input::COUNT_MIN * i + j] *= mul;
                }
        }

        /* Remember expected number of input values. */
        expectedSize = input.getCount();
}

Color
Interpolation::interpolate(const float value, const float lo, const float hi) const
{
        /* Clamp value to given range. */
        float t;
        if (value <= lo)
                t = 0;
        else if (value >= hi)
                t = 1;
        else
                t = (value - lo) / (hi - lo);

        /* Map value to color.  Values from first half of range are
           mapped to colors between blue and green, values from second
           half or range are mapped to colors between green and red. */
        return (t < 0.5) ? Color(0, 1.6 * t, 0.8 - 1.6 * t) : Color(1.6 * t - 0.8, 1.6 - 1.6 * t, 0);
}

void
Interpolation::process(const std::vector<float> &values, const float lo, const float hi) const
{
        /* Check that number of given values is as expected. */
        if ((int) values.size() != expectedSize)
                throw Exception(Exception::INVALID_INTERPOLATION_REQUEST);

        /* For each vertex... */
        int i, j;
        for (i = 0; i < count; i++) {
                /* ...interpolate vertex score value from score values
                   of nearest sensors using precalculated interpolation
                   coefficients... */
                float value = 0;
                for (j = 0; j < Input::COUNT_MIN; j++)
                        value += coefficients[i * Input::COUNT_MIN + j] * values[indices[i * Input::COUNT_MIN + j]];

                
                /* ...and map interpoolated vertex score value to vertex
                   color. */
                vertices[i].setColor(interpolate(value, lo, hi));
        }
}
