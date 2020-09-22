/*
 * test_file1.cpp
 *
 *  Created on: Sep 22, 2020
 *      Author: KZ
 */

#include "test_static.h"
#include "../doctest.h"

TEST_CASE("static in namespace") {
	CHECK(static_value == 456);
	CHECK(non_static_value == 1230); //already set in test_file1.cpp

	static_value = 4561;
	non_static_value = 1231;

	CHECK(static_value == 4561);
	CHECK(non_static_value == 1231);

}


