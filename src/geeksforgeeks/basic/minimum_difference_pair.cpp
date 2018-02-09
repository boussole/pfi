/*
Given an unsorted array, find the minimum difference between any pair in given array.

Input:

The first line of input contains an integer T denoting the number of test cases.
The first line of each test case is N, the size of array. Second line of the test case is the Array.

Output:

Print the minimum difference between any two pairs.

Constraints:

1 <= T <= 30
1 < N <= 100
1 <= arr[i] <= 100000

Example:
Input:
2
5
2 4 5 7 9
10
87 32 99 75 56 43 21 10 68 49

Output:
1
6
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int min_diff_pair(vector<int> &arr)
{
	sort(arr.begin(), arr.end());
	int min_diff = numeric_limits<int>::max();
	for (size_t i = 1; i < arr.size(); ++i) {
		int cand = abs(arr[i] - arr[i - 1]);
		if (cand < min_diff)
			min_diff = cand;
	}

	return min_diff;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		size_t size;
		cin >> size;

		vector<int> arr(size);
		for (size_t i = 0; i < size; ++i)
			cin >> arr[i];

		cout << min_diff_pair(arr) << endl;
	}

	return 0;
}
