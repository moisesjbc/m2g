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

#include "text_renderer.hpp"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

namespace m2g {


/***
 * 1. Initialization and destruction
 ***/

TextRenderer::TextRenderer( SDL_Renderer *renderer ) :
    renderer_( renderer ),
    nextFontID_( 0 )
{}


TextRenderer::~TextRenderer()
{
    for( auto& font : fonts_ ){
        TTF_CloseFont( font.second );
    }
}


/***
 * 2. Fonts management
 ***/

unsigned int TextRenderer::loadFont( const char *fontPath, int fontSize )
{
    TTF_Font* newFont =
            TTF_OpenFont( fontPath, fontSize );
    if( !newFont ){
        throw std::runtime_error( TTF_GetError() );
    }

    fonts_[nextFontID_] = newFont;

    return nextFontID_++;
}


/***
 * 3. Drawing
 ***/

void TextRenderer::drawText( const char *text,
                             unsigned int fontIndex,
                             const SDL_Color &color,
                             int x,
                             int y,
                             HorizontalAlign textAlign ) const
{
    SDL_Surface* textSurface =
            renderTextToSurface( text,
                                 fontIndex,
                                 color,
                                 textAlign );

    SDL_Texture* textTexture =
            SDL_CreateTextureFromSurface( renderer_, textSurface );

    SDL_Rect textRect =
    {
        0, 0, textSurface->w, textSurface->h
    };

    SDL_RenderCopy( renderer_, textTexture, nullptr, &textRect );

    SDL_FreeSurface( textSurface );
    SDL_DestroyTexture( textTexture );
}


SDL_Rect TextRenderer::renderTextToSurface( const char *text,
                                        unsigned int fontIndex,
                                        const SDL_Color &color,
                                        SDL_Surface *textSurface,
                                        const SDL_Rect &textRect,
                                        HorizontalAlign horizontalAlign,
                                        VerticalAlign verticalAlign ) const
{
    TTF_Font* font = nullptr;
    SDL_Surface* lineSurface = nullptr;
    std::vector< std::string > lines;
    SDL_Rect dstRect = { 0, 0, 0, 0 };
    int textWidth, textHeight;

    // Load the required font.
    font = fonts_.at( fontIndex );

    // Get the text dimensions.
    getTextDimensions( font, text, textWidth, textHeight, lines );

    //auxTextSurface = SDL_ConvertSurface( auxTextSurface, textSurface->format, textSurface->flags );

    // Prepare the final text surface for the blitting.
    SDL_FillRect( textSurface, nullptr, 0 );
    SDL_SetSurfaceBlendMode( lineSurface, SDL_BLENDMODE_NONE );

    // Give the text the given align.
    dstRect.y = textRect.y;
    switch( verticalAlign ){
        case VerticalAlign::TOP:
        break;
        case VerticalAlign::MIDDLE:
            // FIXME: Check when textSurface->h > textHeight.
            dstRect.y += ( textSurface->h - textHeight ) >> 1;
        break;
        case VerticalAlign::BOTTOM:
            // FIXME: Check when textSurface->h > textHeight.
            dstRect.y += textSurface->h - textHeight;
        break;
    }

    // Render every line and blit it to the final surface.
    for( const std::string& line : lines ){
        // Generate a surface with the text line.
        lineSurface = TTF_RenderText_Blended( font, line.c_str(), color );

        // Give the text the given align.
        // TODO: Change so the switch is executed only once.

        switch( horizontalAlign ){
            case HorizontalAlign::LEFT:
                dstRect.x = 0;
            break;
            case HorizontalAlign::CENTER:
                // FIXME: Check when textWidth > lineSurface.
                dstRect.x = (textWidth >> 1) - (lineSurface->w >> 1);
            break;
            case HorizontalAlign::RIGHT:
                // FIXME: Check when textWidth > lineSurface.
                dstRect.x = textWidth - lineSurface->w;
            break;
        }
        dstRect.x += textRect.x;

        // Blit the line surface to its final surface.
        // FIXME: Check when line's width > textRect.w.
        // FIXME: Check when line's heigh > textRect.h.
        // (*) Update dstRect.w and dst.Rect.h
        SDL_BlitSurface( lineSurface, nullptr, textSurface, &dstRect );

        //
        dstRect.y += TTF_FontHeight( font );
    }

    return dstRect;
}


SDL_Surface *TextRenderer::renderTextToSurface( const char *text,
                                                unsigned int fontIndex,
                                                const SDL_Color &color,
                                                HorizontalAlign textAlign,
                                                SDL_Rect* textRect ) const
{
    std::vector< std::string > lines;
    int textWidth, textHeight;
    int pow2;

    // Set the RGBA mask for the text surface.
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        const Uint32 rmask = 0xff000000;
        const Uint32 gmask = 0x00ff0000;
        const Uint32 bmask = 0x0000ff00;
        const Uint32 amask = 0x000000ff;
    #else
        const Uint32 rmask = 0x000000ff;
        const Uint32 gmask = 0x0000ff00;
        const Uint32 bmask = 0x00ff0000;
        const Uint32 amask = 0xff000000;
    #endif

    // Load font.
    TTF_Font* font = fonts_.at( fontIndex );

    // Get the text dimensions.
    // FIXME: Duplicated code (in next call to renderTextToSurface.
    getTextDimensions( font, text, textWidth, textHeight, lines );

    // Round text dimensions to nearest upper pow of two.
    pow2 = 1;
    while( pow2 < textWidth ){
        pow2 <<= 1;
    }
    textWidth = pow2;

    pow2 = 1;
    while( pow2 < textHeight ){
        pow2 <<= 1;
    }
    textHeight = pow2;

    // Create the final text surface with the power-of-two dimensions.
    SDL_Surface* textSurface =
            SDL_CreateRGBSurface( 0, textWidth, textHeight, 32, rmask, gmask, bmask, amask );

    SDL_Rect rect =
    {
        0,
        0,
        textWidth,
        textHeight
    };

    SDL_Rect textRect_ =
            renderTextToSurface( text,
                                 fontIndex,
                                 color,
                                 textSurface,
                                 rect,
                                 textAlign );
    if( textRect != nullptr ){
        *textRect = textRect_;
    }

    return textSurface;
}


SDL_Renderer *TextRenderer::renderer() const
{
    return renderer_;
}


/***
 * 4. Auxiliar methods
 ***/

void TextRenderer::getTextDimensions( TTF_Font* font, const char* text, int& textWidth, int& textHeight, std::vector< std::string >& lines ) const
{
    char textLine[128];
    int lineWidth;
    unsigned int i;

    // Initialize the text dimensions to 0.
    textWidth = 0;
    textHeight = 0;
    lines.clear();

    // Iterate over the given text, extracting and getting the dimensions of
    // its lines.
    textWidth = 0;
    while( *text ){

        // Extract the next line and insert it in the vector of lines.
        i = 0;
        while( *text && ( *text != '\n' ) ){
            // TODO: Process also character "\ " for multiple lines (CR).
            textLine[i] = *text;

            text++;
            i++;
        }
        textLine[i] = 0;
        lines.push_back( std::string( textLine ) );

        // Get the line dimensions.
        TTF_SizeText( font, textLine, &lineWidth, nullptr );

        // Set the maximum line width as the text one.
        if( lineWidth > textWidth ){
            textWidth = lineWidth;
        }

        // Discard \n.
        if( *text == '\n' ){
            text++;
        }
    }

    // Compute the text height by multiplying the font height by the numer of
    // lines in the text.
    textHeight = TTF_FontHeight( font ) * lines.size();
}

} // namespace m2g
