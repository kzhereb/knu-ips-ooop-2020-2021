/*
 * lab_k29_2021_03_09_factory_method.cpp
 *
 *  Created on: Mar 9, 2021
 *      Author: KZ
 */

#include "../doctest.h"

#include <string>
#include <memory>


class Transport {
protected:
	int number_of_seats;
public:
	virtual std::string get_info_booklet() = 0;
};


enum CarTypes { Sedan, SUV, Offroad };

class Car : public Transport {
private:
	CarTypes type;
	double weight; //in kg
	double engine_volume; // in liters
public:
	std::string get_info_booklet() override {
		return "This is a great car";
	}

};

class Airplane : public Transport {
private:
	double max_altitude; // in meters
public:
	std::string get_info_booklet() override {
		return "Our airplanes never crash!";
	}
};

class TripPlanner {
private:
	std::string from;
	std::string to;
	static constexpr double MAX_DISTANCE_CAR = 1000;



public:
	TripPlanner(std::string from, std::string to): from{from}, to{to} {}
	std::shared_ptr<Transport> get_transport() {
		double distance = get_distance(from, to);
		if (distance > MAX_DISTANCE_CAR) {
			return std::make_shared<Airplane>();
		} else {
			return std::make_shared<Car>();
		}
	}

	static double get_distance(std::string from, std::string to) {
		return from.size() * to.size() * 50;
	}
};

TEST_CASE("creating transport using factory method") {
	TripPlanner planner{"Kyiv", "Odessa"};
	CHECK(TripPlanner::get_distance("Kyiv", "Odessa") == 1200 );
	auto transport = planner.get_transport();
	CHECK(transport->get_info_booklet() == std::string("Our airplanes never crash!"));
}

