/*
 * func.cpp
 *
 *  Created on: Sep 25, 2020
 *      Author: KZ
 */

#include "func.h"

// Approach 3: move implementation to cpp file
template<typename T>
T square(T value) {
	return value*value;
}

// Approach 3: declare all types we need to support
template int square<int>(int value);
template double square<double>(double value);


