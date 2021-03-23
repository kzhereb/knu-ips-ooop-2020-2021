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

TEST_CASE("using list through interface") {
	std::shared_ptr<List<std::string>> mylist = std::make_shared<DoublyLinkedList<std::string>>();
	mylist->append("hello");
	mylist->append("world");
	CHECK(mylist->size() == 2);
	CHECK((*mylist)[0] == std::string("hello"));
	mylist->clear();
	CHECK(mylist->size() == 0);

}


