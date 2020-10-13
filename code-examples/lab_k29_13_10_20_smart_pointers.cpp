/*
 * lab_k29_13_10_20_smart_pointers.cpp
 *
 *  Created on: Oct 13, 2020
 *      Author: KZ
 */

#include "doctest.h"

#include <ostream>
#include <iostream>
#include <sstream>

class Test {
public:
	static std::ostream* out;
	Test() {*out<<"default constructor"<<std::endl;}
	~Test() {*out<<"destructor"<<std::endl;}
};
std::ostream* Test::out = nullptr;


TEST_CASE("smart pointers and object lifetime") {
	std::stringstream out;
	Test::out = &out;
	{
		Test test;
		CHECK(out.str() == "default constructor\n");
	}
	CHECK(out.str() == "default constructor\ndestructor\n");
}

