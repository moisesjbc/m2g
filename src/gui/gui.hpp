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

#ifndef GUI_HPP
#define GUI_HPP

#include "widgets/widget.hpp"
#include <list>

namespace m2g {

class GUI : public Widget {
    public:
        /***
         * 1. Construction
         ***/
        GUI( SDL_Renderer* renderer, const Rect& boundaryRect );


        /***
         * 2. Widgets management
         ***/
        void addWidget( WidgetPtr widget );


        /***
         * 3. Event handling
         ***/
        virtual bool handleEvent( const SDL_Event &event );


        /***
         * 4. Drawing
         ***/
        virtual void draw() const;


    private:
        /***
         * 5. Layout
         ***/
        void updateLayout();


        /***
         * Attributes
         ***/
        std::list< WidgetPtr > widgets_;
};

} // namespace m2g

#endif // GUI_HPP
