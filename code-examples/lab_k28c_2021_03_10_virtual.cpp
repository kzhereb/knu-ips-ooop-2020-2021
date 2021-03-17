/*
 * lab_k28c_2021_03_10_virtual.cpp
 *
 *  Created on: Mar 10, 2021
 *      Author: KZ
 */

#include "doctest.h"

#include <string>
#include <stdexcept>

class Animal {
public:
	static int destructor_count;
	Animal() {}
	virtual std::string make_sound() = 0;
	virtual ~Animal() {destructor_count++;}
};

int Animal::destructor_count = 0;

class Dog : public Animal {
public:
	std::string make_sound() override {
		return "Bow-wow-wow!";
	}
};

class Cat: public Animal {
public:
	static int cat_count;
	Cat(): Animal() {}
	std::string make_sound() override {
		return "Meow-meow";
	}
	~Cat() { cat_count++;}
};
int Cat::cat_count = 0;

TEST_CASE("Virtual methods") {
	Cat mycat;
	CHECK(mycat.make_sound() == std::string("Meow-meow")); // non-polymorphic
	Animal* mypet = new Cat;
	CHECK(mypet->make_sound() == std::string("Meow-meow")); // polymorphic
	CHECK(Animal::destructor_count == 0);
	CHECK(Cat::cat_count == 0);
	delete mypet;
	CHECK(Animal::destructor_count == 1);
	CHECK(Cat::cat_count == 1); // will only work if Animal destructor is virtual
}

Animal* create_animal(std::string type) {
	if (type == "Cat" || type == "Feline") {
		return new Cat;
	} else if (type == "Dog" || type == "Canine") {
		return new Dog;
	} else {
		throw std::invalid_argument("Unknown type: " + type);
	}
}

TEST_CASE("using factory function to create animals") {
	Animal* mypet = create_animal("Dog");
	CHECK(mypet->make_sound() == std::string("Bow-wow-wow!"));
	delete mypet;
}
