/*
 * lab_ips22_2024_03_20_callable.cpp
 *
 *  Created on: Mar 20, 2024
 *      Author: KZ
 */

#include <vector>

#include "doctest.h"

typedef int (*int_function_type)(int);

std::vector<int> map(const std::vector<int>& items, int_function_type func) {
  std::vector<int> result(items.size());
  for(std::size_t i = 0; i< items.size(); i++) {
    result[i] = func(items[i]);
  }
  return result;
 }

int square(int x) { return x*x;}

TEST_CASE("list of squares") {
  std::vector<int> input{1,2,3};
  std::vector<int> result;
  SUBCASE("function pointer") {
    result = map(input, &square);
  }
  SUBCASE("lambda") {
    result = map(input, [](int x) {return x*x;});
  }
  CHECK(result.size() == 3);
  CHECK(result[0] == 1);
  CHECK(result[1] == 4);
  CHECK(result[2] == 9);
}


