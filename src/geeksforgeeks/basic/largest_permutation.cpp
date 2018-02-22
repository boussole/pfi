/*
Given a permutation of first n natural numbers as an array and an integer k. Print the lexicographically largest permutation after at most k swaps.

Input:
The first line of input contains an integer T denoting the number of test cases. Each test case contains two integers n and k where n denotes the number of elements in the array a[]. Next line contains space separated n elements in the array a[].

Output:
Print space separated n integers which form the largest permutation after at most k swaps.

Constraints:
1<=T<=100
1<=n<=1000
1<=a[i]<=1000
1<=k<=100 0

Example:
Input:
2
5 3
4 5 2 1 3
3 1
2 1 3
Output:
5 4 3 2 1
3 1 2
 */

#include <vector>
#include <iostream>

using namespace std;

void largest_permutation_after_at_most_k_swaps(vector<int> &arr, int k)
{
	vector<int> pos(arr.size());
	for (size_t i = 0; i < arr.size(); ++i) {
		pos[arr[i] - 1] = i;
	}

	int val = arr.size() - 1, dst = 0;
	while (val >= 0 && k > 0) {
		if (pos[val] != dst) {
			--k;
			int src = pos[val];
			swap(pos[val], pos[arr[dst] - 1]);
			swap(arr[src], arr[dst]);
		}

		++dst;
		--val;
	}
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz, k;
		cin >> arr_sz >> k;

		vector<int> arr(arr_sz);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		largest_permutation_after_at_most_k_swaps(arr, k);
		for (auto &i : arr)
			cout << i << " ";
		cout << endl;
	}

	return 0;
}
