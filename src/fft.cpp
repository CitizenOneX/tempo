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

//!\file fft.cpp
//!Definition of Fft class.

#include <cmath>
#include "exception.h"
#include "fft.h"

Fft::Fft(const int p)
{
        /* Check is given argument in valid range. */
        if (p < 1 || p > 15)
                throw Exception(Exception::INVALID_FFT_LENGTH);

        /* Calculate real length of allowable input vectors. */
        n = 1 << p;
        int i, j;

        /* Calculate shuffled indices. */
        shuffled.resize(n);
        int index;
        for (i = 0; i < n; i++)
                for(index = i, shuffled[i] = index & 1, j = 1; j < p; j++) {
                        index >>= 1;
                        shuffled[i] <<= 1;
                        shuffled[i] |= index & 1;
                }

        /* Calculate powers of W value. */
        w.resize(n);
        w[0] = std::complex<float>(1, 0);
        w[1] = std::complex<float>(std::cos(2 * M_PI / n), -std::sin(2 * M_PI / n));
        for (i = 2; i < n; i++)
                w[i] = w[i - 1] * w[1];
}

std::vector< std::complex<float> >
Fft::transform(std::vector< std::complex<float> > &in)
{
        /* Check if length of input vector valid. */
        if ((int) in.size() != n)
                throw Exception(Exception::INVALID_FFT_INPUT);

        int i;

        /* Initialize output vector. */
        std::vector< std::complex<float> > out;
        out.resize(n);
        for(i = 0; i < n; i++)
                out[i] = in[shuffled[i]];

        int step;
        int lo, hi;
        int pow, curr;
        /* In each step,... */
        for (step = 1, pow = n / 2; step < n; step *= 2, pow /= 2)
                /* ...for each pair of input vector elements... */
                for (lo = 0, hi = step; hi < n; lo += step, hi += step)
                        for (i = 0, curr = 0; i < step; i++, lo++, hi++, curr += pow) {
                                /* ...calculate new values of pair elements. */
                                std::complex<float> e = out[lo], o = out[hi];
                                out[lo] = e + w[curr] * o;
                                out[hi] = e - w[curr] * o;
                        }

        return out;
}
