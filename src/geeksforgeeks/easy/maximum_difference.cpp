/*
Given an array C[] of integers, find out the maximum difference between any two elements such that larger element appears after the smaller number in C[].
Examples: If array is [2, 3, 10, 6, 4, 8, 1] then returned value should be 8 (Diff between 10 and 2). If array is [ 7, 9, 5, 6, 3, 2 ] then returned value should be 2 (Diff between 7 and 9).

Input:

The first line of input contains an integer T denoting the number of test cases.
The first line of each test case is N,N is the size of array.
The second line of each test case contains N input C[i].

Output:

Print the maximum difference between two element. Otherwise print -1

Constraints:

1 ≤ T ≤ 80
2 ≤ N ≤ 100
1 ≤ C[i] ≤ 500

Example:

Input:
2
7
2 3 10 6 4 8 1
5
1 2 90 10 110

Output:
8
109
 */

#include <iostream>
#include <vector>

using namespace std;

// speed O(N)
// memory O(1)
int maximum_difference(const vector<int> &arr)
{
	int max_diff = 0;
	size_t max_i = 1;
	for (size_t i = 2; i < arr.size(); ++i) {
		if (arr[i] > arr[max_i])
			max_i = i;
	}

	for (size_t i = 0; i < arr.size() - 1; ++i) {
		if (i == max_i) {
			max_i = i + 1;
			for (size_t j = max_i; j < arr.size(); ++j) {
				if (arr[j] > arr[max_i])
					max_i = j;
			}
		}

		max_diff = max(arr[max_i] - arr[i], max_diff);
	}

	return max_diff;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		vector<int> arr(arr_sz);
		for (int i = 0; i < arr_sz; ++i)
			cin >> arr[i];

		cout << maximum_difference(arr) << endl;
	}

	return 0;
}
