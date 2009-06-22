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

//!\file object.cpp
//!Definition of Object class.

#include <fstream>
#include <GL/gl.h>
#include "exception.h"
#include "object.h"

Object::Object(const std::string &name)
{
        /* Open file with object description. */
        std::ifstream stream(name.c_str());
        if (!stream)
                throw Exception(Exception::INVALID_OBJECT_FILE);

        float x, y, z;
        float r, g, b;
        int count;
        int i;

        /* Read and remember object bounding box. */
        stream >> x >> y >> z;
        if (!stream)
                throw Exception(Exception::INVALID_OBJECT_FILE);
        Vector lo(x, y, z);
        stream >> x >> y >> z;
        if (!stream)
                throw Exception(Exception::INVALID_OBJECT_FILE);
        Vector hi(x, y, z);
        boundingBox = BoundingBox(lo, hi);

        /* Read and remember object vertices. */
        stream >> count;
        for (i = 0; i < count; i++) {
                stream >> x >> y >> z;
                if (!stream)
                        throw Exception(Exception::INVALID_OBJECT_FILE);
                Vector point(x, y, z);

                stream >> r >> g >> b;
                if (!stream)
                        throw Exception(Exception::INVALID_OBJECT_FILE);
                Color color(r, g, b);

                Vertex vertex(point, color);
                vertices.push_back(vertex);
        }

        /* Read and remember object vertices normals. */
        stream >> count;
        for (i = 0; i < count; i++) {
                stream >> x >> y >> z;
                if (!stream)
                        throw Exception(Exception::INVALID_OBJECT_FILE);
                Vector normal(x, y, z);

                normals.push_back(normal);
        }

        /* Read and remember object materials. */
        stream >> count;
        for (i = 0; i < count; i++) {
                stream >> r >> g >> b;
                if (!stream)
                        throw Exception(Exception::INVALID_OBJECT_FILE);
                Color ambient(r, g, b);

                stream >> r >> g >> b;
                if (!stream)
                        throw Exception(Exception::INVALID_OBJECT_FILE);
                Color specular(r, g, b);

                float shininess;
                stream >> shininess;
                if (!stream)
                        throw Exception(Exception::INVALID_OBJECT_FILE);

                Material material(ambient, specular, shininess);
                materials.push_back(material);
        }

        /* Read and remember object triangles. */
        stream >> count;
        for (i = 0; i < count; i++) {
                int v0, v1, v2;
                stream >> v0 >> v1 >> v2;
                if (!stream)
                        throw Exception(Exception::INVALID_OBJECT_FILE);

                int n0, n1, n2;
                stream >> n0 >> n1 >> n2;
                if (!stream)
                        throw Exception(Exception::INVALID_OBJECT_FILE);

                int m;
                stream >> m;
                if (!stream)
                        throw Exception(Exception::INVALID_OBJECT_FILE);

                Triangle triangle(v0, v1, v2, n0, n1, n2, m);
                triangles.push_back(triangle);
        }
}

const BoundingBox &
Object::getBoundingBox() const
{
        /* Return bounding box. */
        return boundingBox;
}

std::vector<Vertex> &
Object::getVertices()
{
        /* Return vertices array. */
        return vertices;
}

void
Object::render() const
{
        /* Draw triangles comprising object. */
        glBegin(GL_TRIANGLES);
        int size = triangles.size();
        for (int i = 0; i < size; i++) {
                /* Apply current triangle material parameters. */
                Material material = materials[triangles[i].getM()];
                GLfloat coefficients[3];
                
                const Color &ambient = material.getAmbient();
                coefficients[0] = ambient.getR();
                coefficients[1] = ambient.getG();
                coefficients[2] = ambient.getB();
                glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, coefficients);

                const Color &specular = material.getSpecular();
                coefficients[0] = specular.getR();
                coefficients[1] = specular.getG();
                coefficients[2] = specular.getB();
                glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, coefficients);

                glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.getShininess());

                /* Draw triangle.  Sequence of commands below is
                   intentionaly left as is, without any OpenGL
                   optimizations, for simplicity.*/
                int v[3] = { triangles[i].getV0(), triangles[i].getV1(), triangles[i].getV2() };
                int n[3] = { triangles[i].getN0(), triangles[i].getN1(), triangles[i].getN2() };
                for (int j = 0; j < 3; j++) {
                        const Color &color = vertices[v[j]].getColor();
                        const Vector &point = vertices[v[j]].getPoint();
                        const Vector &normal = normals[n[j]];
                        glColor3f(color.getR(), color.getG(), color.getB());
                        glNormal3f(normal.getX(), normal.getY(), normal.getZ());
                        glVertex3f(point.getX(), point.getY(), point.getZ());
                }
        }
        
        glEnd();
}
