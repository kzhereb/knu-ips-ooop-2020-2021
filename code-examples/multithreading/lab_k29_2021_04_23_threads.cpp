/*
 * lab_k29_2021_04_23_threads.cpp
 *
 *  Created on: Apr 23, 2021
 *      Author: KZ
 */

#include "../doctest.h"
#include <vector>
#include <functional>

std::vector<int> custom_transform_sequential(const std::vector<int>& input, std::function<int(int)> func) {
	std::size_t size = input.size();
	std::vector<int> result(size);
	for(std::size_t i = 0; i<size; i++) {
		result[i] = func(input[i]);
	}
	return result;
}

TEST_CASE("custom tranform - sequential and parallel") {
	std::vector<int> mylist {1, 2, 3, 4, 5};

	std::function<int(int)> square = [](int value) { return value*value; };

	std::vector<int> result = custom_transform_sequential(mylist, square);

	CHECK(result == std::vector<int>{1, 4, 9, 16, 25});
}

