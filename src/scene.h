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

//!\file scene.h
//!Declaration of Scene class.

#ifndef SCENE_H
#define SCENE_H 1

#include <string>
#include "object.h"
#include "rotation.h"

//! Scene description.
/*!
 * This class represents description of scene contents.
 */
class Scene {
 public:
        /*!
         * Construct an object of Scene class given filenames with
         * descriptions of geometry that has visualized score mapped
         * onto itself (geometry that is mapped) and geometry that is
         * rendered as is (geometry that is not mapped).
         */
        Scene(const std::string &, const std::string &);

        /*!
         * Return scene object that is mapped.
         */
        Object &getMapped();

        /*!
         * Return scene object that is not mapped.
         */
        const Object &getNotMapped() const;

        /*!
         * Return scene cumulative rotation.
         */
        const Rotation &getRotation() const;

        /*!
         * Set scene cumulative rotation.
         */
        void setRotation(const Rotation &);

        /*!
         * Draw scene using OpenGL commands.
         */
        void render(const int, const int) const;

 private:
        /*!
         * Scene object that is mapped.
         */
        Object mapped;

        /*!
         * Scene object that is not mapped.
         */
        Object notMapped;

        /*!
         * Scene cumulative rotation.
         */
        Rotation rotation;
};

#endif
