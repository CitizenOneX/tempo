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

//!\file input.cpp
//!Definition of Input class.

#include <complex>
#include <cstdarg>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <sstream>
#include "exception.h"
#include "fft.h"
#include "input.h"

// Emotiv Insight only outputs 5 signals, so change minimum from 6 to 5 electrodes
const int Input::COUNT_MIN = 5;
const std::string Input::VERSION = "0       ";

Input::Input(const std::string &name, const Sensors &sensors)
{
        /* Open file with sampled values. */
        std::ifstream stream(name.c_str(), std::ios::binary);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);

        char buffer[81];
        int i, j;

        /* Read and check version string. */
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        if (buffer != VERSION)
                throw Exception(Exception::INVALID_INPUT_FILE);

        /* Read patient information. */
        stream.read(buffer, 80);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[80] = 0;
        for (i = 79; i >= 0 && buffer[i] == ' '; i--)
                buffer[i] = 0;
        patient = buffer;

        /* Read recording information. */
        stream.read(buffer, 80);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[80] = 0;
        for (i = 79; i >= 0 && buffer[i] == ' '; i--)
                buffer[i] = 0;
        recording = buffer;

        /* Read start date of recording. */
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        for (i = 7; i >= 0 && buffer[i] == ' '; i--)
                buffer[i] = 0;
        std::istringstream date(buffer);
        date >> day;
        date.get();
        date >> month;
        date.get();
        date >> year;
        if (!date)
                throw Exception(Exception::INVALID_INPUT_FILE);

        /* Read start time of recording. */
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        for (i = 7; i >= 0 && buffer[i] == ' '; i--)
                buffer[i] = 0;
        std::istringstream time(buffer);
        time >> hour;
        time.get();
        time >> minute;
        time.get();
        time >> second;
        if (!time)
                throw Exception(Exception::INVALID_INPUT_FILE);
        
        /* Read number of bytes in input file header. */
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        offset = std::atoi(buffer);

        /* Read first reserved block. */
        stream.read(buffer, 44);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);

         /* Read number of data records. */
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        data = std::atoi(buffer);

        /* Read data record duration. */
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        duration = std::atoi(buffer);

        /* Read number of signals in input file. */
        stream.read(buffer, 4);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[4] = 0;
        count = std::atoi(buffer);

        /* Create signal objects. */
        for (i = 0; i < count; i++) {
                /* Read signal label. */
                stream.read(buffer, 16);
                if (!stream)
                        throw Exception(Exception::INVALID_INPUT_FILE);
                buffer[16] = 0;
                for (j = 15; j >= 0 && buffer[j] == ' '; j--)
                        buffer[j] = 0;

                const std::vector<std::string> &names = sensors.getNames();
                const std::vector<Vector> &positions = sensors.getPositions();
                /* Compare signal label with all known sensor
                   names... */
                for (j = 0; j < (int) names.size(); j++)
                        /* ...and if match found, create signal object
                           and read signal information from file, then
                           remember signal object and position of
                           corresponding sensor.  */
                        if (names[j] == buffer) {
                                signals.push_back(Signal(name, i));
                                points.push_back(positions[j]);
                                break;
                        }
        }

        /* Check that at least minimal necessary number of signals exist
           in input file. */
        count = signals.size();
        if (count < COUNT_MIN)
                throw Exception(Exception::INVALID_INPUT_FILE);

        /* Calculate last sample index. */
        for (i = 1; i < count; i++)
                if (signals[i].getBlockCount() != signals[0].getBlockCount())
                        throw Exception(Exception::INVALID_INPUT_FILE);
        last = data * signals[0].getBlockCount() - 1;

        /* Calculate sampling frequency. */
        frequency = (duration != 0) ? (float) signals[0].getBlockCount() / duration : 0;

        /* Calculate physical minimum and maximum value over all
           samples. */
        physicalLo = std::numeric_limits<float>::max();
        physicalHi = -std::numeric_limits<float>::max();
        for (i = 0; i < count; i++) {
                if (physicalLo > signals[i].getPhysicalLo())
                        physicalLo = signals[i].getPhysicalLo();
                if (physicalHi > signals[i].getPhysicalHi())
                        physicalHi = signals[i].getPhysicalHi();
        }
}

const std::string &
Input::getPatient() const
{
        /* Return patient information. */
        return patient;
}

const std::string &
Input::getRecording() const
{
        /* Return recording information. */
        return recording;
}

int
Input::getYear() const
{
        /* Return year of start of recording. */
        return year;
}
 
int
Input::getMonth() const
{
        /* Return month of start of recording. */
        return month;
}
 
int
Input::getDay() const
{
        /* Return day of start of recording. */
        return day;
}
 
int
Input::getHour() const
{
        /* Return hour of start of recording. */
        return hour;
}
 
int
Input::getMinute() const
{
        /* Return minute of start of recording. */
        return minute;
}
 
int
Input::getSecond() const
{
        /* Return second of start of recording. */
        return second;
}

float
Input::getFrequency() const
{
        /* Return sampling frequency. */
        return frequency;
}

int
Input::getCount() const
{
        /* Return number of signals in input file. */
        return count;
}

const std::vector<Vector> &
Input::getPoints() const
{
        /* Return positions of sensors corresponding to signals. */
        return points;
}

std::vector<float>
Input::getValues(const Score score, const int from, ...)
{
        std::vector<float> values;

        std::vector<float> samples;
        int i, j;

        /* If raw potential values requested, read and return samples
           from input file. */
        if (score == RAW_POTENTIAL) {
                for (i = 0; i < count; i++) {
                        samples = signals[i].getSamples(from, 1);
                        values.push_back(samples[0]);
                }

                return values;
        }

        /* If DFT score requested, extract additional function
           arguments. */
        va_list ap;
        va_start(ap, from);
        int window = va_arg(ap, int);
        int frequency = va_arg(ap, int);
        va_end(ap);
        if (from < window - 1 || window < 2)
                throw Exception(Exception::INVALID_INPUT_REQUEST);
        
        /* Check that DFT window is power of 2 and find which one. */
        int p;
        for (p = 0; (window & (1 << p)) == 0; p++);
        if ((window & ~(1 << p)) != 0)
                throw Exception(Exception::INVALID_INPUT_REQUEST);
        Fft fft(p);

        /* For each signal, read raw potential values from input file,
           calculate DFT of these values and extract DFT amplitude or
           phase at requested frequency as result. */
        for (i = 0; i < count; i++) {
                samples = signals[i].getSamples(from - (window - 1), window);
                std::vector< std::complex<float> > in;
                for (j = 0; j < window; j++)
                        in.push_back(std::complex<float>(samples[j], 0));
                std::vector< std::complex<float> > out = fft.transform(in);

                if (score == DFT_AMPLITUDE)
                        values.push_back(std::abs(out[frequency]));
                else if (score == DFT_PHASE)
                        values.push_back(std::arg(out[frequency]));
        }

        return values;
}

int
Input::getLast() const
{
        /* Return last sample index. */
        return last;
}
