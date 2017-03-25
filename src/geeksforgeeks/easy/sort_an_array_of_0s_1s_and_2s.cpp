/*
   Write a program to sort an array of 0's,1's and 2's in ascending order.

   Input:
   The first line contains an integer 'T' denoting the total number of test cases.
   In each test cases, First line is number of elements in array 'N' and second its values.

   Output:
   Print the sorted array of 0's, 1's and 2's.

   Constraints:
   1 <= T <= 100
   1 <= N <= 100
   0 <= arr[i] <= 2

   Example:
   Input :
   2
   5
   0 2 1 2 0
   3
   0 1 0
   Output:

   0 0 1 2 2
   0 0 1
 */

#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

// speed O(N)
// memory O(1)
void sort_an_array_of_0s_1s_and_2s_v1(unique_ptr<int[]> &arr, int arr_sz)
{
	int counter[3] = {};
	for (int i = 0; i < arr_sz; ++i)
		++counter[arr[i]];

	int i = 0;
	for (int j = 0; j < 3; ++j) {
		while (counter[j]--)
			arr[i++] = j;
	}
}

// speed O(N)
// memory O(1)
// in one pass!!!
void sort_an_array_of_0s_1s_and_2s_v2(unique_ptr<int[]> &arr, int arr_sz)
{
	int zero = 0, one = 0, two = arr_sz - 1;
	while (one <= two) {
		switch (arr[one]) {
			case 0:
				swap(arr[zero++], arr[one++]);
				break;
			case 1:
				++one;
				break;
			case 2:
				swap(arr[two--], arr[one]);
				break;
			default: assert(false);
		}
	}
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		unique_ptr<int[]> arr_1(new int[arr_sz]), arr_2(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr_1[i];
			arr_2[i] = arr_1[i];
		}

		sort_an_array_of_0s_1s_and_2s_v1(arr_1, arr_sz);
		sort_an_array_of_0s_1s_and_2s_v2(arr_2, arr_sz);

		for (int i = 0; i < arr_sz; ++i) {
			cout << arr_2[i] << " ";
			assert(arr_1[i] == arr_2[i]);
		}

		cout << endl;
	}
}

