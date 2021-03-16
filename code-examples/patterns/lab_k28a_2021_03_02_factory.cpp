/*
 * lab_k28a_2021_03_02_factory.cpp
 *
 *  Created on: Mar 2, 2021
 *      Author: KZ
 */


#include "creature.h"

#include "../doctest.h"

#include <string>
#include <stdexcept>



Creature* create_creature(std::string type) {
	static int count = 1;
	std::string name = type + std::to_string(count);
	count++;
	if (type == "Warrior") {
		return new DamageDealer(name, 10, 3);
	} else if (type == "Fighter") {
		return new DamageDealer(name, 7, 5);
	} else if (type == "Priest") {
		return new Healer(name, 7, 2);
	} else {
		throw std::invalid_argument("Unknown type "+type);
	}
}

TEST_CASE("creating creatures by type") {
	Creature* warrior = create_creature("Warrior");
	CHECK(warrior->greet() == "I am Warrior1. Prepare to die!!!!");
	Creature* priest = create_creature("Priest");
	CHECK(priest->greet() == "Greetings, my name is Priest2, do you need any healing?");
}

class DummyCreatureFactory;

class CreatureFactory {
private:
	int creature_count;
public:
	virtual Creature* create_creature(std::string type);
	int get_creature_count() { return this->creature_count; }

//singleton pattern
public:
	static CreatureFactory& get_instance();
	CreatureFactory(const CreatureFactory&) = delete;
	CreatureFactory(CreatureFactory&&) = delete;
	CreatureFactory& operator=(const CreatureFactory&) = delete;
	CreatureFactory& operator=(CreatureFactory&&) = delete;
protected:
	CreatureFactory():creature_count{0} {}
};

Creature* CreatureFactory::create_creature(std::string type) {
	this->creature_count++;
	std::string name = type + std::to_string(this->creature_count);
	if (type == "Warrior") {
		return new DamageDealer(name, 10, 3);
	} else if (type == "Fighter") {
		return new DamageDealer(name, 7, 5);
	} else if (type == "Priest") {
		return new Healer(name, 7, 2);
	} else {
		throw std::invalid_argument("Unknown type "+type);
	}
}

TEST_CASE("creating creatures by type using Factory and Singleton") {
	CreatureFactory& factory = CreatureFactory::get_instance();
	CHECK(factory.get_creature_count() == 0);
	Creature* warrior = factory.create_creature("Warrior");
	CHECK(factory.get_creature_count() == 1);
	CHECK(warrior->greet() == "I am Warrior1. Prepare to die!!!!");

	CreatureFactory& factory2 = CreatureFactory::get_instance(); // same instance
	Creature* priest = factory2.create_creature("Priest");
	CHECK(factory2.get_creature_count() == 2);
	CHECK(priest->greet() == "Greetings, my name is Priest2, do you need any healing?");

	// CreatureFactory copy = CreatureFactory::get_instance(); // ERROR: copy constructor is deleted
}

class DummyCreature: public Creature {
private:
	std::string type;
public:
	DummyCreature(std::string type): Creature("dummy",0), type{type} {}
	std::string greet() override {
		return "dummy type="+this->type;
	}
	void heal(int health_amount, Creature* target) override {
	}
};

class DummyCreatureFactory: public CreatureFactory{
public:
	Creature* create_creature(std::string type) { return new DummyCreature(type);}
};

CreatureFactory& CreatureFactory::get_instance() {
	//static DummyCreatureFactory instance; // to replace the type of singleton instance
	static CreatureFactory instance;
	return instance;
}
