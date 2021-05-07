/*
 * lab_k29_2021_04_23_threads.cpp
 *
 *  Created on: Apr 23, 2021
 *      Author: KZ
 */

#include "../doctest.h"
#include <vector>
#include <functional>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>


class Timer {
private:
	std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
	Timer(std::string name) {
		this->name = name;
		this->start = std::chrono::high_resolution_clock::now();
	}
	~Timer() {
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Timer " << name << ": "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(
						end - start).count() << "ms" << std::endl;
	}
};


std::vector<int> custom_transform_sequential(const std::vector<int>& input, std::function<int(int)> func) {
	std::size_t size = input.size();
	std::vector<int> result(size);
	for(std::size_t i = 0; i<size; i++) {
		result[i] = func(input[i]);
	}
	return result;
}

std::vector<int> custom_transform_parallel(const std::vector<int>& input, std::function<int(int)> func) {
	std::size_t size = input.size();
	std::vector<int> result(size);

	std::size_t num_threads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(num_threads);
	std::size_t thread_size = (size / num_threads)+1;
	std::size_t start = 0;
	for (std::size_t i=0; i<num_threads; i++) {
		threads[i] = std::thread(
				[=, &input, &result] () {
						//std::cout<<"worker thread "<<i<<" starts at "<<start<<std::endl;
						for(std::size_t j = start; j < std::min(start+thread_size, size); j++) {
							result[j] = func(input[j]);
						}
					}
				);
		start+= thread_size;
	}
	for (std::size_t i=0; i<num_threads; i++) {
		threads[i].join();
	}



	return result;
}

long long custom_accumulate_sequential(const std::vector<int>& input, std::function<long long(long long, int)> func, long long init_value = 0) {
	std::size_t size = input.size();
	long long result = init_value;
	for(std::size_t i = 0; i<size; i++) {
		result = func(result, input[i]);
	}
	return result;
}


TEST_CASE("custom transform - sequential and parallel") {
	std::vector<int> mylist {1, 2, 3, 4, 5};

	std::function<int(int)> square = [](int value) { return value*value; };

	std::vector<int> result;
	SUBCASE("sequential") {
		result = custom_transform_sequential(mylist, square);
	}
	SUBCASE("parallel") {
		result = custom_transform_parallel(mylist, square);
	}

	CHECK(result == std::vector<int>{1, 4, 9, 16, 25});
}

TEST_CASE("custom transform - measure time") {
	std::size_t size = 1e6;
	std::vector<int> mylist(size, 1);

	std::function<int(int)> square = [](int value) { return value*value; };

	std::vector<int> result;
	SUBCASE("sequential") {
		Timer timer{"sequential-square"};
		result = custom_transform_sequential(mylist, square);
	}
	SUBCASE("parallel") {
		Timer timer{"parallel-square"};
		result = custom_transform_parallel(mylist, square);
	}

	CHECK(result == mylist);
}

struct SumFunctor {
private:
	long long sum;
public:
	SumFunctor():sum(0) {};

	int operator()(int value) {
		sum+=value;
		return value;
	}
	long long get_value() { return sum; }
};

struct SumFunctorThreadSafe {
private:
	long long sum;
	std::mutex mutex;
public:
	SumFunctorThreadSafe():sum(0) {};

	int operator()(int value) {
		{
			std::lock_guard<std::mutex> lock(mutex);
			//mutex.lock(); //done automatically by lock_guard constructor
			sum+=value;
			//mutex.unlock(); //done automatically by lock_guard destructor that is triggered by going out of scope
		}
		return value;
	}
	long long get_value() { return sum; }
};


TEST_CASE("using transform instead of accumulate/reduce - just for demo, don't use in real code") {
	std::vector<int> mylist {1, 2, 3, 4, 5};

	//std::function<int(int)> accumulate_sum = [](int value) { sum+=value; return value; };

	SumFunctor accumulate_sum;
	long long sum;
	SUBCASE("functor with transform") {
		std::vector<int> result;
		SUBCASE("sequential") {
			result = custom_transform_sequential(mylist, std::ref(accumulate_sum));
		}
		SUBCASE("parallel") {
			result = custom_transform_parallel(mylist, std::ref(accumulate_sum));
		}
		CHECK(result == std::vector<int>{1, 2, 3, 4, 5});
		sum = accumulate_sum.get_value();
	}
	SUBCASE("accumulate") {
		std::function<long long(long long, int)> plus = [](
				long long prev_result, int value) {
			return prev_result + value;
		};
		sum = custom_accumulate_sequential(mylist, plus);
	}
	CHECK(sum == 15);

}


TEST_CASE("using big vector") {
	std::size_t size = 1e6;
	std::vector<int> mylist(size, 1);

	//std::function<int(int)> accumulate_sum = [](int value) { sum+=value; return value; };

	//SumFunctor accumulate_sum; //ERROR - won't work because of race condition
	SumFunctorThreadSafe accumulate_sum;

	std::vector<int> result;
	SUBCASE("sequential") {
		Timer time{"sequential-accumulate"};
		result = custom_transform_sequential(mylist, std::ref(accumulate_sum));
	}
	SUBCASE("parallel") {
		Timer time{"parallel-accumulate"};
		result = custom_transform_parallel(mylist, std::ref(accumulate_sum));
	}
	CHECK(result == mylist);
	long long sum = accumulate_sum.get_value();
	CHECK(sum == size);

}
