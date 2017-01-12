/*
   Given a sorted array which is rotated 'N' times. Find the value of 'N'.

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an integer N depicting the size of array and next line followed by the value of array.

   Output:
   Print the value of 'n'.

   Constraints:
   1 ≤ T ≤ 40
   1 ≤ N ≤ 100
   0 ≤ A[i] ≤ 100

   Example:
      Input
      2
      5
      5 1 2 3 4
      5
      1 2 3 4 5

      Output
      1
      0

      **For More Examples Use Expected Output**

      // grow up sorted???
      // rotation to the right???
 */

#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 40;

static const int MinArraySz = 1;
static const int MaxArraySz = 100;

// speed O(N)
// memory O(1)
int rotation_v1(const unique_ptr<int[]> &arr, int size)
{
	if (size < 2)
		return 0;

	for (int i = 0; i < size - 1; ++i) {
		if (arr[i] > arr[i + 1])
			return i + 1;
	}

	return 0;
}

// speed O(LogN)
// memory O(1)
int rotation_v2(const unique_ptr<int[]> &arr, int size)
{
	if (size < 2)
		return 0;

	int a = 0, b = size - 1;
	while (a < b) {
		int c = (a + b) / 2;
		if (arr[c] <= arr[b])
			b = c;
		else
			a = c + 1;
	}

	return a;
}

int main()
{
	int nr_tests = 0;
	cin >> nr_tests;

	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints: 1 ≤ T ≤ 40\n";
		return 1;
	}

	while (nr_tests--) {
		int arr_sz = 0;
		cin >> arr_sz;

		if (arr_sz < MinArraySz || arr_sz > MaxArraySz) {
			cerr << "constraints: 1 ≤ N ≤ 100\n";
			return 1;
		}

		unique_ptr<int[]> arr(new int[arr_sz]());
		int i = 0;
		while (i < arr_sz) {
			cin >> arr[i];
			cerr << arr[i] << " ";
			++i;
		}
		cerr << endl;

		int n1 = rotation_v1(arr, arr_sz), n2 = rotation_v2(arr, arr_sz);
		assert(n1 == n2);
		cout << n1 << endl;
	}

	return 0;
}
