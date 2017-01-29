/*
   You have to merge the two sorted arrays into one sorted array (in non-increasing order)

   Input:
   First line contains an integer T, denoting the number of test cases.
   First line of each test case contains two space separated integers X and Y, denoting the size of the two sorted arrays.
   Second line of each test case contains X space separated integers, denoting the first sorted array P.
   Third line of each test case contains Y space separated integers, denoting the second array Q.

   Output:
   For each test case, print (X + Y) space separated integer representing the merged array.

   Constraints:
   1 <= T <= 100
   1 <= X, Y <= 5 * 10 ^ 4
   0 <= P[i], Q[i] <= 10 ^ 9

   Example:
      INPUT:
      1
      4 5
      7 5 3 1
      9 8 6 2 0

      OUTPUT:
      9 8 7 6 5 3 2 1 0

   **For More Examples Use Expected Output**
 */

#include <assert.h>

#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

template <int base, int power>
struct Power {
	enum : uint64_t { value = base * Power<base, power - 1> :: value };
};

template <int base>
struct Power<base, 0> {
	enum : uint64_t { value = 1 };
};

static const int MinNrTest = 1;
static const int MaxNrTest = 100;

static const int MinArrSize = 1;
static const int MaxArrSize = 5 * Power<10, 4> :: value;

static const int MinValue = 0;
static const int MaxValue = Power<10, 9> :: value;

// speed O(N + M)
// memory O(N + M)
void merge_two_sorted_arrays_v1(unique_ptr<int[]> &arr_1, int arr_1_sz, unique_ptr<int[]> &arr_2, int arr_2_sz)
{
	int merged_sz = arr_1_sz + arr_2_sz;
	int pos_1 = 0, pos_2 = 0, merged_pos = 0;

	unique_ptr<int[]> merged_arr(new int[merged_sz]);

	while (pos_1 < arr_1_sz && pos_2 < arr_2_sz) {
		if (arr_1[pos_1] > arr_2[pos_2])
			merged_arr[merged_pos++] = arr_1[pos_1++];
		else
			merged_arr[merged_pos++] = arr_2[pos_2++];
	}

	// residue 1
	while (pos_1 < arr_1_sz)
		merged_arr[merged_pos++] = arr_1[pos_1++];

	// residue 2
	while (pos_2 < arr_2_sz)
		merged_arr[merged_pos++] = arr_2[pos_2++];

	memcpy(arr_1.get(), merged_arr.get(), sizeof(int) * arr_1_sz);
	memcpy(arr_2.get(), merged_arr.get() + arr_1_sz, sizeof(int) * arr_2_sz);
}

// speed O(N * M)
// memory O(1)
//
// Algorithm notes
// 1) at the end the first array must contain the biggest numbers of both arrays in a descending order
// 2) invariant: the order of both arrays must not be violated in each iteration
void merge_two_sorted_arrays_v2(unique_ptr<int[]> &arr_1, int arr_1_sz, unique_ptr<int[]> &arr_2, int arr_2_sz)
{
	// O(N)
	for (int pos_1 = 0; pos_1 < arr_1_sz; ++pos_1) {
		if (arr_1[pos_1] >= arr_2[0])
			continue;
	
		swap(arr_1[pos_1], arr_2[0]);

		// O(M)
		for (int pos_2 = 0; (pos_2 < arr_2_sz - 1) && (arr_2[pos_2] < arr_2[pos_2 + 1]); ++pos_2)
			swap(arr_2[pos_2], arr_2[pos_2 + 1]);
	}
}

int main()
{
	int nr_tests;

	cin >> nr_tests;
	if (nr_tests < MinNrTest || nr_tests > MaxNrTest) {
		cerr << "constraints error: 1 ≤ T ≤ 30\n";
		return 1;
	}

	while (nr_tests--) {
		int arr_1_sz, arr_2_sz;
		cin >> arr_1_sz;
		cin >> arr_2_sz;
		if (arr_1_sz < MinArrSize || arr_1_sz > MaxArrSize || arr_2_sz < MinArrSize || arr_2_sz > MaxArrSize) {
			cerr << "constraints error: 1 <= N <= 1000\n";
			return 1;
		}

		unique_ptr<int[]> arr_1(new int[arr_1_sz]), arr_1_dup(new int[arr_1_sz]);
		for (int i = 0; i < arr_1_sz; ++i) {
			cin >> arr_1[i];
			arr_1_dup[i] = arr_1[i];
			if (arr_1[i] < MinValue || arr_1[i] > MaxValue) {
				cerr << "constraints error: 0 <= arr[i] <= 10 ^ 9\n";
				return 1;
			}
		}

		unique_ptr<int[]> arr_2(new int[arr_2_sz]), arr_2_dup(new int[arr_2_sz]);
		for (int i = 0; i < arr_2_sz; ++i) {
			cin >> arr_2[i];
			arr_2_dup[i] = arr_2[i];
			if (arr_2[i] < MinValue || arr_2[i] > MaxValue) {
				cerr << "constraints error: 0 <= arr[i] <= 10 ^ 9\n";
				return 1;
			}
		}

		merge_two_sorted_arrays_v1(arr_1, arr_1_sz, arr_2, arr_2_sz);
		merge_two_sorted_arrays_v2(arr_1_dup, arr_1_sz, arr_2_dup, arr_2_sz);

		for (int i = 0; i < arr_1_sz; ++i) {
			cout << arr_1[i] << " ";
			assert(arr_1[i] == arr_1_dup[i]);
		}

		int i = 0;
		for (; i < arr_2_sz - 1; ++i){
			cout << arr_2[i] << " ";
			assert(arr_2[i] == arr_2_dup[i]);
		}
		cout << arr_2[i] <<  endl;
	}

	return 0;
}

