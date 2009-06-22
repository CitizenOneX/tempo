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

//!\file sensors.cpp
//!Definition of Sensors class.

#include <fstream>
#include "exception.h"
#include "sensors.h"

Sensors::Sensors(const std::string &name)
{
        /* Open file with sensors description. */
        std::ifstream stream(name.c_str());
        if (!stream)
                throw Exception(Exception::INVALID_STREAMS_FILE);

        /* Read sensors count. */
        stream >> count;
        if (!stream)
                throw Exception(Exception::INVALID_STREAMS_FILE);

        /* For each sensor,... */
        char c;
        float x, y, z;
        for (int i = 0; i < count; i++) {
                /* ...read sensor name length,... */
                int length;
                stream >> length;
                if (!stream)
                        throw Exception(Exception::INVALID_STREAMS_FILE);

                for (; stream.get() != '"'; )
                        if (!stream)
                                throw Exception(Exception::INVALID_STREAMS_FILE);

                /* ...then read sensor name... */
                std::string name;
                for (; (c = stream.get()) != '"'; ) {
                        if (!stream)
                                throw Exception(Exception::INVALID_STREAMS_FILE);
                        name += c;
                }
                if ((int) name.length() != length)
                        throw Exception(Exception::INVALID_STREAMS_FILE);
                names.push_back(name);

                /* ...and coordinates. */
                stream >> x >> y >> z;
                positions.push_back(Vector(x, y, z));
        }
}

int
Sensors::getCount() const
{
        /* Return sensors count. */
        return count;
}

const std::vector<std::string> &
Sensors::getNames() const
{
        /* Return sensors names. */
        return names;
}

const std::vector<Vector> &
Sensors::getPositions() const
{
        /* Return sensors positions. */
        return positions;
}
