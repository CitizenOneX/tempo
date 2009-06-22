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

//!\file signal.h
//!Declaration of Signal class.

#ifndef SIGNAL_H
#define SIGNAL_H 1

#include <string>
#include <vector>

//! Data values sampled from a sensor.
/*!
 * This class represents set of sampled data values.
 */
class Signal {
 public:
        /*!
         * Construct an object of Signal class given filename with
         * samples and ordering number of given signal in filename.
         */
        Signal(const std::string &, const int);

        /*!
         * Get number of samples in signal data record.
         */
        const int getBlockCount() const;

        /*!
         * Get signal minimum physical value.
         */
        const float getPhysicalLo() const;

        /*!
         * Get signal maximum physical value.
         */
        const float getPhysicalHi() const;

        /*!
         * Get signal samples.
         */
        std::vector<float> getSamples(const int, const int);

 private:
        /*!
         * Input filename.
         */
        std::string name;

        /*!
         * Signal label.
         */
        std::string label;

        /*!
         * Signal transducer type.
         */
        std::string transducer;

        /*!
         * Signal physical dimension.
         */
        float unit;

        /*!
         * Signal physical minimum and maximum.
         */
        float physicalLo, physicalHi;

        /*!
         * Signal digital minimum and maximum.
         */
        float digitalLo, digitalHi;

        /*!
         * Prefiltering indicator.
         */
        std::string prefiltering;

        /*!
         * Number of samples in each data record.
         */
        int blockCount;

        /*!
         * Coefficients from conversion from digital to physical signal
         * value.
         */
        float c0, c1;

        /*!
         * Offset of first signal sample in input file.
         */
        int offset;

        /*!
         * Number of bytes to skip between two successive signal data
         * records.
         */
        int skip;
};

#endif
