/*
 * lab_k29_2021_03_23_adapter.cpp
 *
 *  Created on: Mar 23, 2021
 *      Author: KZ
 */

#include "../list/list.h"

#include "../doctest.h"

#include <memory>
#include <string>
#include <vector>

template<typename T>
class VectorList: public List<T> {
private:
	std::vector<T> container;
public:
	void append(T value) override {
		container.push_back(value);
	}
	void clear() override {
		container.clear();
	}
	T operator[](std::size_t index) override {
		return container[index];
	}
	std::size_t size() override {
		return container.size();
	}
};

template<typename T>
class VectorListClassAdapter: public List<T>, private std::vector<T> {
public:
	void append(T value) override {
		this->push_back(value);
	}
	void clear() override {
		this->clear();
	}
	T operator[] (std::size_t index) {
		return (*this)[index];
	}
	std::size_t size() override {
		return this->size();
	}
//	using std::vector<T>::clear;
//	using std::vector<T>::size;
//	using std::vector<T>::operator[];

};

TEST_CASE("using list through interface") {
	std::shared_ptr<List<std::string>> mylist;
	SUBCASE("using custom implemented doubly linked list") {
		mylist = std::make_shared<DoublyLinkedList<std::string>>();
	}
	SUBCASE("using adapted std::vector") {
		mylist = std::make_shared<VectorList<std::string>>();
	}
//	SUBCASE("using class adapter for std::vector") {
//		mylist = std::make_shared<VectorListClassAdapter<std::string>>();
//	} // error - crashes, may need to call correct constructor for std::vector
	mylist->append("hello");
	mylist->append("world");
	CHECK(mylist->size() == 2);
	CHECK((*mylist)[0] == std::string("hello"));
	mylist->clear();
	CHECK(mylist->size() == 0);

}


