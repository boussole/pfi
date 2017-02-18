/*
   Given a value N, if we want to make change for N Rs, and we have infinite supply of each of the denominations in Indian currency, i.e.,
   we have infinite supply of { 1, 2, 5, 10, 20, 50, 100, 500, 1000} valued coins/notes,
   Find the minimum number of coins and/or notes needed to make the change.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Each test case consist of an Integer value N denoting the amount to get change for.

   Output:
   Print all the possible denominations needed to make the change in a separate line.

   Constraints:
   1 ≤ T ≤ 30
   1 ≤ N ≤ 2000

   Example:
      Input
      1
      43
      Output
      20 20 2 1
 */

#include <assert.h>

#include <iostream>
#include <memory>

#ifndef ARRAYSIZE
#	define ARRAYSIZE(a) (sizeof(a) / sizeof(*(a)))
#endif /* ARRAYSIZE*/

using namespace std;

int coins[] = { 1, 2, 5, 10, 20, 50, 100, 500, 1000 };

struct change_item {
	change_item(int nr_coins = 0, int chosen_coin = 0) :
		_nr_coins(nr_coins),
		_chosen_coin(chosen_coin)
	{}

	int _nr_coins;
	int _chosen_coin;
};

// DP
// speed  O(N)
// memory O(N)
//
// in terms of input data size = logN
// speed O(logN^logN)
// memory O(exp)
int min_number_of_coins_dp(unique_ptr<int[]> &change, int amount)
{
	/* { nr_coins, choosen coin } */
	unique_ptr<change_item[]> full_change(new change_item[amount + 1]);

	full_change[0] = { 0, 0 };

	for (int i = 1; i < amount + 1; ++i) {

		change_item cand(amount + 1, -1); /*< impossible values*/
		for (int j = 0; j < ARRAYSIZE(coins) && coins[j] <= i; ++j) {
			int nr_coins = 1 + full_change[i - coins[j]]._nr_coins;
			if (nr_coins < cand._nr_coins) {
				cand = change_item(nr_coins, coins[j]);
			}
		}

		full_change[i] = cand;
	}

	int nr_coins = full_change[amount]._nr_coins, nr_steps = nr_coins;
	change.reset(new int[nr_coins]);

	int insert_pos = nr_coins - 1;
	while (nr_steps--) {
		change[insert_pos--] = full_change[amount]._chosen_coin;
		amount -= full_change[amount]._chosen_coin;
	}

	return nr_coins;
}

// Gready
// speed  O(N)
// memory O(N)
//
// in terms of input data size = logN
// speed O(exp^exp)
// memory O(exp)
int min_number_of_coins_gready(unique_ptr<int[]> &change, int amount)
{
	// { 1, 2, 5, 10, 20, 50, 100, 500, 1000 };

	unique_ptr<int[]> coin_index(new int[amount]); // the worst case, when change is a sum of `1`

	int c = ARRAYSIZE(coins) - 1;
	int nr_coins = 0;
	while (amount != 0) {
		if (c < 0) {
			assert(nr_coins > 0);
			amount += change[coin_index[--nr_coins]];
			c = coin_index[nr_coins] - 1;
		}

		while (amount - coins[c] >= 0) {
			amount -= coins[c];
			coin_index[nr_coins++] = c;
		}

		--c;
	}

	change.reset(new int[nr_coins]);
	for (int i = 0; i < nr_coins; ++i)
		change[i] = coins[coin_index[i]];

	return nr_coins;
}

int main()
{
	int nr_tests = 0;
	cin >> nr_tests;

	while (nr_tests--) {
		int amount;
		cin >> amount;

		unique_ptr<int[]> change_gready, change_dp;
		int nr_coins_gready = min_number_of_coins_gready(change_gready, amount), nr_coins_dp = min_number_of_coins_dp(change_dp, amount);
		assert(nr_coins_gready == nr_coins_dp);
		assert(nr_coins_dp > 0);

		int i;
		for (i = 0; i < nr_coins_dp - 1; ++i) {
			assert(change_dp[i] == change_gready[i]);
			cout << change_dp[i] << " ";
		}

		assert(change_dp[i] == change_gready[i]);
		cout << change_dp[i] << endl;
	}

	return 0;
}

