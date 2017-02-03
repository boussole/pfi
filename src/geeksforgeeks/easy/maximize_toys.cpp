/*
   Given an array consisting cost of toys.
   Given an integer K depicting the amount with you.
   Maximise the number of toys you can have with K amount.

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an integer N depicting the number of toys and
   an integer K depicting the value of K.
   Next line is followed by the cost of toys.


   Output:
   Print the maximum toys in separate line.

   Constraints:
   1 ≤ T ≤ 30
   1 ≤ N ≤ 1000
   1 ≤ K ≤ 10000
   1 ≤ A[i] ≤ 10000

   Example:
      Input
      1
      7 50
      1 12 5 111 200 1000 10

      Output
      4

   **For More Examples Use Expected Output**
 */

#include <algorithm>
#include <iostream>
#include <memory>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 30;

static const int MinArrSize = 1;
static const int MaxArrSize = 1000;

static const int MinK = 1;
static const int MaxK = 10000;

static const int MinArrValue = 1;
static const int MaxArrValue = 10000;

// speed  O(NlogN)
// memory O(1)
size_t maximize_toys(unique_ptr<int[]> &toys, int nr_toys, int money)
{
	size_t total = 0;

	sort(toys.get(), toys.get() + nr_toys);

	int toy = 0;
	while (toy < nr_toys && money > toys[toy]) {
		++total;
		money -= toys[toy];
		++toy;
	}

	return total;
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
		int nr_toys;
		cin >> nr_toys;
		if (nr_toys < MinArrSize || nr_toys > MaxArrSize) {
			cerr << "1<=N<=1000\n";
			return 1;
		}

		int k;
		cin >> k;
		if (k < MinK || k > MaxK) {
			cerr << "constraints: 1<=T<=30\n";
			return 1;
		}

		unique_ptr<int[]> toys(new int[nr_toys]);
		for (int i = 0; i < nr_toys; ++i) {
			cin >> toys[i];
			if (toys[i] < MinArrValue || toys[i] > MaxArrValue) {
				cerr << "1 ≤ A[i] ≤ 10000\n";
				return 1;
			}
		}

		cout << maximize_toys(toys, nr_toys, k) << endl;
	}

	return 0;
}

