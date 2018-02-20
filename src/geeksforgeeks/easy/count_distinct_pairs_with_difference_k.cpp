/*
Given an integer array and a non-negative integer k, count all distinct pairs with difference equal to k, i.e., A[ i ] - A[ j ] = k.

Input:
The first line of input consists number of the test cases. The description of T test cases is as follows:
The first line of each test case contains the size of the array, the second line has the elements of the array and the third line consists of the difference k.

Output:
In each separate line print the number of times difference k exists between the elements of the array.

Constraints:
1 ≤ T ≤ 100
1 ≤ N≤ 100
0≤K≤100
0 ≤ A[i] ≤ 10000

Example:
Input:
3
5
1 5 4 1 2
0
3
1 1 1
0
3
1 5 3
2

Output:
1
1
2
*/

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

using namespace std;

int count_distinct_pairs_with_difference_0_hash_version(vector<int> &arr)
{
	unordered_map<int, size_t> hash_tbl;
	for (auto &v : arr) {
		++hash_tbl[v];
	}

	int ans = 0;
	for (auto &v : hash_tbl) {
		if (v.second > 1)
			++ans;
	}

	return ans;
}

int count_distinct_pairs_with_difference_k_hash_version(vector<int> &arr, int k)
{
	if (k == 0)
		return count_distinct_pairs_with_difference_0_hash_version(arr);

	unordered_set<int> hash_tbl;
	for (auto &v : arr) {
		hash_tbl.insert(v);
	}

	int ans = 0;
	for (auto &v : arr) {
		unordered_set<int>::const_iterator first = hash_tbl.find(v);
		if (first == hash_tbl.end())
			continue;

		int diff = abs(k - v);
		unordered_set<int>::const_iterator second = hash_tbl.find(diff);
		if (second == hash_tbl.end())
			continue;

		++ans;
		hash_tbl.erase(first);
	}

	return ans;
}

int count_distinct_pairs_with_difference_k_sort_version(vector<int> &arr, int k)
{
	sort(arr.begin(), arr.end());

	int ans = 0;
	size_t l = 0, r = 1;
	while (r < arr.size()) {
		int diff = abs(arr[r] - arr[l]);
		if (diff == k) {
			++ans;
			// skip duplicates
			int duplicate = arr[r];
			while (r < arr.size() && arr[r] == duplicate) {
				++r;
			}

			++l;
		} else {
			if (diff < k)
				++r;
			else
				++l;

			if (l == r)
				++r;
		}
	}

	return ans;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		vector<int> arr(arr_sz);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		int k;
		cin >> k;

		cout << count_distinct_pairs_with_difference_k_sort_version(arr, k) << endl;
	}

	return 0;
}

