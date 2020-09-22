/*
 * lab_k29_16_09_20_oop.cpp
 *
 *  Created on: Sep 16, 2020
 *      Author: KZ
 */

#include "doctest.h"
#include <stdexcept>


class Rational {
	int numerator;
	int denominator;
public:
	Rational(): numerator{0}, denominator{1} {}
	Rational(int numerator, int denominator): numerator{numerator}, denominator{denominator} {}

	int get_numerator() {return numerator;}
	int get_denominator() {return denominator;}
	void set_numerator(int numerator) { this->numerator = numerator; }
	void set_denominator(int denominator) {
		if (denominator == 0) {
			throw std::invalid_argument("denominator");
		}
		this->denominator = denominator;
	}
};

TEST_CASE("Rational numbers") {
	Rational q{10,11};
	CHECK(q.get_numerator()==10);
	CHECK(q.get_denominator()==11);

	SUBCASE("set numerator") {
		q.set_numerator(20);
		CHECK(q.get_numerator()==20);
		CHECK(q.get_denominator()==11);
	}
	SUBCASE("set denominator") {
		q.set_denominator(17);
		CHECK(q.get_numerator()==10);
		CHECK(q.get_denominator()==17);
	}
	SUBCASE("set denominator to 0 should fail") {
		try {
			q.set_denominator(0);
		} catch (const std::invalid_argument& ex) {
			//CHECK(ex.what()=="denominator"); //doesn't work like this - compares pointers
		}
		CHECK(q.get_numerator()==10);
		CHECK(q.get_denominator()==11);
	}
}
