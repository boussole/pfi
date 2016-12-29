/*
   Given an integer K,return the kth row of pascal triangle.
   Pascal's triangle is a triangular array of the binomial coefficients
   formed by summing up the elements of previous row.

   Example of pascal triangle:
   1
   1 1
   1 2 1
   1 3 3 1

   for K=3, return 3rd row i.e 1 2 1

   Input:
   The first line contains an integer T,depicting total number of test cases.
   Then following T lines contains an integer N depicting the row of triangle to be printed.

   Output:
   Print the Nth row of triangle in a separate line.

   Constraints:
   1 ≤ T ≤ 50
   1 ≤ N ≤ 25

   Example:
      Input
      1
      4
      Output
      1 3 3 1

   http://www.practice.geeksforgeeks.org/problem-page.php?pid=123
 */

#include <iostream>
#include <memory>

using namespace std;

static const size_t MinNrTest = 1;
static const size_t MaxNrTest = 50;

static const size_t MinRowVal = 1;
static const size_t MaxRowVal = 25;

void pascal_triangle(unique_ptr<uint32_t[]> &arr, int row)
{
	arr.reset(new uint32_t[row]());

	// basis
	arr[0] = 1;

	for (int r = 0; r < row; ++r) {
		uint32_t buf[2] = {[0] = 0, [1] = 0};

		for (int i = 0; i <= r; ++i) {
			buf[0] = buf[1];
			buf[1] = arr[i];
			arr[i] = buf[0] + buf[1];
		}
	}
}

int main()
{
	int nr_tests = 0;

	cin >> nr_tests;
	if (nr_tests < MinNrTest || nr_tests > MaxNrTest) {
		cout << "constraints error: 1 ≤ T ≤ 50\n";
		return 1;
	}

	while (nr_tests--) {
		int row = 0;

		cin >> row;

		if (row < MinRowVal || row > MaxRowVal) {
			cout << "constraints error: 1 ≤ N ≤ 25\n";
			return 1;
		}

		unique_ptr<uint32_t[]> arr;

		pascal_triangle(arr, row);

		int i = 0;
		for (; i < row - 1; ++i) {
			cout << arr[i] << " ";
		}

		cout << arr[i] << endl;
	}

	return 0;
}

