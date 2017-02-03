/*
   Given a binary array and an integer m, find the maximum number of consecutive 1's produced by flipping 0's.
   You can flip maximum m zeroes.

   Input:
   The first line contains an integer 'T' denoting the total number of test cases.
   In each test cases, the first line contains an integer 'N' denoting the size of array.
   The second line contains N space-separated integers A1, A2, ..., AN denoting the elements of the array.
   Third line consists of an integer m that is maximum number of flips allowed.


   Output:
   Output the maximum numbers of consecutive 1's. (Indices begin from 0).

   Constraints:
   1<=T<=31
   1<=N<=100
   1<=m<=N

   Example:
      Input:
      1
      11
      1 0 0 1 1 0 1 0 1 1 1
      2

      Output:
      8

   Explaination:

   Input:   arr[] = {1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1}
            m = 2
   Output:  8

   We are allowed to flip maximum 2 zeroes. If we flip arr[5] and arr[7], we get 8 consecutive 1's which is maximum possible under given constraints

   **For More Examples Use Expected Output**
*/

#include <assert.h>

#include <memory>
#include <iostream>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 31;

static const int MinArrSize = 1;
static const int MaxArrSize = 100;

static const int MinNrFlips = 0;

// speed O(N)
// memory O(1)
int maximize_number_of_1(unique_ptr<int[]> &arr, int arr_sz, int nr_flips)
{
	int max_nr_of_1 = 0, nr_of_1 = 0;
	int seq_start = 0;

	for (int i = 0; i < arr_sz; ++i) {
		if (arr[i]) {
			++nr_of_1;
		} else if (nr_flips) {
			--nr_flips;
			++nr_of_1;
		} else {
			while (seq_start < i) {
				if (!arr[seq_start++])
					break;

				--nr_of_1;
			}

			assert(nr_of_1 >= 0);
		}

		if (nr_of_1 > max_nr_of_1)
			max_nr_of_1 = nr_of_1;
	}

	return max_nr_of_1;
}

int main()
{
	int nr_tests = 0;
	cin >> nr_tests;

	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints: 1 ≤ T ≤ 1000\n";
		return 1;
	}

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;
		if (arr_sz < MinArrSize || arr_sz > MaxArrSize) {
			cerr << "1<=N<=1000\n";
			return 1;
		}

		unique_ptr<int[]> arr(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
			if (arr[i] != 0 && arr[i] != 1) {
				cerr << "0 <= A[i] ≤ 1\n";
				return 1;
			}
		}

		int nr_flips;
		cin >> nr_flips;
		if (nr_flips < MinNrFlips || nr_flips > arr_sz) {
			cerr << "constraints: 1<=T<=" << arr_sz << endl;
			return 1;
		}

		cout << maximize_number_of_1(arr, arr_sz, nr_flips) << endl;
	}

	return 0;
}
