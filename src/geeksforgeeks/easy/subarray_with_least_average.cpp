/*
   Find the subarray with least average of size K.
   Given an array arr[] of size n and integer k such that k <= n.

   Input:
   The first line contains an integer 'T' denoting the total number of test cases.
   In each test cases, the first line contains an integer 'N' and 'K' denoting the size of array.
   The second line contains N space-separated integers A1, A2, ..., AN denoting the elements of the array.

   Output:
   The first and last index of the subarray. (Index begins from 1).

   Constraints:
   1<=T<=30
   1<=N<=1000
   1<=K<=N
   1<=A[i]<=10^3

   Example:
      Input:
      1
      3 1
      30 20 10

      Output:
      3 3

      **For More Examples Use Expected Output**
 */

#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 30;

static const int MinArrSize = 1;
static const int MaxArrSize = 1000;

static const int MinSubArrSize = 1;

static const int MinArrValue = /*1*/-103;
static const int MaxArrValue = 10 * 10 * 10;

// speed O(N)
// memory O(1)
// subarr_coords contains the first and the last index of subarray, where array starts with `1`
void subarray_with_least_average(const unique_ptr<int[]> &arr, int arr_sz, int subarr_sz, pair<int, int> &subarr_coords)
{
	assert(subarr_sz < arr_sz);

	int total_sum = 0;
	int i = 0;
	for (; i < subarr_sz; ++i)
		total_sum += arr[i];

	subarr_coords.first = 0;
	subarr_coords.second = i - 1;
	int new_sum = total_sum;

	for (; i < arr_sz; ++i) {
		new_sum = new_sum - arr[i - subarr_sz] + arr[i];
		if (new_sum < total_sum) {
			total_sum = new_sum;
			subarr_coords.first = i - subarr_sz + 1;
			subarr_coords.second = i;
		}
	}

	// normalize to task requirements
	++subarr_coords.first;
	++subarr_coords.second;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;
	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints: 1<=T<=30\n";
		return 1;
	}

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;
		if (arr_sz < MinArrSize || arr_sz > MaxArrSize) {
			cerr << "1<=N<=1000\n";
			return 1;
		}

		cerr << "arr_sz = " << arr_sz;

		int subarr_sz;
		cin >> subarr_sz;
		if (subarr_sz < MinSubArrSize || subarr_sz > arr_sz) {
			cerr << "1<=K<=N\n";
			return 1;
		}

		cerr << " subarr_sz = " << subarr_sz << endl;

		cerr << "array [";
		unique_ptr<int[]> arr(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
			if (arr[i] < MinArrValue || arr[i] > MaxArrValue) {
				cerr << "1<=A[i]<=10^3\n";
				return 1;
			}

			cerr << " " << arr[i];
		}

		cerr << " ]\n";

		pair<int, int> subarr_coords;

		subarray_with_least_average(arr, arr_sz, subarr_sz, subarr_coords);

		cout << subarr_coords.first << " " << subarr_coords.second << endl;
	}

	return 0;
}


