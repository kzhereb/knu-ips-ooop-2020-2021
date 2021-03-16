/*
 * creature_factory.h
 *
 *  Created on: Mar 16, 2021
 *      Author: KZ
 */

#ifndef PATTERNS_CREATURE_FACTORY_H_
#define PATTERNS_CREATURE_FACTORY_H_

#include "creature.h"
#include <stdexcept>

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


#endif /* PATTERNS_CREATURE_FACTORY_H_ */
