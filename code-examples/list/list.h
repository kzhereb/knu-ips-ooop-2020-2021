/*
 * list.h
 *
 *  Created on: Mar 2, 2021
 *      Author: KZ
 */

#ifndef LIST_LIST_H_
#define LIST_LIST_H_

#include <cstddef>
#include <ostream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iterator>
#include <vector>

/**
 * \brief A single node in doubly linked list
 *
 * A single node holding a value and pointers to the next and previous nodes.
 * Pointers can be empty (for first and last nodes).
 * \see DoublyLinkedList
 */
template<typename T>
struct ListNode {
	T value;			/**< Value stored in this node */
	ListNode<T>* prev;		/**< Pointer to the previous node in the list, can be empty (nullptr) for the first node */
	ListNode<T>* next;		/**< Pointer to the next node in the list, can be empty (nullptr) for the last node */

	/**
	 * \brief ListNode constructor
	 *
	 * Value must be specified, previous and next pointers are optional.
	 * Can specify only previous without next (useful for append)
	 * \callergraph
	 */
	ListNode(T value, ListNode<T>* prev=nullptr, ListNode<T>* next=nullptr): value{value}, prev{prev}, next{next} {}
};


namespace test_doubly_linked_list {
	void test_create_append_clear();
}

template<typename T>
struct List {
	virtual void append(T value) = 0;
	virtual void clear() = 0;
	virtual T operator[](std::size_t index) = 0;
	virtual std::size_t size() = 0;

};

/**
 * \brief Doubly linked list
 *
 * Stores a sequence of values using nodes (ListNode objects) for each value linked with next and previous pointers,
 * See [Doubly Linked List](https://en.wikipedia.org/wiki/Doubly_linked_list "Wikipedia article on Doubly Linked List")
 */
template<typename T>
class DoublyLinkedList : public List<T> {
private:
	ListNode<T>* _begin;
	ListNode<T>* _end;
	std::size_t _size;
public:

	DoublyLinkedList(): _begin{nullptr}, _end{nullptr}, _size{0} {}

	~DoublyLinkedList() {
		this->clear();
	}

	/**
	 * \brief Append value to the end of this list
	 *
	 * Creates a new node containing this value, inserts it at the end of list.
	 *
	 * \param value a value to be appended
	 * \post List size is increased by 1
	 * \callgraph
	 */
	void append(T value) override {
		auto new_node = new ListNode<T>{value};
		if (_begin == nullptr) {
			_begin = _end = new_node;
		} else {
			new_node->prev = _end;
			_end->next = new_node;
			_end = new_node;
		}
		_size++;
	}

	void clear() override {
		ListNode<T>* current = _begin;
		while(current) {
			ListNode<T>* to_delete = current;
			current = current->next;
			delete to_delete;
		}
		_begin = _end = nullptr;
		_size = 0;
	}

	/**
	 * \brief Access items by index
	 *
	 * Complexity is O(n)
	 * \param index zero-based index of item to get
	 * \throw std::out_of_range if index is too large (greater or equals to list size)
	 * \return value of item
	 */
	T operator[](std::size_t index) override {
		ListNode<T>* current = _begin;
		std::size_t cur_index = 0;
		while(current) {
			if (cur_index == index) {
				return current->value;
			}
			current = current->next;
			cur_index++;
		}
		throw std::out_of_range{"index="+std::to_string(index)+" larger than list size="+std::to_string(_size)};
	}

	std::size_t size() override {
		return _size;
	}

	std::size_t size_naive() {
		std::size_t result = 0;
		ListNode<T>* current = _begin;
		while(current) {
			result++;
			current = current->next;
		}
		return result;
	}

	friend std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<T>& list) {
		ListNode<T>* current = list._begin; //can also use auto current; or auto* current;
		out<<"[ ";
		while(current) {
			out << current->value << " ";
			current = current->next;
		}
		out<<"]";
		return out;
	}

	template<typename U>
	class Iterator {
	private:
		ListNode<U>* current;
	public:
		Iterator(ListNode<U>* current) : current{current} {}

		U operator*() {
			return current->value;
		}
		Iterator<U>& operator++() {
			current = current->next;
			return *this;
		}
		bool operator!=(const Iterator<U>& other) {
			return this->current != other.current;
		}
		typedef std::input_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;
		typedef U value_type;
		typedef U* pointer;
		typedef U& reference;
	};
	typedef Iterator<T> iterator;

	Iterator<T> begin() {
		return iterator{this->_begin};
	}

	Iterator<T> end() {
		return iterator{nullptr};
	}



	friend void test_doubly_linked_list::test_create_append_clear();
};

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


#endif /* LIST_LIST_H_ */
