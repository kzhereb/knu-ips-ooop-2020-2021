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
	virtual std::string get_description() = 0;
};

class Table: public Furniture {
private:
	int number_of_legs;
	int serial_number;
	static int max_number;
public:
	Table(int number_of_legs = 4, bool is_prototype = false): number_of_legs{number_of_legs} {
		if (! is_prototype) {
			max_number++;
			serial_number = max_number;
		} else {
			serial_number = -1;
		}
	}

	double get_height() override { return 80;}
	double get_weight() override { return 60 + 5*number_of_legs; }
	std::string get_material() override { return "wood";}
	std::shared_ptr<Furniture> clone() override {
		return std::make_shared<Table>(number_of_legs);
	}
	std::string get_description() {
		return get_material() + " table number " + std::to_string(serial_number)
			+ " with " + std::to_string(number_of_legs) + " legs";
	}
};

int Table::max_number = 0;

class Sofa: public Furniture {
private:
	int number_of_pillows;
	int serial_number;
	static int max_number;
public:
	Sofa(int number_of_pillows = 2, bool is_prototype = false ): number_of_pillows{number_of_pillows} {
		if (!is_prototype) {
			max_number++;
			serial_number = max_number;
		} else {
			serial_number = -1;
		}
	}

	double get_height() override { return 80 + 20 * number_of_pillows;}
	double get_weight() override { return 120 + 5 * number_of_pillows; }
	std::string get_material() override { return "leather";}
	std::shared_ptr<Furniture> clone() override {
		return std::make_shared<Sofa>(number_of_pillows);
	}
	std::string get_description() {
		return get_material() + " sofa number " + std::to_string(serial_number)
			+ " with " + std::to_string(number_of_pillows) + " pillows";
	}
};

int Sofa::max_number = 0;


TEST_CASE("creating objects with prototypes") {
	std::shared_ptr<Furniture> working_table = std::make_shared<Table>(4, true);
	std::shared_ptr<Furniture> garden_table = std::make_shared<Table>(3, true);
	std::shared_ptr<Furniture> regular_sofa = std::make_shared<Sofa>(4, true);

	auto table1 = working_table->clone();
	CHECK(table1->get_height() == 80);
	CHECK(table1->get_weight() == 80);
	CHECK(table1->get_description() == std::string("wood table number 1 with 4 legs"));

	auto table2 = garden_table->clone();
	CHECK(table2->get_height() == 80);
	CHECK(table2->get_weight() == 75);
	CHECK(table2->get_description() == std::string("wood table number 2 with 3 legs"));

	auto sofa1 = regular_sofa->clone();
	CHECK(sofa1->get_height() == 160);
	CHECK(sofa1->get_weight() == 140);
	CHECK(sofa1->get_description() == std::string("leather sofa number 1 with 4 pillows"));

	auto sofa2 = regular_sofa->clone();
	CHECK(sofa2->get_height() == 160);
	CHECK(sofa2->get_weight() == 140);
	CHECK(sofa2->get_description() == std::string("leather sofa number 2 with 4 pillows"));

}


