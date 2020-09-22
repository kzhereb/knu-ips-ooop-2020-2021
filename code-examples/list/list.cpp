/*
 * list.cpp
 *
 *  Created on: Sep 22, 2020
 *      Author: KZ
 */

#include "../doctest.h"

struct ListNode {
	int value;
	ListNode* prev;
	ListNode* next;
	ListNode(int value): value{value} {}
	ListNode(int value, ListNode* prev, ListNode* next): value{value}, prev{prev}, next{next} {}
};

TEST_CASE("[list] - creating list nodes") {
	ListNode node{123};
	CHECK(node.value == 123);

	ListNode node2{456, &node, nullptr};
	CHECK(node2.value == 456);
	CHECK(node2.prev == &node);
	CHECK(node2.prev->value == 123);
	CHECK(node2.next == nullptr);

}



