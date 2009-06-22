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

//!\file exception.h
//!Declaration of Exception class.

#ifndef EXCEPTION_H
#define EXCEPTION_H 1

//! Exceptional conditions.
/*!
 * This class represents exceptional running-time conditions.
 */
class Exception {
 public:
        /*!
         * Exception types.
         */
        typedef enum { INVALID_COLOR_COMPONENT = 1, INVALID_FFT_INPUT, INVALID_FFT_LENGTH, INVALID_INPUT_FILE, INVALID_INPUT_REQUEST, INVALID_INTERPOLATION_REQUEST, INVALID_MATERIAL_INDEX, INVALID_NORMAL_INDEX, INVALID_OBJECT_FILE, INVALID_SHININESS, INVALID_STREAMS_FILE, INVALID_VERTEX_INDEX } Type;

        /*!
         * Construct an object of Exception class given exception type.
         */
        Exception(const Type);

        /*!
         * Return exception type.
         */
        Type getType() const;

 private:
        /*!
         * Exception type.
         */
        Type type;
};

#endif
