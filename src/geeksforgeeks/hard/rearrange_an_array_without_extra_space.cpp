/*
   Given an array arr[] of size n where every element is in range from 0 to n-1.
   Rearrange the given array so that arr[i] becomes arr[arr[i]].
   This should be done with O(1) extra space.

   Input:
   First line contains an integer denoting the test cases 'T'.
   Every test case contains an integer value depicting size of array 'N' and
   N integer elements are to be inserted in the next line with spaces between them.

   Output:
   Print all elements of the array after rearranging, each separated by a space, in separate line for each test case.

   Constraints:
   1 <= T <= 70
   1 <= N<= 100
   1 <= Arr[i] <= 100
   Arr[i]<=N

   Example:
      Input:
      3
      2
      1 0
      5
      4 0 2 1 3
      4
      3 2 0 1

      Output:
      0 1
      3 4 2 0 1
      1 0 3 2
 */

#include <iostream>
#include <memory>

using namespace std;

/**
 * speed  O(N)
 * memory O(1)
 */
void rearrange_an_array_without_extra_space(unique_ptr<int[]> &arr, size_t size)
{
	constexpr int highest_bit = 1 << 31;
	for (size_t i = 0; i < size; ++i) {
		if (!(arr[i] & highest_bit)) {
			size_t dst_i = i, src_i = arr[i];
			int val = arr[i];
			while (src_i != i) {
				arr[dst_i] = arr[src_i] | highest_bit;
				dst_i = src_i;
				src_i = arr[dst_i];
			}

			arr[dst_i] = val | highest_bit;
		}

		arr[i] &= ~highest_bit;
	}

}

/*
 * Second solution from: https://www.geeksforgeeks.org/rearrange-given-array-place/
 *
 * Let us understand the above steps by an example array {3, 2, 0, 1}
 * In first step, every value is incremented by (arr[arr[i]] % n)*n
 * After first step array becomes {7, 2, 12, 9}.
 * The important thing is, after the increment operation
 * of first step, every element holds both old values and new values.
 * Old value can be obtained by arr[i]%n and new value can be obtained
 * by arr[i]/n.

 * In second step, all elements are updated to new or output values
 * by doing arr[i] = arr[i]/n.
 * After second step, array becomes {1, 0, 3, 2}
 */

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

		rearrange_an_array_without_extra_space(arr, arr_sz);

		for (int i = 0; i < arr_sz; ++i)
			cout << arr[i] << " ";
		cout << endl;
	}

	return 0;
}
