/**
 * \file    combinatorics.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include <combinatorics/combinatorics.h>

namespace conq_combinatorics {

/*********************************************
 * \brief Permutation (recursive)
 *********************************************/
void permutation_R(std :: size_t n, std :: function<void(std :: unique_ptr<std :: size_t[]> &)> fn)
{
	assert(n > 0);

	std :: unique_ptr<std :: size_t []> perm(new std :: size_t[n]);

	// fill basis
	for (std :: size_t i = 0; i < n; ++i)
		perm[i] = i + 1;

	std :: function<void(std :: size_t)> down = [&](std :: size_t level) {
		if (level == n - 1) {
			fn(perm);
			return;
		}

		for (std :: size_t i = level; i < n; ++i) {
			std :: swap(perm[i], perm[level]);
			down(level + 1);
			std :: swap(perm[i], perm[level]);
		}
	};

	down(0);
}

/*********************************************
 * \brief Permutation (iterative)
 *********************************************/
void permutation_I(std :: size_t n, std :: function<void(std :: unique_ptr<std :: size_t[]> &)> fn)
{
	assert(n > 0);

	std :: unique_ptr<std :: size_t []> perm(new std :: size_t[n]);

	for (std :: size_t i = 0; i < n; ++i)
		perm[i] = i + 1;

	do {
		fn(perm);
	} while (nextPermutation(perm, n));
}

/*********************************************
 * \brief Next permutation
 * \return false in case of no more permutations
 *********************************************/
bool nextPermutation(std :: unique_ptr<std :: size_t[]> & perm, std :: size_t n)
{
	int i = n - 2;

	while (i >= 0) {
		int candidate = i + 1;
		if (perm[i] < perm[candidate]) {
			for (int j = candidate + 1; j < static_cast<int>(n); ++j) {
				if (perm[i] < perm[j] && perm[j] < perm[candidate])
					candidate = j;
			}
			std :: swap(perm[i], perm[candidate]);
			std :: sort(&perm[i + 1], &perm[n]);
			return true;
		}
		--i;
	}

	return false;
}

/*********************************************
 * \brief  Show all sets
 *********************************************/
void makeFullSet(std :: size_t n, std :: function<void(std :: unique_ptr<std :: size_t[]> &, std :: size_t)> fn)
{
	std :: unique_ptr<std :: size_t[]> alphabet(new std :: size_t[n]);
	for (std :: size_t i = 1; i <= n; ++i)
		alphabet[i - 1] = i;

	std :: unique_ptr<std :: size_t[]> mask(new std :: size_t[n + 1]);
	std :: fill(mask.get(), mask.get() + n + 1, 0);

	std :: unique_ptr<std :: size_t[]> subset(new std :: size_t[n]);

	while (!mask[n]) {
		// make subset
		std :: size_t set_sz = 0;
		for (std :: size_t i = 0; i < n; ++i) {
			if (mask[i])
				subset[set_sz++] = alphabet[i];
		}

		fn(subset, set_sz);

		// next subset
		std :: size_t i = 0;
		while (mask[i] == 1) {
			mask[i++] = 0;
		}
		mask[i] = 1;
	}
}

/*********************************************
 * \brief  Subset of k-th size
 *********************************************/
void combinations(std :: size_t n, std :: size_t k, std :: function<void(std :: unique_ptr<std :: size_t[]> &)> fn)
{
	std :: unique_ptr<std :: size_t[]> alphabet(new std :: size_t[n]);
	for (std :: size_t i = 1; i <= n; ++i)
		alphabet[i - 1] = i;

	std :: unique_ptr<std :: size_t[]> mask(new std :: size_t[n]);
	std :: fill(mask.get(), mask.get() + 1, 0);

	std :: unique_ptr<std :: size_t[]> subset(new std :: size_t[k]);
	// basic
	for (std :: size_t i = 0; i < k; ++i) {
		mask[i] = 1;
		subset[i] = alphabet[i];
	}

	bool next = true;
	do {
		fn(subset);

		next = false;
		for (int i = static_cast<int>(n - 1), deadend = 0; i > -1; --i) {
			if (mask[i] == 1) {
				if (i != static_cast<int>(n - 1) && mask[i + 1] == 0) { // possible to move right
					mask[i] = 0;
					mask[i + 1] = 1;
					i += 2;
					std :: fill(&mask[i], &mask[i + deadend], 1);
					std :: fill(&mask[i + deadend], &mask[n], 0);
					for (std :: size_t i = 0, sz = 0; i < n; ++i) {
						if (mask[i] == 1)
							subset[sz++] = alphabet[i];
					}
					next = true;
					break;
				}
				else // skip slot
					++deadend;
			}
		}
	} while (next);
}

} /* namespace conq_combinatorics */
