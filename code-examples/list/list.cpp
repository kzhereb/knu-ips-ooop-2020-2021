/*
 * list.cpp
 *
 *  Created on: Sep 22, 2020
 *      Author: KZ
 */

#include "../doctest.h"

#include <cstddef>
#include <ostream>
#include <iostream>
#include <sstream>

struct ListNode {
	int value;
	ListNode* prev;
	ListNode* next;

	ListNode(int value, ListNode* prev=nullptr, ListNode* next=nullptr): value{value}, prev{prev}, next{next} {}
};

struct DoublyLinkedList {
	ListNode* begin;
	ListNode* end;
	std::size_t _size;
	DoublyLinkedList(): begin{nullptr}, end{nullptr}, _size{0} {}

	void append(int value) {
		ListNode* new_node = new ListNode{value};
		if (begin == nullptr) {
			begin = end = new_node;
		} else {
			new_node->prev = end;
			end->next = new_node;
			end = new_node;
		}
		_size++;
	}

	std::size_t size() {
		return _size;
	}

	std::size_t size_naive() {
		std::size_t result = 0;
		ListNode* current = begin;
		while(current) {
			result++;
			current = current->next;
		}
		return result;
	}
};


std::ostream& operator<<(std::ostream& out, const DoublyLinkedList& list) {
	ListNode* current = list.begin;
	out<<"[ ";
	while(current) {
		out << current->value << " ";
		current = current->next;
	}
	out<<"]";
	return out;
}

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

		std::stringstream s_out;
		s_out<<list;
		CHECK(s_out.str()=="[ 123 456 ]");

	}
}



