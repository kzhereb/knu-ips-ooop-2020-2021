/*
 * propmap_creature.h
 *
 *  Created on: Mar 30, 2021
 *      Author: KZ
 */

#ifndef PATTERNS_PROPMAP_CREATURE_H_
#define PATTERNS_PROPMAP_CREATURE_H_

#include <unordered_map>
#include <string>
#include <any>


class PropMapCreature {
private:
	std::unordered_map<std::string, std::any> properties;
public:
	template<typename T = int>
	T get_value(std::string property) {
		return std::any_cast<T>(properties[property]);
	}

	template<typename T>
	void set_value(std::string property, T value) {
		properties[property] = std::any(value);
	}
};






#endif /* PATTERNS_PROPMAP_CREATURE_H_ */
