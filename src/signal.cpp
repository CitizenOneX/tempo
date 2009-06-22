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

//!\file signal.cpp
//!Definition of Signal class.

#include <cstdlib>
#include <fstream>
#include "exception.h"
#include "signal.h"

Signal::Signal(const std::string &name, const int number)
        : name(name)
{
        /* Open file with sampled values. */
        std::ifstream stream(name.c_str(), std::ios::binary);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);

        char buffer[81];
        int i;

        /* Read number of signals from input file. */
        stream.seekg(252);
        stream.read(buffer, 4);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[4] = 0;
        int count = std::atoi(buffer);
        
        /* Read signal label. */
        stream.seekg(256 + number * 16);
        stream.read(buffer, 16);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[16] = 0;
        for (i = 15; i >= 0 && buffer[i] == ' '; i--)
                buffer[i] = 0;
        label = buffer;

        /* Read signal transducer type. */
        stream.seekg(256 + count * 16 + number * 80);
        stream.read(buffer, 80);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[80] = 0;
        for (i = 79; i >= 0 && buffer[i] == ' '; i--)
                buffer[i] = 0;
        transducer = buffer;

        /* Read and calculate signal unit (must be in volts). */
        stream.seekg(256 + count * 96 + number * 8);
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        for (i = 7; i >= 0 && buffer[i] == ' '; i--)
                buffer[i] = 0;
        switch (i) {
        case 0:
                if (buffer[i] != 'V')
                        throw Exception(Exception::INVALID_INPUT_FILE);
                unit = 1e6;
                break;

        case 1:
                if (buffer[i] != 'V')
                        throw Exception(Exception::INVALID_INPUT_FILE);
                switch(buffer[i - 1]) {
                case 'Y':
                        unit = 1e30;
                        break;

                case 'Z':
                        unit = 1e27;
                        break;

                case 'E':
                        unit = 1e24;
                        break;

                case 'P':
                        unit = 1e21;
                        break;

                case 'T':
                        unit = 1e18;
                        break;

                case 'G':
                        unit = 1e15;
                        break;

                case 'M':
                        unit = 1e12;
                        break;

                case 'K':
                        unit = 1e9;
                        break;

                case 'H':
                        unit = 1e8;
                        break;

                case 'D':
                        unit = 1e7;
                        break;

                case 'd':
                        unit = 1e5;
                        break;

                case 'c':
                        unit = 1e4;
                        break;

                case 'm':
                        unit = 1e3;
                        break;

                case 'u':
                        unit = 1;
                        break;

                case 'n':
                        unit = 1e-3;
                        break;

                case 'p':
                        unit = 1e-6;
                        break;

                case 'f':
                        unit = 1e-9;
                        break;

                case 'a':
                        unit = 1e-12;
                        break;

                case 'z':
                        unit = 1e-15;
                        break;

                case 'y':
                        unit = 1e-18;
                        break;

                default:
                        throw Exception(Exception::INVALID_INPUT_FILE);
                }
                break;

        default:
                throw Exception(Exception::INVALID_INPUT_FILE);
        }

        /* Read physical minimum and maximum. */
        stream.seekg(256 + count * 104 + number * 8);
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        physicalLo = std::atoi(buffer);
        stream.seekg(256 + count * 112 + number * 8);
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        physicalHi = std::atoi(buffer);

        /* Read digital minimum and maximum. */
        stream.seekg(256 + count * 120 + number * 8);
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        digitalLo = std::atoi(buffer);
        stream.seekg(256 + count * 128 + number * 8);
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        digitalHi = std::atoi(buffer);

        /* Read prefiltering indicator. */
        stream.seekg(256 + count * 136 + number * 80);
        stream.read(buffer, 80);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[80] = 0;
        for (i = 79; i >= 0 && buffer[i] == ' '; i--)
                buffer[i] = 0;
        prefiltering = buffer;

        /* Read number of samples in each data record. */
        stream.seekg(256 + count * 216 + number * 8);
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        blockCount = std::atoi(buffer);

        /* Read reserved bytes. */
        stream.seekg(256 + count * 224 + number * 32);
        stream.read(buffer, 32);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);

        /* Calculate coefficients for conversion from digital to
           physical signal value. */
        c1 = (digitalHi != digitalLo) ? (physicalHi - physicalLo) * unit / (digitalHi - digitalLo) : 0;
        c0 = physicalLo * unit - digitalLo * c1;

        /* Read number of bytes in input file header. */
        stream.seekg(184);
        stream.read(buffer, 8);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);
        buffer[8] = 0;
        offset = std::atoi(buffer);

        /* Calculate offset of first signal sample in input file and
           number of bytes to skip between two successive signal data
           records. */
        skip = 0;
        for (i = 0; i < number; i++) {
                stream.seekg(256 + count * 216 + i * 8);
                stream.read(buffer, 8);
                if (!stream)
                        throw Exception(Exception::INVALID_INPUT_FILE);
                buffer[8] = 0;
                offset += 2 * std::atoi(buffer);
                skip += 2 * std::atoi(buffer);
        }
        skip += 2 * blockCount;
        for (i = number + 1; i < count; i++) {
                stream.seekg(256 + count * 216 + i * 8);
                stream.read(buffer, 8);
                if (!stream)
                        throw Exception(Exception::INVALID_INPUT_FILE);
                buffer[8] = 0;
                skip += 2 * std::atoi(buffer);
        }
}

const int
Signal::getBlockCount() const
{
        /* Return number of samples in data record. */
        return blockCount;
}

const float
Signal::getPhysicalLo() const
{
        /* Return mimimum physical value. */
        return physicalLo;
}
 
const float
Signal::getPhysicalHi() const
{
        /* Return maximum physical value. */
        return physicalHi;
}

std::vector<float>
Signal::getSamples(const int from, const int length)
{
        std::vector<float> samples;

        /* Open file with sampled values. */
        std::ifstream stream(name.c_str(), std::ios::binary);
        if (!stream)
                throw Exception(Exception::INVALID_INPUT_FILE);

        /* Calculate number of data record and offset in this record of
           first requested sample. */
        div_t div = std::div(from, blockCount);
        stream.seekg(offset + div.quot * skip + 2 * div.rem);

        /* Read samples. */
        char buffer[2];
        for (int i = 0; i < length; i++) {
                /* Read raw sample from input file (samples are stored
                   in little-endian format) and calculate corresponding
                   physical value. */
                stream.read(buffer, 2);
                if (!stream)
                        throw Exception(Exception::INVALID_INPUT_FILE);
                samples.push_back(c0 + c1 * ((buffer[1] << 8) | buffer[0]));

                /* Calculate number of data record and offset in this
                   record of next sample. */
                div.rem++;
                if (div.rem == blockCount) {
                        div.rem = 0;
                        stream.seekg(skip - 2 * blockCount, std::ios_base::cur);
                }
        }

        return samples;
}
