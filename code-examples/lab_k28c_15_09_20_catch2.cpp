/*
 * lab_k28c_15_09_20_catch2.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: KZ
 */

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? 1 : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
	REQUIRE( Factorial(0) == 1 );
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

