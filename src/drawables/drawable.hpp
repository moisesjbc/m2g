/***
 * Copyright 2013 - 2015 Moises J. Bonilla Caraballo (Neodivert)
 *
 * This file is part of M2G.
 *
 * M2G is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * M2G is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with M2G.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <tinyxml2.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#define GL_GLEXT_PROTOTYPES
extern "C" {
    #include <GL/gl.h>
}

namespace m2g {

struct Rect
{
    GLfloat x;
    GLfloat y;
    GLfloat width;
    GLfloat height;

    void loadFromXML( tinyxml2::XMLElement* xmlElement );
    bool collide( const Rect& b ) const ;
};

class Drawable
{
    protected:
        Rect boundaryBox;

    public:
        /***
         * 1. Initialization
         ***/
        Drawable();


        /***
         * 2. Getters and setters
         ***/
        GLfloat getX() const;
        glm::vec2 getPosition() const ;
        GLfloat getWidth() const ;
        GLfloat getHeight() const ;
        virtual const Rect* getBoundaryBox() const ;


        /***
         * 3. Transformations
         ***/
        virtual void translate( const float& tx, const float& ty );
        virtual void moveTo( const float& x, const float& y );


        /***
         * 4. Drawing
         ***/
        virtual void draw( const glm::mat4& projectionMatrix ) const = 0;
};


/***
 * 6. Auxiliar functions
 ***/

void checkOpenGL( const char* str );

typedef std::shared_ptr< Drawable > DrawablePtr;
typedef std::shared_ptr< const Drawable > DrawableConstPtr;

} // Namespace m2g

#endif // DRAWABLE_HPP
