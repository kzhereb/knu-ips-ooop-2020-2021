/*
 * lab_k28a_2021_03_23_prototype.cpp
 *
 *  Created on: Mar 23, 2021
 *      Author: KZ
 */

#include "creature.h"

#include "../doctest.h"


TEST_CASE("creating creatures using prototypes") {
	Creature* warrior_prototype = new DamageDealer("Warrior_prototype", 10, 3);
	Creature* fighter_prototype =  new DamageDealer("Fighter_prototype", 7, 5);
	Creature* priest_prototype =  new Healer("Priest_prototype", 7, 2);

	Creature* warrior1 = warrior_prototype->clone("Warrior1");
	CHECK(warrior1->greet() == "I am Warrior1. Prepare to die!!!!");
	Creature* priest2 = priest_prototype->clone("Priest2");
	CHECK(priest2->greet() == "Greetings, my name is Priest2, do you need any healing?");
}
