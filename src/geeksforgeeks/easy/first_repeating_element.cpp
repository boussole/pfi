/**
   Find the first repeating element in an array of integers, i.e.,
   an element that occurs more than once and whose index of first occurrence is smallest.

   Input:
   The first line contains an integer 'T' denoting the total number of test cases.
   In each test cases, First line is number of elements in array 'N' and second its values.

   Output:
   In each separate line print the index of first repeating element,
   if there is not any repeating element then print “-1”. Use 1 Based Indexing.

   Constraints:
   1 <= T <=500
   1 <= N <=10000
   0 <= a[i] <=10000

   Example:
      Input:
      1
      7
      1 5 3 4 3 5 6

      Output:
      2

   Explanation:
   5 is appearing twice and its first appearance is at index 2 which is less than 3 whose first occurring index is 3.
 */

#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

/**
 * speed(avg): O(N)
 * memory    : O(N)
 */
int find_first_repeating_element(unique_ptr<int[]> &arr, size_t sz)
{
	size_t r = sz;
	unordered_map<int, size_t> tbl;

	for (size_t i = 0; i < sz; ++i) {
		unordered_map<int, size_t>::const_iterator it = tbl.find(arr[i]);
		if (it == tbl.cend()) {
			tbl.insert(make_pair(arr[i], i));
		} else if (it->second < r) {
			r = it->second;
		}
	}

	return r == sz ? -1 : r + 1;
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

		cout << find_first_repeating_element(arr, arr_sz) << endl;
	}

	return 0;
}
