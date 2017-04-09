/*
   In a given array A[] find the maximum value of (A[i] – i) - (A[j] – j) where i is not equal to j.
   i and j vary from 0 to n-1 and N is size of input array A[].  Value of N is always greater than 1.

   Input:
   The first line of input contains a single integer T denoting the number of test cases.
   Then T test cases follow. Each test case consist of two lines.
   The first line of each test case consists of an integer N, where N is the size of array.
   The second line of each test case contains N space separated integers denoting array elements.

   Output:
   Corresponding to each test case, in a new line, print the maximum value.

   Constraints:
   1 ≤ T ≤ 100
   2 ≤ N ≤ 200
   1 ≤ A[i] ≤ 1000

   Example:
   Input
   1
   5
   9 15 4 12 13

   Output
   12

   Explanation
   (a[1]-1) - (a[2]-2) = (15-1)-(4-2) = 12
 */

#include <iostream>
#include <vector>

using namespace std;

// speed O(N)
// memory O(1)
int max_value(const vector<int> &arr)
{
	int small = arr[0] - 1, big = arr[0] - 1;
	for (size_t i = 0; i < arr.size(); ++i) {
		int value = arr[i] - (i + 1);
		small = min(small, value);
		big = max(big, value);
	}

	return big - small;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		size_t arr_sz;
		cin >> arr_sz;
		vector<int> arr(arr_sz);
		for (size_t i = 0; i < arr_sz; ++i)
			cin >> arr[i];

		cout << max_value(arr) << endl;
	}

	return 0;
}
