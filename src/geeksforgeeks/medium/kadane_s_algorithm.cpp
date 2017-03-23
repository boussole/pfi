/*
   Given an array containing both negative and positive integers.
   Find the contiguous sub-array with maximum sum.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   The description of T test cases follows.
   The first line of each test case contains a single integer N denoting the size of array.
   The second line contains N space-separated integers A1, A2, ..., AN denoting the elements of the array.

   Output:
   Print the maximum sum of the contiguous sub-array in a separate line for each test case.

   Constraints:
   1 ≤ T ≤ 40
   1 ≤ N ≤ 100
   -100 ≤ A[i] <= 100

   Example:
   Input
   2
   3
   1 2 3
   4
   -1 -2 -3 -4

   Output
   6
   -1
 */

#include <iostream>
#include <memory>

using namespace std;

// speed O(N)
// memory O(1)
int kadane_s_algorithm(const unique_ptr<int[]> &arr, int arr_sz)
{
	int max_sum = arr[0], sum = arr[0];

	for (int i = 1; i < arr_sz; ++i) {
		sum = max(sum + arr[i], arr[i]);
		if (sum > max_sum)
			max_sum = sum;
	}

	return max_sum;
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

		cout << kadane_s_algorithm(arr, arr_sz) << endl;
	}

	return 0;
}


