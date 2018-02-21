/*
Given an array of integers and a number K. Write a program to find the maximum sum of a subarray of size K.

Input:
First line of input contains a single integer T which denotes the number of test cases. Then T test cases follows. First line of each test case contains two space separated integers N and K where N denotes the number of elements. Second line of each test case contains N space separated integers which denotes the elements of the array.
Output:
For each test case print the maximum sum of a subarray of size K.

Constraints:
1<=T<=100
1<=N<=105
1<=K<=N

Example:
Input:
2
4 2
100 200 300 400
9 4
1 4 2 10 23 3 1 0 20
Output:
700
39
 */

#include <vector>
#include <iostream>

using namespace std;

int max_sum_subarray_of_size_k(const vector<int> &arr, size_t k)
{
	if (arr.size() < k)
		k = arr.size();

	int max_sum = arr[0];
	size_t i = 1;
	for (; i < k; ++i) {
		max_sum += arr[i];
	}

	int sum = max_sum;
	for (; i < arr.size(); ++i) {
		sum = sum - arr[i - k] + arr[i];
		max_sum = max(sum, max_sum);
	}

	return max_sum;
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

		cout << max_sum_subarray_of_size_k(arr, k) << endl;
	}

	return 0;
}

