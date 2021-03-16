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




#endif /* PATTERNS_CREATURE_FACTORY_H_ */
