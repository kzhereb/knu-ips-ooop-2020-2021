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
};

TEST_CASE("[list] - creating list nodes") {
	ListNode node{123};
	CHECK(node.value == 123);
}



