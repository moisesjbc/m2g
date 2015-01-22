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

#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <SDL2/SDL_ttf.h>
#include <map>
#include <vector>
#include "../utilities/alignment.hpp"

namespace m2g {

class TextRenderer
{
    public:
        /***
         * 1. Initialization and destruction
         ***/
        TextRenderer( SDL_Renderer* renderer );
        ~TextRenderer();


        /***
         * 2. Fonts management
         ***/
        unsigned int loadFont( const char* fontPath,
                               int fontSize );


        /***
         * 3. Drawing
         ***/
        void drawText( const char* text,
                       unsigned int fontIndex,
                       const SDL_Color& color,
                       int x,
                       int y,
                       HorizontalAlign textAlign = HorizontalAlign::LEFT ) const;

        void renderTextToSurface( const char* text,
                                  unsigned int fontIndex,
                                  const SDL_Color& color,
                                  SDL_Surface* textSurface,
                                  const SDL_Rect& textRect,
                                  HorizontalAlign horizontalAlign = HorizontalAlign::LEFT,
                                  VerticalAlign verticalAlign = VerticalAlign::MIDDLE ) const;

        SDL_Surface* renderTextToSurface( const char* text,
                                          unsigned int fontIndex,
                                          const SDL_Color &color,
                                          HorizontalAlign textAlign ) const;


        /***
         * 4. Auxiliar methods
         ***/
        SDL_Renderer* renderer() const;
    private:
        void getTextDimensions( TTF_Font* font, const char* text, int& textWidth, int& textHeight, std::vector< std::string >& lines ) const;

        SDL_Renderer *renderer_;
        std::map< unsigned int, TTF_Font* > fonts_;
        unsigned int nextFontID_;
};

} // namespace m2g

#endif // TEXT_RENDERER_HPP
