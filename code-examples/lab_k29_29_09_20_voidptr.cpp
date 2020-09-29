/*
 * lab_k29_29_09_20_voidptr.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: KZ
 */

#include "doctest.h"

#include <string>
#include <ostream>
#include <sstream>

struct Anything {
	void* data;
	std::string type;
};

std::ostream& operator<<(std::ostream& out, const Anything& any) {
	if (any.type == "Int") {
		int* int_data = (int*)any.data;
		out<<(*int_data);
	} else if (any.type == "String" || any.type == "Text") {
		std::string* str_data = (std::string*)any.data;
		out<<'"'<<*str_data<<'"';
	} else {
		out<< "unsupported type: "<<any.type;
	}
	return out;
}

TEST_CASE("working with void*") {

	SUBCASE("int") {
		int int_data = 123;
		Anything int_any{&int_data, "Int"};

		std::stringstream s_out;
		s_out<<int_any;
		CHECK(s_out.str() == "123");
	}

	SUBCASE("string") {
		std::string str_data = "hello world";
		Anything str_any{&str_data, "Text"};

		std::stringstream s_out;
		s_out<<str_any;
		CHECK(s_out.str() == "\"hello world\"");
	}

	SUBCASE("unknown") {
		Anything nothing{nullptr, "???"};
		std::stringstream s_out;
		s_out<<nothing;
		CHECK(s_out.str() == "unsupported type: ???");

	}


}
