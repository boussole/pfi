/*
   Given a value N, find the number of ways to make change for N cents, if we have infinite supply of each of
   S = { S1, S2, .. , Sm} valued coins. The order of coins doesn’t matter.
   For example, for N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}. So output should be 4.
   For N = 10 and S = {2, 5, 3, 6}, there are five solutions: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}. So the output should be 5.

   Input:
   The first line contains an integer 'T' denoting the total number of test cases.
   In each test cases, the first line contains an integer 'M' denoting the size of array.
   The second line contains M space-separated integers A1, A2, ..., AN denoting the elements of the array.
   The third line contains an integer 'N' denoting the cents.

   Output:
   Print number of possible ways to make change for N cents.

   Constraints:
   1 ≤ T ≤ 50
   1 ≤ N ≤ 300
   1 1 ≤ A[i] ≤ 300

   Example:
      Input:
      2
      3
      1 2 3
      4
      4
      2 5 3 6
      10

      Output:
      4
      5
 */

#include <algorithm>
#include <iostream>
#include <memory>
#include <list>

using namespace std;

struct change {
	uint64_t _total;
	list<pair<int, uint64_t> > _per_coin;
};

// this solution can't be verified at geeksforgeeks because of duplicates in thier test cases, but I think it is correct
// speed O(N*M)
// memory O(N*M)
// @note it is possible to reduce memory complexity, just keep changes in window [n - (`max coin` - `min coin`), n]
uint64_t coin_change_v1(const unique_ptr<uint64_t[]> &coins, int nr_coins, uint64_t n)
{
	unique_ptr<change[]> n_change(new change[n + 1]());

	// from change '1' to 'N'
	for (uint64_t i = 1; i <= n; ++i) {
		// for each coin in coins
		for (uint64_t c = 0; c < nr_coins; ++c) {
			uint64_t coin = coins[c];
			// skip coins that are greater than change
			if (coin > i)
				continue;
			// coins is a full change
			if (i - coin == 0) {
				++n_change[i]._total;
				n_change[i]._per_coin.push_back(make_pair(coin, 1));
			} else {
				uint64_t total = 0;
				for (auto it : n_change[i - coin]._per_coin) {
					if (it.first <= coin && it.second) {
						total += it.second;
						n_change[i]._total += it.second;
					}
				}

				if (total)
					n_change[i]._per_coin.push_back(make_pair(coin, total));
			}
		}
	}

	return n_change[n]._total;
}

// speed O(N*M)
// memory O(N)
uint64_t coin_change_v2(const unique_ptr<uint64_t[]> &coins, int nr_coins, uint64_t n)
{
	unique_ptr<uint64_t[]> change(new uint64_t[n + 1]());

	change[0] = 1;

	for (int i = 0; i < nr_coins; ++i) {
		uint64_t coin = coins[i];
		for (uint64_t ch = 1; ch <= n; ++ch) {
			if (ch >= coin)
				change[ch] += change[ch - coin];
		}
	}

	return change[n];
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while(nr_tests--) {
		int nr_coins;
		cin >> nr_coins;

		unique_ptr<uint64_t[]> coins(new uint64_t[nr_coins]);
		for (uint64_t i = 0; i < nr_coins; ++i)
			cin >> coins[i];

		int n;
		cin >> n;

		cout << coin_change_v1(coins, nr_coins, n) << endl;
		cout << coin_change_v2(coins, nr_coins, n) << endl;
	}

	return 0;
}

