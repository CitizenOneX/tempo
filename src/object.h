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

//!\file object.h
//!Declaration of Object class.

#ifndef OBJECT_H
#define OBJECT_H 1

#include <string>
#include <vector>
#include "bounding_box.h"
#include "material.h"
#include "triangle.h"
#include "vector.h"
#include "vertex.h"

//! Geometry object.
/*!
 * This class represents a geometry object in scene.
 */
class Object {
 public:
        /*!
         * Construct an object of Object class given filename with
         * object description.  Object file format is described in
         * "Hacking" section of manual.
         */
        Object(const std::string &);

        /*!
         * Return object bounding box.
         */
        const BoundingBox &getBoundingBox() const;

        /*!
         * Return object vertices array.
         */
        std::vector<Vertex> &getVertices();

        /*!
         * Draw object using OpenGL commands.
         */
        void render() const;

 private:
        /*!
         * Object bounding box.
         */
        BoundingBox boundingBox;

        /*!
         * Object vertices array.
         */
        std::vector<Vertex> vertices;

        /*!
         * Object vertices normals array.
         */
        std::vector<Vector> normals;

        /*!
         * Object materials array.
         */
        std::vector<Material> materials;

        /*!
         * Object triangles array.
         */
        std::vector<Triangle> triangles;
};

#endif
