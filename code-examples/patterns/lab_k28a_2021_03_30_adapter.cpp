/*
 * lab_k28a_2021_03_30_adapter.cpp
 *
 *  Created on: Mar 30, 2021
 *      Author: KZ
 */

#include "creature.h"

#include "propmap_creature.h"

#include "../doctest.h"


TEST_CASE("using propmap creatures") {
	PropMapCreature warrior;

	warrior.set_value("name", std::string("Warrior1"));
	warrior.set_value("health", 10);
	warrior.set_value("damage_per_hit", 3);

	CHECK(warrior.get_value<std::string>("name") == "Warrior1");
	CHECK(warrior.get_value<int>("health") == 10);
	CHECK(warrior.get_value("damage_per_hit") == 3);
}

class CreatureAdaptsPropMap: public Creature {
private:
	PropMapCreature impl;
public:
	CreatureAdaptsPropMap(std::string name, int health, bool is_hostile = true): Creature(name, health, is_hostile) {}

	std::string greet() override {
		return impl.get_value<std::string>("greet");
	}

	void heal(int health_amount, Creature* target) override {
		int damage_to_deal = impl.get_value("damage");
		change_health_for_target(-damage_to_deal, target);
	}

	Creature* clone(std::string name) override {
		CreatureAdaptsPropMap* result = new CreatureAdaptsPropMap(name, this->health, this->is_hostile());
		result->set_additional_prop("damage", impl.get_value<int>("damage"));
		result->set_additional_prop("greet", impl.get_value<std::string>("greet"));
		return result;
	}

	template<typename T>
	void set_additional_prop(std::string name, T value) {
		impl.set_value(name, value);
	}
};


TEST_CASE("using adapted creatures") {
	CreatureAdaptsPropMap* warrior_prototype = new CreatureAdaptsPropMap("Warrior_proto", 10, true);
	warrior_prototype->set_additional_prop("damage",3);
	warrior_prototype->set_additional_prop("greet",std::string("Prepare to die!!!!"));

	Creature* warrior = warrior_prototype->clone("Warrior1");
	CHECK(warrior->greet() == std::string("Prepare to die!!!!"));
}





