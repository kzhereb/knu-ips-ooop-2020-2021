/*
 * func.h
 *
 *  Created on: Sep 25, 2020
 *      Author: KZ
 */

#ifndef CODE_EXAMPLES_LAB_K29_25_09_20_TEMPLATES_FUNC_H_
#define CODE_EXAMPLES_LAB_K29_25_09_20_TEMPLATES_FUNC_H_

template<typename T>
T square(T value);

// Approach 1: move implementation to header
template<typename T>
T square(T value) {
	return value*value;
}

#endif /* CODE_EXAMPLES_LAB_K29_25_09_20_TEMPLATES_FUNC_H_ */
