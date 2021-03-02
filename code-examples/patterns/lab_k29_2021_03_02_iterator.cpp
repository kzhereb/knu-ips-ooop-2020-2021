/*
 * lab_k29_2021_03_02_iterator.cpp
 *
 *  Created on: Mar 2, 2021
 *      Author: KZ
 */

#include "../doctest.h"

#include <algorithm>
#include <iterator>
#include <vector>


TEST_CASE("std::copy using iterators") {
	std::vector<int> source {1, 3, 5, 7, 9};
	std::vector<int> destination;
	SUBCASE("using std::back_inserter") {
		std::copy(source.begin(), source.end(), std::back_inserter(destination));
	}
	SUBCASE("set size") {
		destination.resize(source.size());
		std::copy(source.begin(), source.end(), destination.begin());
	}
	CHECK(destination.size() == source.size());
	CHECK(destination[0] == source[0]);
}


