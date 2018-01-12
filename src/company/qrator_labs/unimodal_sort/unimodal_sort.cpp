/**
 * \file    min_swap_sort.cpp
 * \brief
 * \details
 * \author  conquistador
 */

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <functional>
#include <list>
#include <tuple>
//-
#include "unimodal_sort.h"

using namespace std;

/**
 * \brief Minimal quantity to sort sequence in order:
 *        a[0] > a[1] > a[2] > … > a[k - 1] > a[k] < a[k+1] < a[k+2] < … a[N]
 *
 *        Speed  O(N^2)
 *        Memory O(N)
 */
int n_swaps(const std :: vector<int> &a)
{
	int counter = 0;

#ifdef DEBUG_UNIMODAL_SORT
		cout << "in :";
		for (size_t i = 0; i < a.size(); ++i)
			cout << " " << a[i];
		cout << "\n---------\n";
#endif

	/**
	 * 0. Invariant
	 * since we have unique numbers (task condition):
	 * - 1 minimal element (at the beginning or at the end or within array)
	 * - 2 elements that are greater than minimal and located and the beginning or at the end of array
	 * (or on one side depends on minimal element location)
	 */

	/**
	 * 1. Solution
	 * Let's keep invariant and solve this task:
	 * a) find maximal element in an array[0..N]
	 * b) move maximal element to the nearest side of array using neighbor swap
	 * c) shrink array from the beginning or from the end depends on direction of step 'b)'
	 * d) if sizeof(array) > 1 goto 'a)'
	 */

	/** 2. Implementation */
	/**
	 * Let's keep 2 lists for fast understanding of movement direction
	 * and heap to get a new maximal element with O(logN)
	 * Using heap we can find position of element in a left/right direction lists
	 */
	size_t middle = a.size() / 2;

	using HeapType = tuple<int, list<unsigned char>::const_iterator>;
	auto HeapTypeCmp = [](HeapType &lhs, HeapType &rhs) {
		return get<0>(lhs) < get<0>(rhs);
	};

	vector<HeapType> heap;

	list<unsigned char> direction[2];
	for (size_t i = 0; i < middle; ++i) {
		direction[0].push_front(0);
		heap.push_back(make_tuple(a[i], direction[0].cbegin()));
	}

	for (size_t i = middle; i < a.size(); ++i) {
		direction[1].push_back(1);
		heap.push_back(make_tuple(a[i], --direction[1].cend()));
	}

	make_heap(heap.begin(), heap.end(), HeapTypeCmp);

	while (!heap.empty()) {
		pop_heap(heap.begin(), heap.end(), HeapTypeCmp);

		list<unsigned char>::const_iterator it = get<1>(heap.back());
		int src = *it, dst = (src + 1) % 2;

#ifdef DEBUG_UNIMODAL_SORT
		cout << "left:  ";
		for (int i : direction[0])
			cout << i << " ";

		cout << "\nright: ";
		for (int i : direction[1])
			cout << i << " ";

		cout << "\nvalue = " << get<0>(heap.back()) << " (" << (src == 0 ? "left" : "right") << ")\n";
		cout << "---------\n";
#endif

		it = direction[src].erase(it);
		while (it != direction[src].cend()) {
			++it;
			++counter;
		}

		heap.pop_back();

		/** balance lists
		 *  NOTE: no need to balance lists with difference == 1, it means that we work with array of odd size
		 *        in case of odd array size we have the same distance from both side of array
		 */
		if (!direction[dst].empty() && (direction[src].size() + 1 < direction[dst].size())) {
			direction[src].splice(direction[src].cbegin(), direction[dst], direction[dst].cbegin());
			*direction[src].begin() = src;
		}
	}

	return counter;
}
