/*
Given an unsorted array of non-negative integers, find a continuous sub-array which adds to a given number.

Input:
The first line of input contains an integer T denoting the number of test cases. Then T test cases follow. Each test case consists of two lines. The first line of each test case is N and S, where N is the size of array and S is the sum. The second line of each test case contains N space separated integers denoting the array elements.

Output:
Corresponding to each test case, in a new line, print the starting and ending positions of first such occuring subarray if sum equals to subarray, else print -1.

Note: Position of 1st element of the array should be considered as 1.

Expected Time Complexity: O(n)

Constraints:
1 ≤ T ≤ 100
1 ≤ N ≤ 100
1 ≤ an array element ≤ 200

Example:

Input:
2
5 12
1 2 3 7 5
10 15
1 2 3 4 5 6 7 8 9 10

Output:
2 4
1 5

Explanation :
In first test case, sum of elements from 2nd position to 4th position is 12
In second test case, sum of elements from 1st position to 5th position is 15
 */

#include <vector>
#include <iostream>
#include <utility>

using namespace std;

pair<int, int> subarray_with_given_sum(const vector<int> &arr, int sum)
{
	size_t start = 0, i = 1;
	int cur_sum = arr[start];

	while (i <= arr.size()) {

		if (cur_sum == sum) {
			return make_pair(start + 1, i);
		}

		if (cur_sum < sum) {
			if (i < arr.size())
				cur_sum += arr[i];
			++i;
		}
		else {
			while (start <= i && cur_sum > sum) {
				cur_sum -= arr[start++];
			}
		}
	}

	return make_pair(-1, -1);
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz, sum;
		cin >> arr_sz >> sum;

		vector<int> arr(arr_sz);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		pair<int, int> ans = subarray_with_given_sum(arr, sum);
		if (ans.first == -1)
			cout << -1 << endl;
		else
			cout << ans.first << " " << ans.second << endl;
	}

	return 0;
}

