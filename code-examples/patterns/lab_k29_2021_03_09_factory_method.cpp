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
	Transport() : number_of_seats(0) {}
	Transport(int number_of_seats) : number_of_seats(number_of_seats) {}
	virtual std::string get_info_booklet() = 0;
	int get_number_of_seats() { return number_of_seats;}
};


enum CarTypes { Sedan, SUV, Offroad };

class Car : public Transport {
private:
	CarTypes type;
	double weight; //in kg
	double engine_volume; // in liters
public:
	Car(): Transport(5), type{Sedan}, weight{1500}, engine_volume {1.5} {}
	std::string get_info_booklet() override {
		return "This is a great car";
	}

};

class Airplane : public Transport {
private:
	double max_altitude; // in meters
public:
	Airplane() : Transport(60), max_altitude{10000} {}
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

class MaintenanceCompany {
public:
	virtual int estimate_costs(std::shared_ptr<Transport> transport) = 0;
};

class CarMaintenanceCompany: public MaintenanceCompany {
public:
	int estimate_costs(std::shared_ptr<Transport> transport) {
		return transport->get_number_of_seats() * 1000;
	}
};

class AirplaneMaintenanceCompany: public MaintenanceCompany {
public:
	int estimate_costs(std::shared_ptr<Transport> transport) {
		return transport->get_number_of_seats() * 1e6;
	}
};

class TransportFactory {
public:
	virtual std::shared_ptr<Transport> create_transport() = 0;
	virtual std::shared_ptr<MaintenanceCompany> create_maintenance_company() = 0;
};

class CarFactory: public TransportFactory {
public:
	std::shared_ptr<Transport> create_transport() override {
		return std::make_shared<Car>();
	}
	std::shared_ptr<MaintenanceCompany> create_maintenance_company() override {
		return std::make_shared<CarMaintenanceCompany>();
	}
};

class AirplaneFactory: public TransportFactory {
public:
	std::shared_ptr<Transport> create_transport() override {
		return std::make_shared<Airplane>();
	}
	std::shared_ptr<MaintenanceCompany> create_maintenance_company() override {
		return std::make_shared<AirplaneMaintenanceCompany>();
	}
};

TEST_CASE("creating parallel hierarchies using Abstract Factory pattern") {
	std::shared_ptr<TransportFactory> factory = std::make_shared<CarFactory>();
	auto transport = factory->create_transport();
	auto company = factory->create_maintenance_company();
	CHECK(company->estimate_costs(transport) == 5000);

	factory = std::make_shared<AirplaneFactory>();
	transport = factory->create_transport();
	company = factory->create_maintenance_company();
	CHECK(company->estimate_costs(transport) == 6e7);
}
