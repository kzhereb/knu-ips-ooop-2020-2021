/*
 * lab_k28c_15_09_20_oop.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: KZ
 */

#include "doctest.h"

#include <string>


class Human {
private:
	double height; // in cm
	double weight; // in kg
	std::string name;
public:
	Human(double height, double weight, std::string name): height{height}, weight{weight}, name{name} { }
	double get_height() { return this->height;}
	bool is_tankist() { return height <= 170; }
};

TEST_CASE("creating human and accessing properties") {
	Human someone(170, 50, "Yehor");
	CHECK(someone.get_height() == 170);
	CHECK(someone.is_tankist());

	Human someone2(171, 50, "Andrii");
	CHECK(someone2.get_height() == 171);
	CHECK_FALSE(someone2.is_tankist());
}


