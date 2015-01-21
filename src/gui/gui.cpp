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

#include <tinyxml2.h>
#include "gui.hpp"

namespace m2g {

/***
 * 1. Construction
 ***/

GUI::GUI(SDL_Renderer *renderer, const Rect& boundaryRect) :
    Drawable( renderer ),
    Widget( renderer )
{
    this->boundaryBox = boundaryRect;
}


/***
 * 1. Widgets management
 ***/

void GUI::addWidget( WidgetPtr widget )
{
    widgets_.push_back( std::move( widget ) );
    updateLayout();
}


/***
 * 2. Event handling
 ***/

bool GUI::handleEvent( const SDL_Event &event )
{
    for( WidgetPtr& widget : widgets_ ){
        if( widget->handleEvent( event ) ){
            return true;
        }
    }
    return false;
}


/***
 * 3. Drawing
 ***/

void GUI::draw() const
{
    for( const WidgetPtr& widget : widgets_ ){
        widget->draw();
    }
}


/***
 * 5. Layout
 ***/

void GUI::updateLayout()
{
    // TODO: Implement according to GUI's vertical and horizontal align.
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int guiHeight = 0;

    // Get the total height of the widgets in the GUI. Use this to set a
    // central vertical align.
    for( const WidgetPtr& widget : widgets_ ){
        guiHeight += widget->getHeight();
    }
    y = boundaryBox.y;
    if( boundaryBox.height > guiHeight ){
        y += ( ( boundaryBox.height - guiHeight ) >> 1 );
    }


    // Update the position of every widget in the GUI.
    for( WidgetPtr& widget : widgets_ ){
        x = boundaryBox.x;
        if( boundaryBox.width > widget->getWidth() ){
            x += ( ( boundaryBox.width - widget->getWidth() ) >> 1 );
        }
        widget->moveTo( x, y );
        y += widget->getHeight();
    }
}

} // namespace m2g