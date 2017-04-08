/*
   Given an array A your task is to tell at which position the equilibrium first occurs in the array.
   Equilibrium position in an array is a position such that
   the sum of elements below it is equal to the sum of elements after it.

   Input:
   The first line of input contains an integer T denoting the no of test cases then T test cases follow.
   First line of each test case contains an integer N denoting the size of the array.
   Then in the next line are N space separated values of the array A.

   Output:
   For each test case in a new line print the position at which the elements are at equilibrium
   if no equilibrium point exists print -1.

   Constraints:
   1<=T<=100
   1<=N<=100

   Example:
   Input:
   2
   1
   1
   5
   1 3 5 2 2

   Output:
   1
   3

   Explanation:
   1. Since its the only element hence its the only equilibrium point
   2. For second test case equilibrium point is at position 3 as elements below it (1+3) = elements after it (2+2)
 */

#include <iostream>
#include <vector>

using namespace std;

// speed O(N)
// memory O(1)
int equilibrium_point(const vector<int> &arr)
{
	// sum O(N)
	int64_t left = 0, right = 0;
	for (size_t i = 0; i < arr.size(); ++i)
		right += arr[i];

	// O(N)
	for (size_t i = 0; i < arr.size(); ++i) {
		right -= arr[i];
		if (left == right)
			return i;
		left += arr[i];
	}

	return -1;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;
	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;
		vector<int> arr(arr_sz);
		for (size_t i = 0; i < arr.size(); ++i)
			cin >> arr[i];

		int ep = equilibrium_point(arr);

		// the task requires an index started from 1, so correct it
		if (ep != -1)
			++ep;

		cout << ep << endl;
	}

	return 0;
}

