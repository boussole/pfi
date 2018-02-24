/*
Given an array A[] of n numbers and another number x, determine whether or not there exist two elements in A whose sum is exactly x.

Input:

The first line of input contains an integer T denoting the number of test cases.
The first line of each test case is N and X,N is the size of array.
The second line of each test case contains N integers representing array elements C[i].

Output:

Print "Yes" if there exist two elements in A whose sum is exactly x, else "No" without quotes.

Constraints:

1 ≤ T ≤ 200
1 ≤ N ≤ 200
1 ≤ C[i] ≤ 1000

Example:

Input:
2
6 16
1 4 45 6 10 8
5 10
1 2 4 3 6

Output:
Yes
Yes
 */
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

bool key_pair(vector<int> &arr, int x)
{
	sort(arr.begin(), arr.end());
	size_t i = 0, j = arr.size() - 1;
	while (i < j) {
		int sum = arr[i] + arr[j];
		if (sum == x)
			return true;

		if (sum < x)
			++i;
		else
			--j;
	}

	return false;
}

int main()
{
int nr_tests;
cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz, x;
		cin >> arr_sz >> x;

		vector<int> arr(arr_sz);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		cout << (key_pair(arr, x) ? "Yes" : "No") << endl;
	}

	return 0;
}
