/*
 * func.cpp
 *
 *  Created on: Sep 25, 2020
 *      Author: KZ
 */

#include "func.h"

#include "../doctest.h"

template<typename T>
T square(T value) {
	return value*value;
}

TEST_CASE("[template] - template function") {
	int result = square(5);
	CHECK(result == 25);

	CHECK(square<double>(0.5) == 0.25); // power of 2 - can compare exactly
	CHECK(square<double>(0.1) == doctest::Approx(0.01));
}
