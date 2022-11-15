/*
 * list.cpp
 *
 *  Created on: Sep 22, 2020
 *      Author: KZ
 */

#include "list.h"

#include "../doctest.h"








TEST_CASE("[list] - creating list nodes") {
	ListNode<int> node{123};
	CHECK(node.value == 123);

	ListNode<int>* node2;
	SUBCASE("constructor with 3 arguments") {
		node2 = new ListNode<int>{456, &node, nullptr};
	}
	SUBCASE("constructor with 2 arguments") {
		node2 = new ListNode<int>{456, &node};
	}

	CHECK(node2->value == 456);
	CHECK(node2->prev == &node);
	CHECK(node2->prev->value == 123);
	CHECK(node2->next == nullptr);

	delete node2;
}


namespace test_doubly_linked_list {
	void test_create_append_clear() {
		DoublyLinkedList<int> list;
			CHECK(list._begin == nullptr);
			CHECK(list._end == nullptr);
			CHECK(list.size() == 0);

			SUBCASE("append element") {
				list.append(123);
				CHECK(list._end == list._begin);
				CHECK(list._begin->value == 123);
				CHECK(list._begin->prev == nullptr);
				CHECK(list._begin->next == nullptr);
				CHECK(list.size() == 1);

				list.append(456);
				CHECK(list._end != list._begin);
				CHECK(list._begin->value == 123);
				CHECK(list._begin->prev == nullptr);
				CHECK(list._begin->next == list._end);

				CHECK(list._end->value == 456);
				CHECK(list._end->prev == list._begin);
				CHECK(list._end->next == nullptr);

				CHECK(list.size() == 2);

				{
					std::stringstream s_out;
					s_out<<list;
					CHECK(s_out.str()=="[ 123 456 ]");
				} // to keep s_out in local scope

				CHECK(list[0]==123);
				CHECK(list[1]==456);
				try {
					int result = list[2];
					CHECK(result); // not called
				} catch(const std::out_of_range& ex) {
					CHECK(std::string(ex.what()) == "index=2 larger than list size=2");
				}

				CHECK_THROWS_WITH_AS(list[2],"index=2 larger than list size=2",std::out_of_range);

				SUBCASE("clear list") {
					list.clear();
					CHECK(list.size()==0);
					list.append(789);
					CHECK(list.size()==1);
					CHECK(list[0]==789);
				}

			}
	}
}

TEST_CASE("[list] - creating doubly-linked list") {
	test_doubly_linked_list::test_create_append_clear();
}



