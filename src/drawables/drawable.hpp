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

#include "../utilities/rect.hpp"
#include <memory> // shared_ptr
#include <glm/vec2.hpp>
#include <SDL2/SDL.h>

namespace m2g {

// TODO: Move non-drawing methods to classes Collidable or Sprite.
// TODO: Remove attributes and use a default constructor so
// users of virtually-derived classes doesn't have to call the
// constructor explicitlly.
class Drawable
{
    protected:
        SDL_Renderer* renderer_;
        Rect boundaryBox;

    public:
        /***
         * 1. Initialization
         ***/
        Drawable( SDL_Renderer* renderer );


        /***
         * 2. Getters and setters
         ***/
        int getX() const;
        glm::ivec2 getPosition() const ;
        unsigned int getWidth() const ;
        unsigned int getHeight() const ;
        Rect getBoundaryBox() const ;


        /***
         * 3. Transformations
         ***/
        virtual void translate( int tx, int ty );
        virtual void moveTo( int x, int y );


        /***
         * 4. Drawing
         ***/
        virtual void draw() const = 0;
};

typedef std::shared_ptr< Drawable > DrawablePtr;
typedef std::shared_ptr< const Drawable > DrawableConstPtr;

} // Namespace m2g

#endif // DRAWABLE_HPP
