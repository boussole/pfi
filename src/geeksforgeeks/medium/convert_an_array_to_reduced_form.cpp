/*
   Given an array with n distinct elements, convert the given array to a reduced
   form where all elements are in range from 0 to n-1. The order of elements is same,
   i.e., 0 is placed in place of smallest element, 1 is placed for second smallest element, … n-1 is placed for largest element.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   The first line of each test case is N, where N is the size of array.
   The second line of each test case contains N input arr[i].

   Output:
   Print the reduced form of the array.

   Constraints:
   1 ≤ T ≤ 100
   1 ≤ N ≤ 200
   1 ≤ arr[i] ≤ 1000

   Example:
      Input:
      2
      3
      10 40 20
      5
      5 10 40 30 20

      Output:
      0 2 1
      0 1 4 3 2
 */

#include <iostream>
#include <memory>

using namespace std;

/**
 * speed O(N + MAXVAL)
 * memory O(MAXVAL)
 */
void convert_an_array_to_reduced_form(unique_ptr<int[]> &arr, size_t size)
{
	/* WARNING!!! An input condition gives up a limit for values [0 <= arr[i] <= 1000], so we can use here counting sort */
	constexpr size_t counter_arr_sz = 1001;
	unique_ptr<uint16_t[]> counter_arr(new uint16_t[counter_arr_sz]()); // 2 bytes * 1001 = 2002 bytes => not so much

	for (size_t i = 0; i < size; ++i)
		counter_arr[arr[i]] = 1;

	uint16_t counter = 0;
	for (size_t i = 0; i < counter_arr_sz; ++i) {
		if (counter_arr[i] > 0) {
			counter_arr[i] = counter++;
		}
	}

	for (size_t i = 0; i < size; ++i)
		arr[i] = counter_arr[arr[i]];
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

		convert_an_array_to_reduced_form(arr, arr_sz);

		for (int i = 0; i < arr_sz; ++i)
			cout << arr[i] << " ";
		cout << endl;
	}

	return 0;
}



