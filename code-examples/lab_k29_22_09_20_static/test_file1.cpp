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
	CHECK(non_static_value == 123);

	static_value = 4560;
	non_static_value = 1230;

	CHECK(static_value == 4560);
	CHECK(non_static_value == 1230);

}


