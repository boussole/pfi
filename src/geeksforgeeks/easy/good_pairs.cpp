/*
   You are given an array of positive integer numbers a1,a2...aN.
   Count number of pairs (i,j) such that:
   1≤ i ≤ N
   1≤ j ≤ N
   ai < aj

   Input:
   The first line contains 'T' denoting the number of testcases.
   Then follows description of testcases.Each case begins with a single positive integer N denoting the size of array.The second line contains N space separated positive integers denoting the elements of array.

   Output:
   For each test case, output a single line containing number of pairs for corresponding test case.

   Constraints:
   1<=T<=20
   1<=N<=10^3
   1<=a[i]<=10^3

   Example:
      Input :
      2
      2
      2 1
      3
      2 3 2

      Output :
      1
      2

      Explanation:
      In the first testcase, the only good pair is (2,1).
      In the second testcase, the two good pairs are (2,3) and (3,2).
 */

#include <assert.h>

#include <algorithm>
#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

// speed O(NlogN)
// memory O(1)
// note @arr is modified inside
uint32_t good_pairs_v1(unique_ptr<int[]> &arr, int arr_sz)
{
	uint32_t nr_pairs = 0;

	// O(NlogN)
	sort(arr.get(), arr.get() + arr_sz);

	// O(N)
	int nr_duplicates = 0, duplicate = 0, i = 0;
	while (i < arr_sz) {
		if (!nr_duplicates) {
			duplicate = i;
			++nr_duplicates;
			++i;
		} else {
			if (arr[i] == arr[duplicate]) {
				++nr_duplicates;
				++i;
			} else {
				nr_pairs += nr_duplicates * (arr_sz - i);
				nr_duplicates = 0;
			}
		}
	}

	return nr_pairs;
}

// speed O(N)
// memory O(N)
uint32_t good_pairs_v2(const unique_ptr<int[]> &arr, int arr_sz)
{
	uint32_t nr_pairs = 0;

	// put all numbers to hash of counters <value, counter>
	// 1 pass      = O(N)
	// put to hash = O(1) avg
	unordered_map<int, int> h_tbl;

	// O(N)
	for (int i = 0; i < arr_sz; ++i)
		// O(1) avg
		++h_tbl[arr[i]];

	// calculate all pairs with duplicates
	// ( n )
	// ( 2 ) = n! / 2! (n - 2)! = n * (n - 1) / 2
	nr_pairs = (arr_sz * (arr_sz - 1)) / 2;

	// remove redundant elements O(N)
	for (auto it = h_tbl.begin(); it != h_tbl.end(); ++it) {
		if (it->second == 1)
			continue;

		int nr_redundent_pairs = (((it->second + 1) * it->second) / 2) - it->second;
		nr_pairs -= nr_redundent_pairs;
	}

	return nr_pairs;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		unique_ptr<int[]> arr(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i)
			cin >> arr[i];

		// don't call v1 before v2, it modifies array !!!
		uint32_t ans_2 = good_pairs_v2(arr, arr_sz), ans_1 = good_pairs_v1(arr, arr_sz);
		assert(ans_1 == ans_2);

		cout << ans_1 << endl;
	}

	return 0;
}


