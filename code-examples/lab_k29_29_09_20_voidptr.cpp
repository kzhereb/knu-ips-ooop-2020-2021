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
#include <iostream>

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

TEST_CASE("getting addresses") {

	SUBCASE("int") {
		int value = 123;
		int* ptr = &value;
		//std::cout<< "value = "<<value<<", address = "<<ptr<<std::endl;
		SUBCASE("value") {
			std::stringstream s_out;
			s_out<<value;
			CHECK(s_out.str() == "123");
		}
		SUBCASE("ptr") {
			std::stringstream s_out;
			s_out<<ptr;
			CHECK(s_out.str().substr(0,2) == "0x");
		}

		SUBCASE("value as ptr") {
			std::stringstream s_out;
			s_out<<(void*)value;
			CHECK(s_out.str() == "0x7b");
		}

	}

	char cvalue = 'a';
	char* cptr = &cvalue;
	//std::cout<< "value = "<<cvalue<<", address = "<<cptr<<std::endl; //error - tries to treat char* as 0-terminated string
	//std::cout<< "value = "<<cvalue<<", address = "<<(void*)cptr<<std::endl;


}
