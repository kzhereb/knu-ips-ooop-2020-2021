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
}


