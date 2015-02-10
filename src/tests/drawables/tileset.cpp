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

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include "../../drawables/tileset.hpp"

TEST_CASE( "Tileset is created properly" )
{
    REQUIRE_NOTHROW( m2g::Tileset( ".data/tileset_w32_h64.png" , 32, 64 ); );
}


TEST_CASE( "Tileset gives right tile dimensions (different components)" )
{
    m2g::Tileset tileset( ".data/test_tileset.png", 32, 64 );

    const sf::Vector2u tileDimensions = tileset.tileDimensions();

    REQUIRE( tileDimensions.x == 32 );
    REQUIRE( tileDimensions.y == 64 );
}


TEST_CASE( "Tileset gives right tile dimensions (equal components)" )
{
    m2g::Tileset tileset( ".data/test_tileset.png", 32, 32 );

    const sf::Vector2u tileDimensions = tileset.tileDimensions();

    REQUIRE( tileDimensions.x == 32 );
    REQUIRE( tileDimensions.y == 32 );
}