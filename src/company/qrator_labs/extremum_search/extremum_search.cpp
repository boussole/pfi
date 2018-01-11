/**
 * \file    extremum_search.cpp
 * \brief
 * \details
 * \author  conquistador
 */
#include "extremum_search.h"
#include <iostream>
using namespace std;

/**
 * \brief   Naive extremum search
 * \details Speed       = O(N)
 *          Comparison  = (N - 2) * 2 + 2 (with last assert)
 */
std :: size_t extremum_search_naive(std :: vector<int> &v)
{
	assert(v.size() > 1);

	std :: size_t e = 0;

	// extra case "begining"
	if (v[0] < v[1])
		return e;

	for (e = 1; e < v.size() - 1; ++e) {
		if (v[e - 1] > v[e] && v[e] < v[e + 1])
			return e;
	}

	// extra case "ending" (elements are all different, extremum here or error of input data)
	assert(v[e] < v[e - 1]);

	return e;
}


/**
 * \brief   Dichotomy extremum search
 * \details Speed      = O(logN)
 *          Comparison = 2 * logN + 1
 */
std :: size_t extremum_search_dichotomy(std :: vector<int> &v)
{
	int left = 0, right = v.size() - 1;

	while (left < right) {
		int e = (left + right) / 2;

		if (e != left && v[e - 1] < v[e]) {
			right = e;
			continue;
		}

		if (e != right && v[e + 1] < v[e]) {
			left = e + 1;
			continue;
		}

		left = e;
		break; // found
	}

	return static_cast<size_t>(left);
}
