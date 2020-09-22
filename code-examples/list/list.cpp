/*
 * list.cpp
 *
 *  Created on: Sep 22, 2020
 *      Author: KZ
 */

#include "../doctest.h"

#include <cstddef>

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

	void append(int value) {
		ListNode* new_node = new ListNode{value};
		if (begin == nullptr) {
			begin = end = new_node;
		} else {
			new_node->prev = end;
			end->next = new_node;
			end = new_node;
		}
	}

	std::size_t size() {
		std::size_t result = 0;
		ListNode* current = begin;
		while(current) {
			result++;
			current = current->next;
		}
		return result;
	}
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
	CHECK(list.size() == 0);

	SUBCASE("append element") {
		list.append(123);
		CHECK(list.end == list.begin);
		CHECK(list.begin->value == 123);
		CHECK(list.begin->prev == nullptr);
		CHECK(list.begin->next == nullptr);
		CHECK(list.size() == 1);

		list.append(456);
		CHECK(list.end != list.begin);
		CHECK(list.begin->value == 123);
		CHECK(list.begin->prev == nullptr);
		CHECK(list.begin->next == list.end);

		CHECK(list.end->value == 456);
		CHECK(list.end->prev == list.begin);
		CHECK(list.end->next == nullptr);

		CHECK(list.size() == 2);

	}
}



