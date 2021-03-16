/*
 * creature.h
 *
 *  Created on: Mar 16, 2021
 *      Author: KZ
 */

#ifndef PATTERNS_CREATURE_H_
#define PATTERNS_CREATURE_H_

#include <string>
#include <vector>


class Modifier {
public:
	virtual bool is_hostile(bool prev) { return prev;}
	virtual std::string get_color() { return "grey"; }
	virtual int healing_amount(int prev) { return prev;}
};

class HostileModifier: public Modifier {
public:
	bool is_hostile(bool prev) override { return true;}
	std::string get_color() override { return "red";}
};

class ColorModifier: public Modifier {
private:
	std::string color;
public:
	ColorModifier(std::string color) : color{color} {}
	std::string get_color() override { return color; }
};

class WeaponModifier: public Modifier {
public:
	int healing_amount(int prev) override {
		if (prev < 0) {
			return prev*2;
		} else {
			return prev;
		}
	}
};

class Creature {
protected:
	std::string name;
	int health;
	bool _is_hostile;
	std::vector<Modifier*> modifiers;

	int modified_healing_amount(int starting_amount) {
		int result = starting_amount;
		for(Modifier* mod: modifiers) {
			result = mod->healing_amount(result);
		}
		return result;
	}

	void change_health_for_target(int health_amount, Creature* target) {
		int real_amount = modified_healing_amount(health_amount);
		target->change_health(real_amount);
	}

public:
	Creature(std::string name, int health, bool is_hostile = true) :
		name{name}, health{health}, _is_hostile{is_hostile}, modifiers{} {}
	void change_health(int amount) { this->health += amount;}
	bool is_hostile() {
		bool result = _is_hostile;
		for(Modifier* mod: modifiers) {
			result = mod->is_hostile(result);
		}
		return result;
	}
	std::string get_color() {
		std::string result = "";
		for(Modifier* mod: modifiers) {
			result = mod->get_color();
		}
		return result;
	}
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
		change_health_for_target(-damage_to_deal, target);
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
		change_health_for_target(health_amount, target);
	}
};



#endif /* PATTERNS_CREATURE_H_ */
