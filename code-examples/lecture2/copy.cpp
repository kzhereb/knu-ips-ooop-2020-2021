/*
 * copy.cpp
 *
 *  Created on: Sep 8, 2020
 *      Author: KZ
 */

#include <iostream>
#include <vector>
using namespace std;

class Obj {
public:
	int val;
	Obj(int val): val{val} {}
};

ostream& operator<<(ostream& cout, const Obj& item) {
	cout<<"{val="<<item.val<<"}";
	return cout;
}

ostream& operator<<(ostream& out, const Obj* item) {
	out<<"{val="<<item->val<<"}";
	return out;
}


template <typename T>
ostream& operator<<(ostream& out, const vector<T>& items) {
	for (const auto & item: items) {
		out<<item<<" ";
	}
	out<<endl;
	return out;
}

void test_deepcopy() {
	cout<<"deepcopy"<<endl;
	vector<Obj> a = {Obj(1), Obj(2), Obj(3)};
	vector<Obj> b = a;
	cout<<a;
	b[1] = Obj(42);
	cout<<b;
	cout<<a;
	b[2].val = 123;
	cout<<b;
	cout<<a;
}

void test_reference() {
	cout<<"test_reference"<<endl;
	vector<Obj> a = {Obj(1), Obj(2), Obj(3)};
	vector<Obj>& b = a;
	cout<<a;
	b[1] = Obj(42);
	cout<<b;
	cout<<a;
	b[2].val = 123;
	cout<<b;
	cout<<a;
}

void test_shallowcopy() {
	cout<<"test_shallowcopy"<<endl;
	vector<Obj*> a = {new Obj(1), new Obj(2), new Obj(3)};
	vector<Obj*> b = a;
	cout<<a;
	b[1] = new Obj(42);
	cout<<b;
	cout<<a;
	b[2]->val = 123;
	cout<<b;
	cout<<a;
}


int main() {
	// your code goes here
	test_deepcopy();
	test_reference();
	test_shallowcopy();

	return 0;
}




