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
//-
#include "extremum_search.h"

using namespace std;

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

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cout << "usage: " << *argv << " <array size>\n";
		return 1;
	}

	char *end = nullptr;
	int val = strtol(argv[1], &end, 10);
	if ((end && *end) || val <= 1) {
		cout << "invalid array size\n";
		return 1;
	}

	vector<int> v;

	generate_uniq_array(v, static_cast<size_t>(val));

	cout << "array:";
	for (size_t i = 0; i < v.size(); ++i) {
		if (i > 0)
			cout << ((v[i - 1] < v[i]) ? " <" : " >");
		cout << " ([" << i << "] = " << v[i] << ")";
	}
	cout << endl;

	int extremum = /*extremum_search_naive(v); */ extremum_search_dichotomy(v);

	cout << "extremum: [" << extremum << "] = " << v[extremum] << endl;

	return 0;
}
