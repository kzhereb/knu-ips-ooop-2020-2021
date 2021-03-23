/*
 * lab_k29_lesson_2021_03_23_bridge.cpp
 *
 *  Created on: Mar 23, 2021
 *      Author: KZ
 */

#include "../list/list.h"

#include "../doctest.h"

#include <memory>
#include <string>

template<typename T>
class AbstractList: public List<T> {
protected:
	std::shared_ptr<List<T>> implementation;
public:
	void append(T value) override  {
		implementation->append(value);
	}
	void clear() override {
		implementation->clear();
	}
	T operator[](std::size_t index) override {
		return (*implementation)[index];
	}
	std::size_t size() override {
		return implementation->size();
	}

	void set_implementation(std::shared_ptr<List<T>> implementation) {
		this->implementation = implementation;
	}
};

template<typename T>
class Stack: public AbstractList<T> {
public:
	void push(T value) {
		this->implementation->append(value);
	}
	T peek() {
		return (*this->implementation)[this->implementation->size()-1];
	}
};

TEST_CASE("using different abstractions with different implementations: Stack") {
	std::shared_ptr<Stack<std::string>> mystack = std::make_shared<Stack<std::string>>();
	SUBCASE("using custom implemented doubly linked list") {
		mystack->set_implementation(std::make_shared<DoublyLinkedList<std::string>>());
	}
//	SUBCASE("using adapted std::vector") {
//		mylist = std::make_shared<VectorList<std::string>>();
//	}

	mystack->push("hello");
	CHECK(mystack->size() == 1);
	CHECK(mystack->peek() == std::string("hello"));
	mystack->push("world");
	CHECK(mystack->size() == 2);
	CHECK(mystack->peek() == std::string("world"));
}


