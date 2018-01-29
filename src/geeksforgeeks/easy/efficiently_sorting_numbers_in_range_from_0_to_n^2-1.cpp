/*
   Given an array of numbers of size n.
   It is also given that the array elements are in range from 0 to n2 – 1.
   Sort the given array in linear time.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Then T test cases follow.
   Each test case contains an integer n denoting the size of the array.
   The following line contains n space separated integers.

   Output:
   Sort the given array in linear time.

   Constraints:
   1<=T<=10^5
   1<=n<=10^4
   1<=a[i]<=(10^4)-1

   Example:
   Input:
      2
      7
      40 12 45 32 33 1 22
      5
      24 12 0 15 8

   Output:
      1 12 22 32 33 40 45
      0 8 12 15 24
 */

#include <iostream>
#include <memory>

using namespace std;

/**
 * speed  O(N)
 * memory O(N)
 */
void counting_sort(unique_ptr<int[]> &arr, int sz, int base)
{
	int count[10] = {0};
	unique_ptr<int[]> out(new int[sz]());

	for (int i = 0; i < sz; ++i) {
		++count[(arr[i] / base) % 10];
	}

	for (int i = 1; i < 10; ++i) {
		count[i] += count[i - 1];
	}

	for (int i = sz - 1; i > -1; --i) {
		int index = (arr[i] / base) % 10;
		out[--count[index]] = arr[i];
	}

	copy(out.get(), out.get() + sz, arr.get());
}

/**
 * speed  O(N)
 * memory O(N)
 */
void efficiently_sorting_numbers_in_range_from_0_to_n_square(unique_ptr<int[]> &arr, int sz)
{
	// find the maximum number
	int max_val = arr[0];
	for (int i = 0; i < sz; ++i) {
		if (arr[i] > max_val)
			max_val = arr[i];
	}

	int base = 1;
	do {
		counting_sort(arr, sz, base);
		base *= 10;
	} while (base <= max_val);
}
/*
Prevent finding of max value (https://www.geeksforgeeks.org/sort-n-numbers-range-0-n2-1-linear-time/)
-------------------------------------

How to sort if range is from 1 to n2?
If range is from 1 to n n2, the above process can not be directly applied, it must be changed. Consider n = 100 and range from 1 to 10000. Since the base is 100, a digit must be from 0 to 99 and there should be 2 digits in the numbers. But the number 10000 has more than 2 digits. So to sort numbers in a range from 1 to n2, we can use following process.
1) Subtract all numbers by 1.
2) Since the range is now 0 to n2, do counting sort twice as done in the above implementation.
3) After the elements are sorted, add 1 to all numbers to obtain the original numbers.

How to sort if range is from 0 to n^3 -1?
Since there can be 3 digits in base n, we need to call counting sort 3 times.

This article is contributed by Bateesh. Please write comments if you find anything incorrect, or you want to share more information about the topic discussed above
*/

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		unique_ptr<int[]> arr(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		efficiently_sorting_numbers_in_range_from_0_to_n_square(arr, arr_sz);

		for (int i = 0; i < arr_sz; ++i) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	return 0;
}
