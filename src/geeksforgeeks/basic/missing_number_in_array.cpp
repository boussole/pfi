/*
Given an array of size n-1 and given that there are numbers from 1 to n with one missing, the missing number is to be found.

Input:

The first line of input contains an integer T denoting the number of test cases.
The first line of each test case is N.
The second line of each test case contains N-1 input C[i],numbers in array.

Output:

Print the missing number in array.

Constraints:

1 ≤ T ≤ 200
1 ≤ N ≤ 1000
1 ≤ C[i] ≤ 1000

Example:

Input
2
5
1 2 3 5
10
1 2 3 4 5 6 7 8 10

Output
4
9
 */

#include <vector>
#include <iostream>

using namespace std;

/**
 * xor solution is better here, but I want to try another approach also in O(N),
 * but with modification of array
 */
int missing_number_in_array(vector<int> &arr)
{
	int mask = 1<<31;
	for (size_t i = 0; i < arr.size(); ++i) {
		int val = ((arr[i] - 1) & ~mask);
		if (val < static_cast<int>(arr.size()))
			arr[val] |= mask;
	}

	int ans = 0;
	for (size_t i = 0; i < arr.size(); ++i) {
		if ((arr[i] & mask) == 0)
			ans = i + 1;
		arr[i] &= ~mask;
	}

	return ans == 0 ? arr.size() + 1 : ans;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		vector<int> arr(arr_sz - 1);
		for (int i = 0; i < arr_sz - 1; ++i) {
			cin >> arr[i];
		}

		cout << missing_number_in_array(arr) << endl;
	}

	return 0;
}

