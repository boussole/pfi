/*
   Given an array of positive integers. Find the maximum sum of strictly increasing subarrays.

   Example:
   Input: arr[] = {1, 2, 3, 2, 5, 1, 7}
   Output: 8

   Explanation:
   Some Strictly increasing subarrays are -
   {1, 2, 3} sum = 6,
   {2, 5} sum = 7,
   {1, 7} sum = 8,

   maximum sum = 8

   Input:
   The first line of input contains T denoting the no. of test cases.
   Then T test cases follow.
   The first line of each test case contains an Integer N and the next line contains N
   space separated values of the array A[ ] .

   Output:
   For each test case output the required result in a new line.

   Constraints:
   1<=T<=100
   1<=N<=100
   1<=A[]<=1000

   Example:
   Input:
   2
   7
   1 2 3 2 5 1 7
   4
   1 2 2 4
   Output:
   8
   6
*/

#include <assert.h>

#include <iostream>
#include <vector>

using namespace std;

// speed O(N)
// memory O(1)
size_t find_maximum_sum_strictly_increasing_subarray(const vector<int> &arr)
{
	assert(!arr.empty());

	size_t max_sum = arr[0], sum = arr[0];
	for (size_t i = 1; i < arr.size(); ++i) {
		if (arr[i] > arr[i - 1]) {
			sum += arr[i];
		} else {
			max_sum = max(max_sum, sum);
			sum = arr[i];
		}
	}

	return max(max_sum, sum);;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;
	while (nr_tests--) {
		int size;
		cin >> size;
		vector<int> arr(size);
		for (size_t i = 0; i < arr.size(); ++i)
			cin >> arr[i];

		cout << find_maximum_sum_strictly_increasing_subarray(arr) << endl;
	}

	return 0;
}

