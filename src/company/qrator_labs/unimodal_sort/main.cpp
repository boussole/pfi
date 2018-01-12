/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  conquistador
 */
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <assert.h>
//-
#include "unimodal_sort.h"

using namespace std;

static constexpr int DEFAULT_SIZE = 1000;

/**
 * \brief      Generate array of unique values
 * \details    Based on snuffle O(N)
 *             https://en.wikipedia.org/wiki/Fisher–Yates_shuffle
 * \param [in] size Array size
 */
void generate_uniq_array(vector<int> &v, size_t size)
{
	assert(size > 0);

	int val = -1 * (size / 2);

	v.resize(size);

	unsigned s = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator;
	generator.seed(s);

	for (size_t i = 0; i < size; ++i) {
		v[i] = val++;
		uniform_int_distribution<int> distribution(0, i);
		swap(v[i], v[distribution(generator)]);
	}
}

/**
 * Test:
 *
 * 1 2 3 4 5 6
 * 6 5 4 3 2 1
 * 6 5 1 4 2 3
 * 5 1 4 3 2 -100 -1
 * 0 1
 * 1 0
 * 9 8 7 6 5 10 12 14
 */
int main(int argc, char *argv[])
{
	int size = DEFAULT_SIZE;

	if (argc > 1) {
		char *end = nullptr;
		size = strtol(argv[1], &end, 10);
		if ((end && *end) || size < 1) {
			cout << "invalid array size\n";
			return 1;
		}
	}

//	int n = n_swaps({1, 2, 3, 4, 5, 6});

//	int n = n_swaps({6, 5, 4, 3, 2, 1});

//	int n = n_swaps({7, 6, 5, 1, 4, 2, 3});

//	int n = n_swaps({5, 1, 4, 3, 2, -100, -1});

//	int n = n_swaps({0, 1});

//	int n = n_swaps({1, 0});

//	int n = n_swaps({9, 8, 7, 6, 5, 10, 12, 14});

	vector<int> a;

	generate_uniq_array(a, static_cast<size_t>(size));

	int n = n_swaps(a);

	cout << "min swaps = " << n << endl;

	return 0;
}
