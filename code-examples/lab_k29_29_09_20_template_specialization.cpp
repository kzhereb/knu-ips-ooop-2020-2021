/*
 * lab_k29_29_09_20_template_specialization.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: KZ
 */

#include "doctest.h"

#include <vector>
#include <ostream>
#include <sstream>

template<typename T>
void print_sum(std::ostream& out, const std::vector<T>& items) {
	out<<"[ ";
	for (const auto& item:items) {
		out<<item<<" ";
	}
	out<<"]";
}

template<>
void print_sum(std::ostream& out, const std::vector<int>& items) {
	int result = 0;
	for (auto item:items) {
		result += item;
	}
	out<<result;
}

TEST_CASE("template specializations") {
	SUBCASE(" generic ") {
		std::vector<std::string> strings{"abc", "123", "???"};
		std::stringstream s_out;
		print_sum(s_out, strings);
		CHECK(s_out.str() == "[ abc 123 ??? ]");
	}
	SUBCASE("int") {
		std::vector<int> items{1, 3, 5};
		std::stringstream s_out;
		print_sum(s_out, items);
		CHECK(s_out.str() == "9");
	}
}
