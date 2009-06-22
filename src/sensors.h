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

//!\file sensors.h
//!Declaration of Sensors class.

#ifndef SENSORS_H
#define SENSORS_H 1

#include <string>
#include <vector>
#include "vector.h"

//! Sensors set.
/*!
 * This class represents set of sensors for sampling data values.
 */
class Sensors {
 public:
        /*!
         * Construct an object of Sensors class given filename with
         * sensors description.  Sensors file format is described in
         * "Hacking" section of manual.
         */
        Sensors(const std::string &);

        /*!
         * Return number of sensors.
         */
        int getCount() const;

        /*!
         * Return vector of sensors names.
         */
        const std::vector<std::string> &getNames() const;

        /*!
         * Return vector of sensors positions.
         */
        const std::vector<Vector> &getPositions() const;

 private:
        /*!
         * Number of sensors.
         */
        int count;

        /*!
         * Vector of sensors names.
         */
        std::vector<std::string> names;

        /*!
         * Vector of sensors positions.
         */
        std::vector<Vector> positions;
};

#endif
