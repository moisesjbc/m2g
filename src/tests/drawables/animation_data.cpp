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

#include <catch.hpp>
#include "../../drawables/animation_data.hpp"
#include <vector>

namespace m2g {

TEST_CASE( "Animation references its tileset" )
{
    Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );

    REQUIRE( &( animData.tileset() ) == &tileset );
}


TEST_CASE( "AnimationData returns its refresh rate" )
{
    Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );

    SECTION( "AnimationData returns its refresh rate (default value)" )
    {
        AnimationData animData( tileset );
        REQUIRE( animData.refreshRate() == DEFAULT_ANIMATION_REFRESH_RATE );
    }

    SECTION( "AnimationData returns its refresh rate (given value)" )
    {
        AnimationData animData( tileset, 30 );
        REQUIRE( animData.refreshRate() == 30 );
    }
}


TEST_CASE( "Animation states management" )
{
    Tileset tileset( "./data/tileset_w64_h64.png", 32, 32 );
    AnimationData animData( tileset );

    SECTION( "AnimationState addition to AnimationData" ){
        std::vector< AnimationState > animStates =
        {
            { 0, 1, 0 },
            { 2, 2, 1 },
            { 1, 2, 2 }
        };

        for( const AnimationState& animState : animStates ){
            animData.addState( animState );
        }

        for( unsigned int i = 0; i < animStates.size(); i++ ){
            REQUIRE( animData.state( i ) == animStates[i] );
        }
    }


    SECTION( "AnimationState returns its number of states" )
    {
        std::vector< AnimationState > animStates =
        {
            { 0, 1, 0 },
            { 2, 2, 1 },
            { 1, 2, 2 }
        };

        unsigned int nExpectedStates = 0;
        REQUIRE( animData.nStates() == nExpectedStates );

        for( const AnimationState& animState : animStates ){
            animData.addState( animState );
            nExpectedStates++;

            REQUIRE( animData.nStates() == nExpectedStates );
        }
    }


    SECTION( "AnimationState with an out-of-range lastFrame can't be added to an AnimationData" )
    {
        AnimationState animState( 0, 5 );
        REQUIRE_THROWS_AS( animData.addState( animState ), std::out_of_range );
    }


    SECTION( "Attemp to retrieve an out-of-range state must throw" )
    {
        AnimationState animState( 0, 1 );

        REQUIRE_THROWS_AS( animData.state( 0 ), std::out_of_range );

        animData.addState( animState );
        REQUIRE_NOTHROW( animData.state( 0 ) );
        REQUIRE_THROWS_AS( animData.state( 1 ), std::out_of_range );
    }
}

} // namespace m2g
