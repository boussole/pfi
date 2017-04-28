/*
   Given two integers ‘n’ and ‘sum’, find count of all n digit numbers with sum of digits as ‘sum’.
   Leading 0’s are not counted as digits. Print your output % 10^9+7.

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains 2 integers n and sum.

   Output:
   Print the number of digits. Print -1 if answer is not possible.

   Constraints:
   1<=T<=30
   1<=n<=100
   1<=sum<=1000

   Example:
      Input:
      1
      2 2
      Output:
      2
      Explaination:  2 numbers 11 and 20.
 */

#include <assert.h>

#include <iostream>
#include <vector>

using namespace std;

static const int modulo = (1000000000 + 7);

void add_modulo(int64_t &nr_digits, int value = 1)
{
	nr_digits += value;

	while (nr_digits > modulo)
		nr_digits %= modulo;
}

// speed O(N^N) - exp
// memory O(N)
void count_of_n_digit_numbers_whose_sum_of_digits_equals_to_given_sum_v1(int nr_digits, int sum, int64_t &res, int start = 0)
{
	if (nr_digits * 9 < sum)
		return;

	if (nr_digits == 0) {
		if (sum == 0)
			add_modulo(res);

		return;
	}

	for (int i = start; i <= 9; ++i) {
		int down_sum = sum - i;
		if (down_sum < 0)
			break;

		count_of_n_digit_numbers_whose_sum_of_digits_equals_to_given_sum_v1(nr_digits - 1, down_sum, res);
	}
}

// N - nr digits, S - sum
// speed O(N * (S * (S + 1) / 2))- poli
// memory O(sum * nr_digits)
void count_of_n_digit_numbers_whose_sum_of_digits_equals_to_given_sum_v2(int nr_digits, int sum, int64_t &res)
{
	assert(nr_digits != 0 && sum != 0);

	/* this is table i - number of digits, j - sum,
	   where [n, s] = <total number of cases to make sum `s` using `n` digits>
	 */
	vector<vector<int64_t> > memoization(nr_digits);

	int sum_sz = min(sum, 9) + 1;

	// basic: using 1 digit it's possible to make sum [0 - 9] only one way using 1 digit
	memoization[0].resize(sum + 1, 0);
	for (int i = 0; i < sum_sz; ++i)
		memoization[0][i] = 1;

	// fill rows table from '0' excepting highest level
	for (int i = 1; i < nr_digits - 1; ++i) {
		memoization[i].resize(sum + 1, 0);
		for (int s = 0; s <= sum; ++s) {
			for (int j = 0; j <= 9 && j <= s; ++j) {
				add_modulo(memoization[i][s], memoization[i - 1][s - j]);
			}
		}
	}

	// last past excluding leading zero
	const int last_row = nr_digits - 1;
	if (last_row == 0) {
		res = sum == 0 ? 0 : memoization[0][sum];
		return;
	}

	memoization[last_row].resize(sum + 1, 0);
	for (int s = 0; s <= sum; ++s) {
		for (int j = 1; j <= 9 && j <= s; ++j) {
			add_modulo(memoization[last_row][s], memoization[last_row - 1][s - j]);
		}
	}

	res = memoization[nr_digits - 1][sum];
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int nr_digits, sum;
		cin >> nr_digits >> sum;

		int64_t res = 0;
		// to long for big numbers
		// count_of_n_digit_numbers_whose_sum_of_digits_equals_to_given_sum(nr_digits, sum, res, 1);

		count_of_n_digit_numbers_whose_sum_of_digits_equals_to_given_sum_v2(nr_digits, sum, res);

		cout << (res == 0 ? -1 : res) << endl;
	}

	return 0;
}

