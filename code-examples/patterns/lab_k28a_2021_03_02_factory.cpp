/*
 * lab_k28a_2021_03_02_factory.cpp
 *
 *  Created on: Mar 2, 2021
 *      Author: KZ
 */

#include "../doctest.h"

#include <string>
#include <stdexcept>

class Creature {
protected:
	std::string name;
	int health;
	bool is_hostile;
public:
	Creature(std::string name, int health, bool is_hostile = true) : name{name}, health{health}, is_hostile{is_hostile} {}
	void change_health(int amount) { this->health += amount;}
	virtual ~Creature() {}
	virtual std::string greet() = 0;
	virtual void heal(int health_amount, Creature* target) = 0;


};

class PlayerCharacter: public Creature {

};

class DamageDealer: public Creature {
private:
	int damage_per_hit;
public:
	DamageDealer(std::string name, int health, int damage_per_hit): Creature{name, health, true}, damage_per_hit{damage_per_hit} {}
	std::string greet() override {
		return "I am " + name + ". Prepare to die!!!!";
	}
	void heal(int health_amount, Creature* target) override {
		int damage_to_deal = health_amount;
		if (health_amount > damage_per_hit) {
			damage_to_deal = damage_per_hit;
		}
		target->change_health(-damage_to_deal);
	}
};

class Healer: public Creature {
private:
	int heal_per_second;
public:
	Healer(std::string name, int health, int heal_per_second): Creature{name, health, false}, heal_per_second{heal_per_second} {}
	std::string greet() override {
		return "Greetings, my name is " + this->name + ", do you need any healing?";
	}
	void heal(int health_amount, Creature* target) override {
		target->change_health(health_amount);
	}
};

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


