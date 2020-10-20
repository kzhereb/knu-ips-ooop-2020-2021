/*
 * lab_k29_20_10_20_unordered_map.cpp
 *
 *  Created on: Oct 20, 2020
 *      Author: KZ
 */

#include "doctest.h"

#include <unordered_map>
#include <string>

class TestHash {
public:
	int data;
	std::string name;
public:
	//Test(int data, std::string name) : data(data), name(name) {}
	bool operator==(const TestHash& other) const {
		return data == other.data && name == other.name;
	}
};

namespace std
{
    template<> struct hash<TestHash>
    {
        std::size_t operator()(TestHash const& test) const noexcept
        {
            std::size_t h1 = std::hash<int>{}(test.data);
            std::size_t h2 = std::hash<std::string>{}(test.name);
            return h1 ^ (h2 << 1); // or use boost::hash_combine
        }
    };
}


TEST_CASE("working with dictionaries (maps)") {
	std::unordered_map<std::string, int> mapping;
	mapping["hello"] = 123;
	mapping["world"] = 456;
	CHECK(mapping["hello"] == 123);
	CHECK(mapping["world"] == 456);
	CHECK(mapping.size() == 2);
}

TEST_CASE("custom class as key") {
	std::unordered_map<TestHash, int> mapping;
	TestHash test1{123, "hello"};
	mapping[test1] = 321;
	CHECK(mapping[test1] == 321);
	CHECK(mapping[{123, "hello"}] == 321);
}

