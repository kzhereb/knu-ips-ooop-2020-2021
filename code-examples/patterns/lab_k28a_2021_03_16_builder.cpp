/*
 * lab_k28a_2021_03_16_builder.cpp
 *
 *  Created on: Mar 16, 2021
 *      Author: KZ
 */

#include "creature.h"
#include "creature_factory.h"

#include "../doctest.h"


class CreatureBuilder {
private:
	Creature* creature;
public:
	CreatureBuilder(Creature* creature) : creature{creature} {}

	void recolor(std::string color) {
		creature->add_modifier(new ColorModifier(color));
	}

	void make_hostile() {
		creature->add_modifier(new HostileModifier);
	}

	void arm_with_weapon() {
		creature->add_modifier(new WeaponModifier);
	}

	Creature* get_creature() {
		return creature;
	}
};

TEST_CASE("Modifying creatures with builder") {
	Creature* unmodified = CreatureFactory::get_instance().create_creature("Priest");
	CHECK(unmodified->is_hostile() == false);
	CHECK(unmodified->get_color() == std::string(""));

	SUBCASE ("hostile priest") {
		CreatureBuilder builder{unmodified};
		builder.make_hostile();
		Creature* priest = builder.get_creature();

		CHECK(priest->is_hostile() == true);
		CHECK(priest->get_color() == std::string("red"));
	}

	SUBCASE ("hostile green priest") {
		CreatureBuilder builder{unmodified};
		builder.make_hostile();
		builder.recolor("green");
		Creature* priest = builder.get_creature();

		CHECK(priest->is_hostile() == true);
		CHECK(priest->get_color() == std::string("green"));
	}

}


