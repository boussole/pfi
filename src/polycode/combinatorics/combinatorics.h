/**
 * \file    combinatorics.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef COMBINATORICS_H_
#define COMBINATORICS_H_

#include <common/common.h>

#if 0
char ** g_array = NULL;
int g_array_sz = 0;

void print_arr(char * arr[], int sz)
{
	for (int idx = 0; idx < sz; idx++) {
		std :: cout << arr[idx] << " ";
	}

	std :: cout << std :: endl;
}

/**
 * sequence process (recursive)
 */
void recursive_method(char * arr[], int sz)
{
	if (sz > 1) {
		for (int idx = 0; idx < sz; idx++) {
			boost :: swap(arr[0], arr[(idx)]);
			recursive_method(arr + 1, sz - 1);
			boost :: swap(arr[0], arr[(idx)]);
		}
	}
	else {
		print_arr(g_array, g_array_sz);
	}
}

/**
 * sequence process (iteration)
 */
void iteration_method(unsigned int num = 4)
{
//	std :: array<int, 4> arr = {1, 2, 3, 4};
	typedef std :: array<int, 4> seq_array;
	seq_array arr = {1, 2, 3, 4};
	bool stop = false;

	std :: for_each(arr.begin(), arr.end(), [](int el) {
		std :: cout << el << " ";
	});

	std :: cout << std :: endl;

	while (!stop) {
		stop = true;
		unsigned int left = arr.size() - 1, right = 0;
		while (left > 0) {
			right = left;
			left--;
			if (arr[left] < arr[right]) {
				unsigned int exchange = right + 1;
				while (exchange < arr.size()) {
					if ((arr[exchange] < arr[right]) && (arr[exchange] > arr[left])) {
						right = exchange;
					}
					exchange++;
				}

				boost :: swap(arr[left], arr[right]);
				std :: sort(arr.begin() + left + 1, arr.end());

				std :: for_each(arr.begin(), arr.end(), [](int el) {
					std :: cout << el << " ";
				});

				std :: cout << std :: endl;

				stop = false;

				break;
			}
		}
	}
}
#endif

namespace conq_combinatorics {

/*********************************************
 * \brief Permutation (recursive)
 *********************************************/
void permutation_R(std :: size_t n, std :: function<void(std :: unique_ptr<std :: size_t[]> &)> fn);

/*********************************************
 * \brief Permutation (iterative)
 *********************************************/
void permutation_I(std :: size_t n, std :: function<void(std :: unique_ptr<std :: size_t[]> &)> fn);

/*********************************************
 * \brief  Next permutation
 * \return false in case of no more permutations
 *********************************************/
bool nextPermutation(std :: unique_ptr<std :: size_t[]> & perm, std :: size_t n);

/*********************************************
 * \brief  Show all sets
 *********************************************/
void makeFullSet(std :: size_t n, std :: function<void(std :: unique_ptr<std :: size_t[]> &, std :: size_t)> fn);

/*********************************************
 * \brief  Subset of k-th size
 *********************************************/
void combinations(std :: size_t n, std :: size_t k, std :: function<void(std :: unique_ptr<std :: size_t[]> &)> fn);

} /* namespace conq_combinatorics */

#endif /* COMBINATORICS_H_ */
