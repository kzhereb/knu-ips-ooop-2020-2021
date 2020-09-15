/*
 * main.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: KZ
 */
// unit_doctest
// lecture2_08_09_20

#define current_ns unit_doctest

namespace current_ns {
	int main(int argc, char** argv);
}

int main_1(int argc, char** argv) {
	return current_ns::main(argc, argv);
}

