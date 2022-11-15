/*
 * lab_k28c_2021_03_10_virtual.cpp
 *
 *  Created on: Mar 10, 2021
 *      Author: KZ
 */

#include "doctest.h"

#include <string>
#include <stdexcept>
#include <unordered_map>

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

class AnimalFactory {
private:
	std::unordered_map<std::string,int> type_counts;
protected:
	AnimalFactory(): type_counts{} {}
public:
	static AnimalFactory& get() {
		static AnimalFactory instance;
		return instance;
	}
	AnimalFactory(const AnimalFactory&) = delete;
	AnimalFactory(AnimalFactory&&) = delete;
	AnimalFactory& operator=(const AnimalFactory&) = delete;
	AnimalFactory& operator=(AnimalFactory&&) = delete;

	Animal* create_animal(std::string type) {
		if (type_counts.find(type) != type_counts.end()) {
			type_counts[type]++;
		} else {
			type_counts[type] = 1;
		}
		if (type == "Cat" || type == "Feline") {
			return new Cat;
		} else if (type == "Dog" || type == "Canine") {
			return new Dog;
		} else {
			throw std::invalid_argument("Unknown type: " + type);
		}
	}

	int get_type_count(std::string type) {
		return type_counts[type];
	}

};

TEST_CASE("using factory class (singleton) to create animals") {
	// MAGIC factory;
	// AnimalFactory factory; // ERROR - constructor is protected
	// AnimalFactory factory = AnimalFactory::get(); // ERROR - copy constructor deleted
	// AnimalFactory* factory_ptr = &(AnimalFactory::get()); // works, but dangerous - what if someone calls delete?
	AnimalFactory& factory = AnimalFactory::get();

	CHECK(factory.get_type_count("Dog") == 0);
	Animal* mypet = factory.create_animal("Dog");
	CHECK(mypet->make_sound() == std::string("Bow-wow-wow!"));
	CHECK(factory.get_type_count("Dog") == 1);
	Animal* another = factory.create_animal("Dog");
	CHECK(another->make_sound() == std::string("Bow-wow-wow!"));
	CHECK(mypet != another);
	CHECK(factory.get_type_count("Dog") == 2);
	Animal* exotic = factory.create_animal("Canine");
	CHECK(exotic->make_sound() == std::string("Bow-wow-wow!"));
	CHECK(factory.get_type_count("Dog") == 2);
	CHECK(factory.get_type_count("Canine") == 1);
	delete mypet;
}
