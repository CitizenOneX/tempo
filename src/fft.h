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

//!\file fft.h
//!Declaration of Fft class.

#ifndef FFT_H
#define FFT_H 1

#include <complex>
#include <vector>

//! FFT transformation.
/*!
 * This class represents FFT algorithm for calculating discrete Fourier
 * transform.
 */
class Fft {
 public:
        /*!
         * Construct an object of Fft class able to calculate Fourier
         * transform of complex number vectors of given length.  The
         * length is power of 2 which exponent is given as argument of
         * this function (the exponent must be in [1,15] interval).
         */
        Fft(const int);

        /*!
         * Calculate FFT of given vector of complex numbers.
         */
        std::vector< std::complex<float> > transform(std::vector< std::complex<float> > &);

 private:
        /*!
         * Real length of vectors for which this object is able to
         * calculate Fourier transform.
         */
        int n;

        /*!
         * Shuffled indices for rearranging elements of input vector
         * before approaching FFT butterfly calculations.
         */
        std::vector<int> shuffled;

        /*
         * Powers of 2*pi/n=W value needed for FFT butterfly
         * calculations.
         */
        std::vector< std::complex<float> > w;
};

#endif
