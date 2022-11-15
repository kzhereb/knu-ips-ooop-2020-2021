/*
 * lab_k29_2021_04_23_type_erasure.cpp
 *
 *  Created on: Apr 23, 2021
 *      Author: KZ
 */

#include "doctest.h"
#include <string>
#include <sstream>
#include <memory>

class AbstractContainer {
public:
	virtual std::string get() = 0;
	virtual void set(std::string value) = 0;
};

template<typename T>
class Container {
private:
	T value;
public:
	Container(const T& value): value{value} {}
	T get() {return value;}
	void set(const T& value) {this->value = value;}
};

template<typename T>
class ContainerWrapper: public AbstractContainer {
private:
	Container<T> implementation;
	static std::string to_string(const T& value) {
		std::stringstream out;
		out << value;
		return out.str();
	}
	static T parse(std::string text) {
		std::stringstream in(text);
		T result;
		in >> result;
		return result;
	}

public:
	ContainerWrapper(std::string value): implementation{parse(value)} {	}
	std::string get() override {
		return to_string(implementation.get());
	}
	void set(std::string value) override {
		implementation.set(parse(value));
	}
};


TEST_CASE("working with type erased containers") {
	std::shared_ptr<AbstractContainer> container = std::make_shared<ContainerWrapper<int>>("123");
	CHECK(container->get() == std::string("123"));
	container->set("456");
	CHECK(container->get() == std::string("456"));

	container = std::make_shared<ContainerWrapper<std::string>>("hello");
	CHECK(container->get() == std::string("hello"));
	container->set("world");
	CHECK(container->get() == std::string("world"));
}

