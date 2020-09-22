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

	ListNode(int value, ListNode* prev=nullptr, ListNode* next=nullptr): value{value}, prev{prev}, next{next} {}
};

struct DoublyLinkedList {
	ListNode* begin;
	ListNode* end;
	DoublyLinkedList(): begin{nullptr}, end{nullptr} {}
};

TEST_CASE("[list] - creating list nodes") {
	ListNode node{123};
	CHECK(node.value == 123);

	ListNode* node2;
	SUBCASE("constructor with 3 arguments") {
		node2 = new ListNode{456, &node, nullptr};
	}
	SUBCASE("constructor with 2 arguments") {
		node2 = new ListNode{456, &node};
	}

	CHECK(node2->value == 456);
	CHECK(node2->prev == &node);
	CHECK(node2->prev->value == 123);
	CHECK(node2->next == nullptr);
}

TEST_CASE("[list] - creating doubly-linked list") {
	DoublyLinkedList list;
	CHECK(list.begin == nullptr);
	CHECK(list.end == nullptr);
}



