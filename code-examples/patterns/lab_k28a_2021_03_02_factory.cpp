/*
 * lab_k28a_2021_03_02_factory.cpp
 *
 *  Created on: Mar 2, 2021
 *      Author: KZ
 */


#include "creature.h"
#include "creature_factory.h"

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


