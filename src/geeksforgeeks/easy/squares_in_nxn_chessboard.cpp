/*
   Find total number of Squares in a N*N cheesboard.

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an integer N that is the side of the chessboard.

   Output:
   Each seperate line showing the maximum number of squares possible.

   Constraints:
   1 ≤ T ≤ 100
   1 ≤ N ≤ 100

   Example:
   Input:
   2
   1
   2

   Output:
   1
   5

   **For More Examples Use Expected Output**
 */

#include <iostream>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 100;

static const int MinBoardDimension = 1;
static const int MaxBoardDimension = 100;


// `sum of the squares of the first n natural numbers using summation`:
// n^3 / 3  + n^2 / 2 + n / 6 =
// (2 * n^3 + 3 * n^2 + n) / 6 =
// n * (n + 1) * (2 * n + 1) / 6
// speed O(log(N^3))
// memory O(1)
// \todo simplify formula to prevent overflow
uint64_t squares_in_nxn_chessboard(uint64_t n)
{
	return (n * (n + 1) * (2 * n + 1)) / 6;
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
		int n = 0;
		cin >> n;

		if (n < MinBoardDimension || n > MaxBoardDimension) {
			cerr << "constraints: 1 ≤ N ≤ 10000\n";
			return 1;
		}

		cerr << "N = " << n << endl;
		cout << squares_in_nxn_chessboard(static_cast<uint64_t>(n)) << endl;
	}

	return 0;
}

