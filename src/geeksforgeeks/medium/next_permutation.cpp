/*
   Implement the next permutation, which rearranges numbers into the numerically next greater permutation of numbers.

   If such arrangement is not possible, it must be rearranged as the lowest possible order ie, sorted in an ascending order.

   For example:
   1,2,3 → 1,3,2
   3,2,1 → 1,2,3

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an integer N depicting the size of array and next line followed by the value of array.

   Output:
   Print the array of next permutation in a separate line.

   Constraints:
   1 ≤ T ≤ 40
   1 ≤ N ≤ 100
   0 ≤ A[i] ≤ 100

   Example:
      Input
      1
      6
      1 2 3 6 5 4
      Output
      1 2 4 3 5 6
 */

#include <algorithm>
#include <iostream>
#include <memory>

using namespace std;

// speed O(N)
// memory O(1)
void next_permutation(unique_ptr<int[]> &arr, int arr_sz)
{
	for (int i = arr_sz - 1; i > 0; --i) {
		if (arr[i - 1] < arr[i]) {
			int left = i - 1;
			int right = i;
			// choose minimal which is greater than left
			while (right + 1 < arr_sz && arr[left] < arr[right + 1]) {
				++right;
			}

			swap(arr[left], arr[right]);
			reverse(arr.get() + left + 1, arr.get() + arr_sz);
			return;
		}
	}

	reverse(arr.get(), arr.get() + arr_sz);
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

		next_permutation(arr, arr_sz);

		for_each(arr.get(), arr.get() + arr_sz, [](int v) { cout << v << " "; } ); cout << endl;
	}

	return 0;
}
