/*
 * lab_k29_13_10_20_smart_pointers.cpp
 *
 *  Created on: Oct 13, 2020
 *      Author: KZ
 */

#include "doctest.h"

#include <ostream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

class Test {
public:
	static std::ostream* out;
	int value;
	Test() {*out<<"default constructor"<<std::endl; value = 5;}
	Test(const Test& that) { *out<<"copy constructor "<<that.value<<std::endl; value = that.value + 100; }
	Test(Test&& that) { *out<<"move constructor "<<that.value<<std::endl; value = that.value + 10000; that.value = -that.value; }
	~Test() {*out<<"destructor "<<value<<std::endl;}
};
std::ostream* Test::out = nullptr;

class Container {
private:
	std::vector<std::shared_ptr<Test>> stored;
public:
	void store(std::shared_ptr<Test> test) {
		stored.push_back(test);
	}
	int sum() const {
		int result = 0;
		for(auto item:stored) {
			result += item->value;
		}
		return result;
	}
	std::shared_ptr<Test> get(std::size_t index) {
		return stored[index];
	}
	std::size_t get_use_count(std::size_t index) {
		return stored[index].use_count();
	}
};


class ContainerUnique {
private:
	std::vector<std::unique_ptr<Test>> stored;
public:
	void store(Test* test) {
		stored.push_back(std::unique_ptr<Test>(test) );
	}
	void store(std::unique_ptr<Test>&& test) {
		stored.push_back(std::move(test));
	}
	void dont_store(std::unique_ptr<Test>&& test) {
		//stored.push_back(std::move(test));
	}
	int sum() const {
		int result = 0;
		for(const auto& item:stored) {
			result += item->value;
		}
		return result;
	}
};



TEST_CASE("smart pointers and object lifetime - stack") {
	std::stringstream out;
	Test::out = &out;
	{
		Test test;
		CHECK(out.str() == "default constructor\n");
	}
	CHECK(out.str() == "default constructor\ndestructor 5\n");
}

TEST_CASE("smart pointers and object lifetime - heap") {
	std::stringstream out;
	Test::out = &out;

	Test* ptest = new Test;
	CHECK(out.str() == "default constructor\n");
	delete ptest;
	CHECK(out.str() == "default constructor\ndestructor 5\n");
}

TEST_CASE("smart pointers and object lifetime - smart pointer") {
	std::stringstream out;
	Test::out = &out;
	{
		std::shared_ptr<Test> ptest = std::make_shared<Test>();
		CHECK(out.str() == "default constructor\n");
		CHECK(ptest->value == 5);
	}
	CHECK(out.str() == "default constructor\ndestructor 5\n");
}

TEST_CASE("smart pointers and object lifetime - smart pointer in container") {
	std::stringstream out;
	Test::out = &out;
	{
		Container container;
		{
			std::shared_ptr<Test> ptest = std::make_shared<Test>();
			CHECK(out.str() == "default constructor\n");
			CHECK(ptest->value == 5);
			CHECK(ptest.use_count() == 1 );
			container.store(ptest);
			CHECK(container.sum() == 5);
			CHECK(ptest->value == 5);
			CHECK(ptest.use_count() == 2 );
		}
		CHECK(container.sum() == 5);
		CHECK(out.str() == "default constructor\n");
		CHECK(container.get(0).use_count() == 2); // temporary std::shared_ptr increases use_count
		CHECK(container.get_use_count(0) == 1); //temporary object from previous line already deleted

		{
			std::shared_ptr<Test> pstored = container.get(0);
			CHECK(pstored.use_count() == 2);
			CHECK(container.get_use_count(0) == 2);
		}
		CHECK(container.get_use_count(0) == 1);

	}
	CHECK(out.str() == "default constructor\ndestructor 5\n");
}

TEST_CASE("smart pointers and object lifetime - smart pointer (unique_ptr)") {
	std::stringstream out;
	Test::out = &out;
	{
		std::unique_ptr<Test> ptest = std::make_unique<Test>();
		CHECK(out.str() == "default constructor\n");
		CHECK(ptest->value == 5);
	}
	CHECK(out.str() == "default constructor\ndestructor 5\n");
}

TEST_CASE("smart pointers and object lifetime - smart pointer in container") {
	std::stringstream out;
	Test::out = &out;
	{
		ContainerUnique container;
		{
			std::unique_ptr<Test> ptest = std::make_unique<Test>();
			CHECK(out.str() == "default constructor\n");
			CHECK(ptest->value == 5);
			container.store(ptest.release());
			CHECK(ptest.get() == nullptr);
			CHECK(container.sum() == 5);
		}
		CHECK(container.sum() == 5);
		CHECK(out.str() == "default constructor\n");
	}
	CHECK(out.str() == "default constructor\ndestructor 5\n");
}

TEST_CASE("smart pointers and object lifetime - moving unique_ptr") {
	std::stringstream out;
	Test::out = &out;
	{
		ContainerUnique container;
		{
			std::unique_ptr<Test> ptest = std::make_unique<Test>();
			CHECK(out.str() == "default constructor\n");
			CHECK(ptest->value == 5);

			container.dont_store(std::move(ptest)); // move is not performed here!
			CHECK(ptest.get() != nullptr);
			CHECK(ptest->value == 5);

			container.store(std::move(ptest));
			CHECK(ptest.get() == nullptr);
			CHECK(container.sum() == 5);
		}
		CHECK(container.sum() == 5);
		CHECK(out.str() == "default constructor\n");
	}
	CHECK(out.str() == "default constructor\ndestructor 5\n");
}


TEST_CASE("smart pointers and object lifetime - weak pointer") {
	std::stringstream out;
	Test::out = &out;
	{
		std::weak_ptr<Test> weak_test;
		{
			std::shared_ptr<Test> ptest = std::make_shared<Test>();
			CHECK(out.str() == "default constructor\n");
			CHECK(ptest.use_count() == 1);
			CHECK(ptest->value == 5);
			weak_test = ptest;
			bool complex_expression = weak_test.lock()->value ==  5 && weak_test.use_count() == 2;
			CHECK(complex_expression);
			CHECK(ptest.use_count() == 1);
			CHECK(weak_test.use_count() == 1);
		}
		CHECK(weak_test.use_count() == 0);
		CHECK(out.str() == "default constructor\ndestructor 5\n");
	}
	CHECK(out.str() == "default constructor\ndestructor 5\n");
}

TEST_CASE("move semantics for Test class") {
	std::stringstream out;
	Test::out = &out;
	{
		Test test;
		CHECK(out.str() == "default constructor\n");
		Test test2{std::move(test)};
		CHECK(out.str() == "default constructor\nmove constructor 5\n");
		CHECK(test2.value == 10005);
		CHECK(test.value == -5);
	}
	CHECK(out.str() == "default constructor\nmove constructor 5\ndestructor 10005\ndestructor -5\n");
}
