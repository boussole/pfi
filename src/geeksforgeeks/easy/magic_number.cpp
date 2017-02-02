/*
   A magic number is defined as a number which can be expressed as a power of 5
   or sum of unique powers of 5.
   First few magic numbers are 5, 25, 30(5 + 25), 125, 130(125 + 5), ...

   Given the value of n. find the nth Magic number.
   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an integer N depicting the value of N.

   Output:
   Print the nth magic number in a separate line.

   Constraints:
   1 ≤ T ≤ 30
   1 ≤ N ≤ 100

   Example:
   Input:
      2
      1
      2
   Output:
      5
      25

   **For More Examples Use Expected Output**
 */

#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 50;

static const uint64_t MinValue = 1;
static const uint64_t MaxValue = 100;

// speed O(2^LogN) ???
// memory O(2^LogN^2) ???
uint64_t nth_magic_number_v1(int nth)
{
	unique_ptr<uint64_t[]> magic(new uint64_t[nth]);

	int power_of_5 = 0;
	int i = 0;
	magic[0] = 1;
	while (i < nth) {
		magic[i] = magic[power_of_5] * 5;
		power_of_5 = i++;

		for (int j = 0; (j < power_of_5) && (i < nth); ++j)
			magic[i++] = magic[power_of_5] + magic[j];
	}

	return magic[nth - 1];
}

// speed O(N)
// memory O(N)
//
// each magic number is: ['1' or '0'] * 5 ^ N + ['1' or '0'] * 5 ^ (N - 1) ... + ['1' or '0'] * 5 ^ 1
// where factor [1 or 0] corresponds to bit value in binary representation of nth
// i.e.
// if nth(dec) == 3  then nth(bin) = 11   => so '1' * 5 ^ 2 + '1' * 5 ^ 1 = 30
// if nth(dec) == 10 then nth(bin) = 1010 => so '1' * 5 ^ 4 + '0' * 5 ^ 3 + '1' * 5 ^ 2 + '0' * 5 ^ 1 = 650
// ...
uint64_t nth_magic_number_v2(int nth)
{
	uint64_t magic = 0;
	uint64_t power_of_5 = 5;

	while (nth > 0) {
		if (nth & 1)
			 magic += power_of_5;

		power_of_5 *= 5;
		nth >>= 1;
	}

	return magic;
}

int main()
{
	int nr_tests;

	cin >> nr_tests;
	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints: 1 ≤ T ≤ 30\n";
		return 1;
	}

	while (nr_tests--) {
		int n_th;
		cin >> n_th;
		if (n_th < MinValue || n_th > MaxValue) {
			cerr << "constraints: 1 ≤ N ≤ 100\n";
			return 1;
		}

		uint64_t ans_1 = nth_magic_number_v1(n_th), ans_2 = nth_magic_number_v2(n_th);
		assert(ans_1 == ans_2);
		cout << ans_1 << endl;
	}

	return 0;
}
