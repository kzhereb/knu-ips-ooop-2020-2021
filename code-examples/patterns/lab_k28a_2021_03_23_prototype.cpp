/*
 * lab_k28a_2021_03_23_prototype.cpp
 *
 *  Created on: Mar 23, 2021
 *      Author: KZ
 */

#include "creature.h"

#include "../doctest.h"

#include <map>


TEST_CASE("creating creatures using prototypes") {
	Creature* warrior_prototype = new DamageDealer("Warrior_prototype", 10, 3);
	Creature* fighter_prototype =  new DamageDealer("Fighter_prototype", 7, 5);
	Creature* priest_prototype =  new Healer("Priest_prototype", 7, 2);

	Creature* warrior1 = warrior_prototype->clone("Warrior1");
	CHECK(warrior1->greet() == "I am Warrior1. Prepare to die!!!!");
	Creature* priest2 = priest_prototype->clone("Priest2");
	CHECK(priest2->greet() == "Greetings, my name is Priest2, do you need any healing?");
}


class CreatureRegistry {
private:
	std::map<std::string, Creature*> prototypes;
	int creature_count;
public:
	CreatureRegistry() {
		creature_count = 0;
	}
	void register_type(std::string type, Creature* prototype) {
		prototypes[type] = prototype;
	}
	Creature* create_creature(std::string type) {
		this->creature_count++;
		return prototypes[type]->clone(type+std::to_string(creature_count));
	}
};


TEST_CASE("creating creatures using prototypes") {
	CreatureRegistry registry;
	registry.register_type("Warrior", new DamageDealer("Warrior_prototype", 10, 3));
	registry.register_type("Fighter", new DamageDealer("Fighter_prototype", 7, 5));
	registry.register_type("Priest", new Healer("Priest_prototype", 7, 2));


	Creature* warrior1 = registry.create_creature("Warrior");
	CHECK(warrior1->greet() == "I am Warrior1. Prepare to die!!!!");
	Creature* priest2 = registry.create_creature("Priest");
	CHECK(priest2->greet() == "Greetings, my name is Priest2, do you need any healing?");
}
