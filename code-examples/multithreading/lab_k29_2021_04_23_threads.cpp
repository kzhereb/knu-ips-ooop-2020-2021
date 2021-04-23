/*
 * lab_k29_2021_04_23_threads.cpp
 *
 *  Created on: Apr 23, 2021
 *      Author: KZ
 */

#include "../doctest.h"
#include <vector>
#include <functional>
#include <thread>
#include <iostream>

std::vector<int> custom_transform_sequential(const std::vector<int>& input, std::function<int(int)> func) {
	std::size_t size = input.size();
	std::vector<int> result(size);
	for(std::size_t i = 0; i<size; i++) {
		result[i] = func(input[i]);
	}
	return result;
}

std::vector<int> custom_transform_parallel(const std::vector<int>& input, std::function<int(int)> func) {
	std::size_t size = input.size();
	std::vector<int> result(size);

	std::size_t num_threads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(num_threads);
	std::size_t thread_size = (size / num_threads)+1;
	std::size_t start = 0;
	for (std::size_t i=0; i<num_threads; i++) {
		threads[i] = std::thread(
				[=, &input, &result] () {
						//std::cout<<"worker thread "<<i<<" starts at "<<start<<std::endl;
						for(std::size_t j = start; j < std::min(start+thread_size, size); j++) {
							result[j] = func(input[j]);
						}
					}
				);
		start+= thread_size;
	}
	for (std::size_t i=0; i<num_threads; i++) {
		threads[i].join();
	}



	return result;
}


TEST_CASE("custom tranform - sequential and parallel") {
	std::vector<int> mylist {1, 2, 3, 4, 5};

	std::function<int(int)> square = [](int value) { return value*value; };

	std::vector<int> result;
	SUBCASE("sequential") {
		result = custom_transform_sequential(mylist, square);
	}
	SUBCASE("parallel") {
		result = custom_transform_parallel(mylist, square);
	}

	CHECK(result == std::vector<int>{1, 4, 9, 16, 25});
}

