/*
 * lab_k29_17_11_20_variadic.cpp
 *
 *  Created on: Nov 17, 2020
 *      Author: KZ
 */

#include "doctest.h"

#include <iostream>

#include <vector>
#include <string>
#include <cstdarg>


std::size_t total_size_old(std::vector<std::string> types, ...) {
    std::size_t result = 0;
    std::va_list args;
    va_start(args, types);
    for (const auto& type: types) {
    	//std::cout<<type<<std::endl;
    	if (type == "int") {
    		auto arg = va_arg(args, int);
    		//std::cout<<arg<<std::endl;
    		result += sizeof(arg);
    	} else if (type == "double") {
    		auto arg = va_arg(args, double);
    		//std::cout<<arg<<std::endl;
    		result += sizeof(arg);
    	} else if (type == "char") {
    		char arg = va_arg(args, int);
    		//std::cout<<arg<<std::endl;
    		result += sizeof(arg);
    	} else if (type == "string") {
    		char* arg = va_arg(args, char*);
    		//std::cout<<arg<<std::endl;
    		std::string string_arg { arg };
    		result += string_arg.size();
    	}
    }

    va_end(args);
    return result;
}


TEST_CASE("using C-style variadic functions") {
	auto result = total_size_old({"int", "int", "char", "string", "double"}, 12, 42, '?', "hello", 99.9);
	CHECK(result == 22);
}


