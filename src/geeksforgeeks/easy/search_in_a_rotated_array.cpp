/*
   Given a sorted and rotated array (rotated at some point) A[ ], and given an element K,
   the task is to find the index of the given element K in the array A[ ].
   The array has no duplicate elements. If the element does not exist in the array, print -1.

   Input:
   The first line of the input contains an integer T, depicting the total number of test cases.
   Then T test cases follow. Each test case consists of three lines.
   First line of each test case contains an integer N denoting the size of the given array.
   Second line of each test case contains N space separated integers denoting the elements of the array A[ ].
   Third line of each test case contains an integer K denoting the element to be searched in the array.

   Output:
   Corresponding to each test case, print in a new line, the index of the element found in the array.
   If element is not present, then print -1.

   Constraints:
   1 ≤ T ≤ 100
   1 ≤ N ≤ 100005
   0 ≤ A[i] ≤ 10000005
   1 ≤ k ≤ 100005

   Example:
      Input
      3
      9
      5 6 7 8 9 10 1 2 3
      10
      3
      3 1 2
      1
      4
      3 5 1 2
      6

      Output
      5
      1
     -1
     **For More Examples Use Expected Output**

   http://www.practice.geeksforgeeks.org/problem-page.php?pid=146
 */

#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 100;

static const int MinArrSz = 1;
static const int MaxArrSz = 100005;

static const int MinArrValue = 0;
static const int MaxArrValue = 10000005;

static const int MinK = 1;
static const int MaxK = 100005;

// speed O(LogN)
// memory O(1)
int search_in_a_rotated_array_v1(const unique_ptr<int[]> &arr, int arr_sz, int k)
{
	if (arr_sz <= 0)
		return -1;

	if (arr_sz == 1)
		return arr[0] == k ? 0 : -1;

	// find minimum element, cause all elements are unique, it is also unique
	// speed O(LogN)
	// memory O(1)
	int a = 0, b = arr_sz - 1;
	while (a < b) {
		int c = (a + b) / 2;
		if (arr[c] < arr[b])
			b = c;
		else
			a = c + 1;
	}

	// find value in a appropriate area
	// speed O(LogN)
	// memory O(1)
	if (k >= arr[a] && k <= arr[arr_sz - 1]) {
		b = arr_sz - 1;
	} else {
		if (a == 0)
			return -1;

		b = a - 1;
		a = 0;
	}

	while (a < b) {
		int c = (a + b) / 2;
		if (arr[c] < k)
			a = c + 1;
		else
			b = c;
	}

	return arr[a] == k ? a : -1;
}

// speed O(LogN)
// memory O(1)
int search_in_a_rotated_array_v2(const unique_ptr<int[]> &arr, int arr_sz, int k)
{
	if (arr_sz <= 0)
		return -1;

	int a = 0, b = arr_sz - 1;

	// two cases here
	// 1. if there is an area [x..y] such that x < y, so no rotation in this area
	// 2. only one of two area's can contain rotation
	// 3. it is possible to confirm whether unrotated area contain value, using simple comparation
	// 4. if unrotated area doesn't contain value, look rotated area

	while (a < b) {
		int c = (a + b) / 2;

		if (arr[c] < arr[b]) {
			// the right area is unrotated
			if (arr[c] < k && arr[b] >= k)
				a = c + 1;
			else
				b = c;
		} else {
			// the left area is unrotated
			if (arr[a] <= k && arr[c] >= k)
				b = c;
			else
				a = c + 1;
		}
	}

	return arr[a] == k ? a : -1;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints: 1 ≤ N ≤ 100\n";
		return 1;
	}

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		if (arr_sz < MinArrSz || arr_sz > MaxArrSz) {
			cerr << "constraints: 1 ≤ N ≤ 100005\n";
			return 1;
		}

		unique_ptr<int[]> arr(new int[arr_sz]());
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
			if (arr[i] < MinArrValue || arr[i] > MaxArrValue) {
				cerr << "constraints: 0 ≤ A[i] ≤ 10000005\n";
				return 1;
			}

			cerr << arr[i] << " ";
		}
		cerr << endl;

		int k;
		cin >> k;
		if (k < MinK || k > MaxK) {
			cerr << "constraints: 1 ≤ k ≤ 100005\n";
			return 1;
		}

		cerr << "k = " << k << endl;
		int ans_1 = search_in_a_rotated_array_v1(arr, arr_sz, k), ans_2 = search_in_a_rotated_array_v2(arr, arr_sz, k);
		assert(ans_1 == ans_2);
		cout << ans_1 << endl;
	}

	return 0;
}

