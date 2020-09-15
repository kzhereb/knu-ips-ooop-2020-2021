/*
 * lab_k29_15_09_2020_doctest.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: KZ
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cassert>
#include <vector>


int factorial(int number) {
	assert(number>=0);
	return number <= 1 ? 1 : factorial(number - 1) * number;
}

TEST_CASE("testing the factorial function") {
	CHECK(factorial(0) == 1);
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(10) == 3628800);
}

TEST_CASE("vectors can be sized and resized") {
    std::vector<int> v(5);

    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 5);

    SUBCASE("adding to the vector increases it's size") {
        v.push_back(1);

        CHECK(v.size() == 6);
        CHECK(v.capacity() >= 6);
    }
    SUBCASE("reserving increases just the capacity") {
        v.reserve(6);

        CHECK(v.size() == 5);
        CHECK(v.capacity() >= 6);
    }
}
