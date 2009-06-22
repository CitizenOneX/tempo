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

//!\file material.h
//! Declaration of Material class.

#ifndef MATERIAL_H
#define MATERIAL_H 1

#include "color.h"

//! Material properties.
/*!
 * This class represents object material properties.
 */
class Material {
 public:
        /*!
         * Construct an object of Material class given ambient and
         * specular color and shininess.
         */
        Material(const Color &, const Color &, const float);

        /*!
         * Return material ambient color.
         */
        const Color &getAmbient() const;

        /*!
         * Return material specular color.
         */
        const Color &getSpecular() const;

        /*!
         * Return material shininess.
         */
        float getShininess() const;

 private:
        /*!
         * Material ambient color.
         */
        Color ambient;

        /*!
         * Material specular color.
         */
        Color specular;

        /*!
         * Material shininess.
         */
        float shininess;
};

#endif
