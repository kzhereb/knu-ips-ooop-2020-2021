/*
 * func_test.cpp
 *
 *  Created on: Sep 25, 2020
 *      Author: KZ
 */

#include "func.h"

#include "../doctest.h"


TEST_CASE("[template] - template function") {
	int result = square(5);
	CHECK(result == 25);

	CHECK(square<double>(0.5) == 0.25); // power of 2 - can compare exactly
	CHECK(square<double>(0.1) == doctest::Approx(0.01));
}
