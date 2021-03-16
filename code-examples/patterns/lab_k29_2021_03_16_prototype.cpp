/*
 * lab_k29_2021_03_16_prototype.cpp
 *
 *  Created on: Mar 16, 2021
 *      Author: KZ
 */

#include "../doctest.h"

#include <memory>
#include <string>

class Furniture {
public:
	virtual double get_height() = 0; // in cm
	virtual double get_weight() = 0; // in kg
	virtual std::string get_material() = 0;
	virtual std::shared_ptr<Furniture> clone() = 0;
};

class Table: public Furniture {
private:
	int number_of_legs;
public:
	Table(int number_of_legs = 4): number_of_legs{number_of_legs} {}

	double get_height() override { return 80;}
	double get_weight() override { return 60 + 5*number_of_legs; }
	std::string get_material() override { return "wood";}
	std::shared_ptr<Furniture> clone() override {
		return std::make_shared<Table>(number_of_legs);
	}
};

class Sofa: public Furniture {
private:
	int number_of_pillows;
public:
	Sofa(int number_of_pillows = 2): number_of_pillows{number_of_pillows} {}

	double get_height() override { return 80 + 20 * number_of_pillows;}
	double get_weight() override { return 120 + 5 * number_of_pillows; }
	std::string get_material() override { return "leather";}
	std::shared_ptr<Furniture> clone() override {
		return std::make_shared<Sofa>(number_of_pillows);
	}
};

TEST_CASE("creating objects with prototypes") {
	std::shared_ptr<Furniture> working_table = std::make_shared<Table>();
	std::shared_ptr<Furniture> garden_table = std::make_shared<Table>(3);
	std::shared_ptr<Furniture> regular_sofa = std::make_shared<Sofa>(4);

	auto table1 = working_table->clone();
	CHECK(table1->get_height() == 80);
	CHECK(table1->get_weight() == 80);

	auto table2 = garden_table->clone();
	CHECK(table2->get_height() == 80);
	CHECK(table2->get_weight() == 75);

	auto sofa1 = regular_sofa->clone();
	CHECK(sofa1->get_height() == 160);
	CHECK(sofa1->get_weight() == 140);

	auto sofa2 = regular_sofa->clone();
	CHECK(sofa2->get_height() == 160);
	CHECK(sofa2->get_weight() == 140);

}


