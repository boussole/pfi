/*
   Given an array containing N numbers.
   The task is to find the maximum sum bitonic subarray.
   A bitonic subarray is a subarray in which elements are first increasing and then decreasing.
   A strictly increasing or strictly decreasing subarray is also considered as bitonic subarray.

   Time Complexity : O(n)
   Auxiliary Space : O(1)

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Then T test cases follow. Each test case consists of two lines.
   First line of each test case contains a integer N and the second line contains N space separated array elements.

   Output:
   For each test case, print the maximum bitonic subarray sum in new line.

   Constraints:
   1<=T<=200
   1<=N<=105
   1<=A[i]<=105

   Example:
      Input:
      2
      7
      5 3 9 2 7 6 4
      7
      5 4 3 2 1 10 6

      Output:
      19
      17
 */

#include <iostream>
#include <limits>
#include <memory>

using namespace std;

/**
 * speed : O(N)
 * memory: O(1)
 */
unsigned long maximum_bitonic_subarray_sum(const unique_ptr<unsigned int[]> &arr, size_t sz)
{
	size_t i = 0;
	unsigned long max_sum = arr[0];

	while (i < sz - 1) {
		unsigned long sum = arr[i];

		// while equal
		if (arr[i] == arr[i + 1]) {
			++i;
			if (max_sum < sum)
				max_sum = sum;

			continue;
		}

		// while increasing
		while(i < sz - 1 && arr[i] < arr[i + 1]) {
			sum += arr[++i];
		}

		// while decreasing
		while (i < sz - 1 && arr[i] > arr[i + 1]) {
			sum += arr[++i];
		}

		if (max_sum < sum)
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

		unique_ptr<unsigned int[]> arr(new unsigned int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i)
			cin >> arr[i];

		cout << maximum_bitonic_subarray_sum(arr, arr_sz) << endl;
	}

	return 0;
}
