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
//private:
//	static const Rational _one;
public:
	Rational(): numerator{0}, denominator{1} {}
	Rational(int numerator, int denominator): numerator{numerator}, denominator{denominator} {}

	int get_numerator() const {return numerator;}
	int get_denominator() const {return denominator;}
	void set_numerator(int numerator) { this->numerator = numerator; }
	void set_denominator(int denominator) {
		if (denominator == 0) {
			throw std::invalid_argument("denominator");
		}
		this->denominator = denominator;
	}

	static const Rational zero;

	static const Rational one() {
		static const Rational _one{1,1};
		return _one;
	}
	static int GCD(int a, int b) {
		// this->zero; //this is unavailable in static methods
		// Rational::zero; //static fields are available
		return b ? GCD (b, a % b) : a;
	}

};

const Rational Rational::zero{0,1};
//const Rational Rational::_one{1,1};

const Rational zero{0,1};

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

TEST_CASE("Rational constants") {
	Rational zero1{0,1}, zero2{0,1};
	CHECK(&zero1 != &zero2);

	CHECK(zero1.get_numerator() == 0);
	CHECK(zero1.get_denominator() == 1);
	CHECK(zero2.get_numerator() == 0);
	CHECK(zero2.get_denominator() == 1);

	CHECK(zero.get_numerator() == 0);
	CHECK(zero.get_denominator() == 1);

	CHECK(Rational::zero.get_numerator() == 0);
	CHECK(Rational::zero.get_denominator() == 1);

	// static fields and methods can also be called from instance
	CHECK(zero1.zero.get_numerator() == 0);
	CHECK(zero1.zero.get_denominator() == 1);

	// but they are not stored in each instance - sizeof only includes instance fields
	CHECK(sizeof(Rational) == 2*sizeof(int));

	CHECK(Rational::one().get_numerator() == 1);
	CHECK(Rational::one().get_denominator() == 1);

}

TEST_CASE("Static methods") {
	CHECK(Rational::GCD(10, 15) == 5);
	CHECK(Rational::GCD(10, 17) == 1);
	CHECK(Rational::GCD(0, 17) == 17);
	CHECK(Rational::GCD(17, 0) == 17);
	CHECK(Rational::GCD(0, 0) == 0);
}

class Empty {
public:
	static const int zero;
};
const int Empty::zero = 0;

TEST_CASE("Empty class") {
	CHECK(Empty::zero==0);
	CHECK(sizeof(Empty) > 0);
	WARN(sizeof(Empty) == 1); // not required?
}
