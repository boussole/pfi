/*
Given an array arr[] of n integers, construct a Product Array prod[] (of same size) such that prod[i] is equal to the product of all the elements of arr[] except arr[i].

Input:

The first line of input contains an integer T denoting the number of test cases.
The first line of each test case is N,N is the size of array.
The second line of each test case contains N input A[i].

Output:

Print the Product array prod[].

Constraints:

1 ≤ T ≤ 10
1 ≤ N ≤ 15
1 ≤ C[i] ≤ 20

Example:

Input
2
5
10 3 5 6 2
2
12 20

Output
180 600 360 300 900
20 12
 */

#include <vector>
#include <iostream>

using namespace std;

void product_array_puzzle(vector<int> &arr)
{
	int product = 1;
	for (auto i : arr) {
		product *= i;
	}

	for (size_t i = 0; i < arr.size(); ++i) {
		arr[i] = product / arr[i];
	}
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		vector<int> arr(arr_sz);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		product_array_puzzle(arr);
		for (auto i : arr)
			cout << i << " ";
		cout << endl;
	}

	return 0;
}
