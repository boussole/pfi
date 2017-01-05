/*

   Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an integer N depicting the size of array and next line followed by the value of array.

   Output:
   Print the maximum gap between the successive elements.


   Constraints:
   1 ≤ T ≤ 30
   1 ≤ N ≤ 1000
   1 ≤ A[i] ≤ 1000


   Example:
      Input
      1
      3
      1 10 5
      Output
      5
   **For More Examples Use Expected Output**

   http://www.practice.geeksforgeeks.org/problem-page.php?pid=130
 */

#include <assert.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

using namespace std;

static const int MinNrTest = 1;
static const int MaxNrTest = 30;

static const int MinArraySz = 1;
static const int MaxArraySz = 1000;

static const int MinArrayValue = 1;
static const int MaxArrayValue = 1000;

/* speed O(N)
   memory O(MaxArrayValue - MinArrayValue + 1)
 */
int maximum_gap_v1(unique_ptr<int[]> &arr, int sz)
{
	switch (sz) {
		case 0:
		case 1: return 0;
		case 2: return abs(arr[0] - arr[1]);
		default: break;
	}

	int counting_sz = MaxArrayValue - MinArrayValue + 1;
	unique_ptr<int[]> counting(new int[counting_sz]());

	int min = numeric_limits<int> :: max();
	// O(N)
	for (int i = 0; i < sz; ++i) {
		if (arr[i] < min)
			min = arr[i];
		++counting[arr[i]];
	}

	int max_gap = numeric_limits<int> :: min(), val = min;
	int i = min + 1;
	while (i < counting_sz) {
		if (counting[i]) {
			int candidate = i - val;
			if (candidate > max_gap)
				max_gap = candidate;

			val = i;
		}

		++i;
	}

	return max_gap;
}

/* speed O(N)
   memory O(<<<< N)

   this is not my solution, this algorithm I found here:
   http://cgm.cs.mcgill.ca/~godfried/teaching/dm-reading-assignments/Maximum-Gap-Problem.pdf
 */
int maximum_gap_v2(unique_ptr<int[]> &arr, int sz)
{
	int max_gap = 0;

	switch (sz) {
		case 0:
		case 1: return 0;
		case 2: return abs(arr[0] - arr[1]);
		default: break;
	}

	// find min, max values => O(N)
	int min = arr[0], max = arr[0];
	for_each(arr.get(), arr.get() + sz, [&min, &max](int val) {
		if (val < min)
			min = val;
		else if (val > max)
			max = val;
	});

	struct bucket {
		// small optimization: don't save each element in buckets, just save min and max element of each bucket
		void put(int val) {
			if (!_init) {
				_min = _max = val;
				_init = true;
			} else {
				if (val < _min)
					_min = val;
				else if (val > _max)
					_max = val;
			}
		}

		int _min, _max;
		bool _init;
	};

	const int nr_buckets = sz - 1;
	vector<bucket> v(nr_buckets);

	// put sz - 2 element (without min and max) in a buckets [0, sz - 1] => O(N)
	for_each(arr.get(), arr.get() + sz, [&](int val) {
		/* NOTE: it is possible to use FPU here
		   double interval = static_cast<double>((max - min)) / nr_buckets;
		   int bucket_num = floor((val - min) / interval); */

		if (val != max && val != min) {
			int bucket_num = ((val - min) * nr_buckets) / (max - min);
			v[bucket_num].put(val);
		}
	});

	// find maximum gap => O(N)
	max_gap = numeric_limits<int> :: min();
	int prev_max = min;
	for (size_t i = 0; i < v.size(); ++i) {
		if (v[i]._init) {
			int candidate = v[i]._min - prev_max;
			if (candidate > max_gap)
				max_gap = candidate;

			prev_max = v[i]._max;
		}
	}

	int candidate = max - prev_max;
	if (candidate > max_gap)
		max_gap = candidate;

	return max_gap;
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
		int arr_sz = 0;
		cin >> arr_sz;
		if (arr_sz < MinArraySz || arr_sz > MaxArraySz) {
			cerr << "constraints error: 1 ≤ N ≤ 1000\n";
			return 1;
		}

		unique_ptr<int[]> arr(new int[arr_sz]());
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
			if (arr[i] < MinArrayValue || arr[i] > MaxArrayValue) {
				cerr << "constraints error: 1 ≤ A[i] ≤ 1000\n";
				return 1;
			}
		}

		int res1 = maximum_gap_v1(arr, arr_sz);
		int res2 = maximum_gap_v2(arr, arr_sz);
		cout << res1 << " " << res2 << endl;
		assert(res1 == res2);

		cout << res1 << endl;
	}

	return 0;
}

