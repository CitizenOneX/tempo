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

//!\file input.h
//!Declaration of Input class.

#ifndef INPUT_H
#define INPUT_H 1

#include <string>
#include <vector>
#include "sensors.h"
#include "signal.h"
#include "vector.h"

//! Input dataset.
/*!
 * This class represents sets of all values sampled during measuring.
 */
class Input {
 public:
        /*!
         * Type of score calculated from sampled values.
         */
        typedef enum { RAW_POTENTIAL, DFT_AMPLITUDE, DFT_PHASE } Score;

        /*!
         * Minimum number of signals needed for successfull
         * interpolation.
         */
        static const int COUNT_MIN;

        /*!
         * Construct an object of Input class given filename with
         * samples and object with sensors descriptions.
         */
        Input(const std::string &, const Sensors &);

        /*!
         * Get patient information.
         */
        const std::string &getPatient() const;

        /*!
         * Get recording information.
         */
        const std::string &getRecording() const;

        /*!
         * Get year of start of recording.
         */
        int getYear() const;

        /*!
         * Get month of start of recording.
         */
        int getMonth() const;

        /*!
         * Get day of start of recording.
         */
        int getDay() const;

        /*!
         * Get hour of start of recording.
         */
        int getHour() const;

        /*!
         * Get minute of start of recording.
         */
        int getMinute() const;

        /*!
         * Get second of start of recording.
         */
        int getSecond() const;

        /*!
         * Get sampling frequency.
         */
        float getFrequency() const;

        /*!
         * Get signals count.
         */
        int getCount() const;

        /*!
         * Get positions of sensors corresponding to signals.
         */
        const std::vector<Vector> &getPoints() const;

        /*!
         * Get given score values starting from given sample.  Depending
         * on score, function may have more arguments:  DFT scores
         * require specifying DFT window length and frequency to return
         * values for.
         */
        std::vector<float> getValues(const Score, const int, ...);

        /*!
         * Get last sample index.
         */
        int getLast() const;

 private:
        /*!
         * Version of input format supported.
         */
        static const std::string VERSION;

        /*!
         * Patient information.
         */
        std::string patient;

        /*!
         * Recording information.
         */
        std::string recording;

        /*!
         * Start of recording date.
         */
        int year, month, day;

        /*!
         * Start of recording time.
         */
        int hour, minute, second;

        /*!
         * Number of bytes in input file header.
         */
        int offset;

        /*!
         * Number of data records in input file.
         */
        int data;

        /*!
         * Duration of data records (in seconds).
         */
        int duration;

        /*!
         * Number of signals recorded in input file.
         */
        int count;

        /*!
         * Signals objects.
         */
        std::vector<Signal> signals;

        /*!
         * Positions of seonsors corresponding to signals.
         */
        std::vector<Vector> points;

        /*!
         * Last sample index.
         */
        int last;

        /*!
         * Sampling frequency.
         */
        float frequency;

        /*!
         * Signals physical minimum and maximum.
         */
        float physicalLo, physicalHi;
};

#endif
