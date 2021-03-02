/*
 * lab_k29_2021_03_02_iterator.cpp
 *
 *  Created on: Mar 2, 2021
 *      Author: KZ
 */

#include "../list/list.h"

#include "../doctest.h"

#include <algorithm>
#include <iterator>
#include <vector>
#include <sstream>


TEST_CASE("std::copy using iterators") {
	std::vector<int> source {1, 3, 5, 7, 9};
	std::vector<int> destination;
	SUBCASE("using std::back_inserter") {
		std::copy(source.begin(), source.end(), std::back_inserter(destination));
	}
	SUBCASE("set size") {
		destination.resize(source.size());
		std::copy(source.begin(), source.end(), destination.begin());
	}
	CHECK(destination.size() == source.size());
	CHECK(destination[0] == source[0]);
}

TEST_CASE("custom iterator for DoublyLinkedList") {
	DoublyLinkedList<int> mylist;
	mylist.append(1);
	mylist.append(3);
	mylist.append(5);
	std::stringstream out;
	for(int value: mylist) {
		out<<value<<std::endl;
	}
	CHECK(std::string(out.str()) == "1\n3\n5\n");

	std::vector<int> destination;
	std::copy(mylist.begin(), mylist.end(), std::back_inserter(destination));
	CHECK(destination.size() == 3);
	for (std::size_t i = 0; i< destination.size(); i++) {
		CHECK(destination[i] == mylist[i]);
	}
}
