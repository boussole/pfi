/*

Write a program to find the majority element in the array. A majority element in an array A[] of size n is an element that appears more than n/2 times (and hence there is at most one such element).  If input array doesn't contain a majority element, then output "NO Majority Element"

Input:  The first line of the input contains T denoting the number of testcases. The first line of the test case will be the size of array and second line will be the elements of the array.
Output: For each test case the output will be the majority element of the array.
Constraints:

1 <=T<= 100

1 <=N<= 100

0 <= a[i]<= 100


Example:

Input:
2
5
3 1 3 3 2
3
1 2 3

Output:
3
NO Majority Element
 */

#include <vector>
#include <iostream>

using namespace std;

int majority_element(const vector<int> &arr)
{
	int cand = 0;
	size_t freq = 1;
	for (size_t i = 1; i < arr.size(); ++i) {
		if (freq == 0) {
			cand = i;
			++freq;
		}
		else {
			freq = (arr[i] != arr[cand]) ? freq - 1 : freq + 1;
		}
	}

	freq = 0;
	for (size_t i = 0; i < arr.size(); ++i) {
		if (arr[i] == arr[cand]) {
			++freq;
		}
	}

	return freq > arr.size() / 2 ? cand : -1;
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

		int idx = majority_element(arr);
		if (idx < 0)
			cout << "NO Majority Element\n";
		else
			cout << arr[idx] << endl;
	}

	return 0;
}

