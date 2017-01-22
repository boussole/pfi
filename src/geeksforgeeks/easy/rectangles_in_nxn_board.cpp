/*
   Find total number of Rectangles (excluding squares) in a N*N cheesboard.

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an integer N that is the side of the chessboard.

   Output:
   Each seperate line showing the maximum number of rectangles possible.

   Constraints:
   1 ≤ T ≤ 1000
   1 ≤ N ≤ 10000

   Example:
      Input:
      2
      1
      2

      Output:
      0
      4

   Explanation :
   For n=1 there is only one square possible and no rectangles so answer will be 0.
   For n=2 there will be 2 rectangles of dimension 1*2 and 2 rectangles of dimension 2*1. So answer if 4.

   **For More Examples Use Expected Output**
 */

#include <assert.h>

#include <iostream>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 1000;

static const int MinBoardDimension = 1;
static const int MaxBoardDimension = 10000;

// speed O(N)
// memory O(1)
uint64_t rectangles_in_nxn_board_v1(uint64_t n)
{
	uint64_t nr_rects = 0;

	uint64_t nr_rows = 1;
	uint64_t nr_cols = 2;
	for (int i = 0; i < n - 1; ++i) {
		uint64_t nr_row_steps = n - nr_rows + 1;
		uint64_t nr_col_steps = n - nr_cols + 1;
		uint64_t min_nr_rect_in_row = 1;
		uint64_t max_nr_rect_in_row = n - nr_cols + 1;

		/* arithmetic progression */
		uint64_t nr_rects_in_row = ((min_nr_rect_in_row + max_nr_rect_in_row) * nr_col_steps) / 2;
		nr_rects += nr_row_steps * nr_rects_in_row;
		++nr_rows;
		++nr_cols;
	}

	return nr_rects * 2 /* mirrors */;
}

// speed O(LogN^3)
// memory O(1)
// total number of shapes: 1 shape = 2 horizonntal points + 2 vertical points
// number of horizontal points: n + 1
// number of vertical points: n + 1
//                         | n + 1 |   | n + 1 |
// total number of shapes: |   2   | * |   2   | =
//
// ((n + 1)! / (2 * (n + 1 - 2)!)) * ((n + 1)! / (2 * (n + 1 - 2)!)) = (n * (n + 1) * n * (n + 1)) / 4
//
// total number of squares for square N x N: 1^2 + 2^2 + 3^2 + ... + N^2 = n * (n + 1) * (2 * n + 1) / 6
uint64_t rectangles_in_nxn_board_v2(uint64_t n)
{
	uint64_t nr_shapes = (n * (n + 1) * n * (n + 1)) / 4;

	uint64_t nr_squares = n * (n + 1) * (2 * n + 1) / 6;

	return nr_shapes - nr_squares;
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
		uint64_t ans_1 = rectangles_in_nxn_board_v1(static_cast<uint64_t>(n)), ans_2 = rectangles_in_nxn_board_v2(static_cast<uint64_t>(n));
		assert(ans_1 == ans_2);
		cout << ans_1 << endl;
	}

	return 0;
}

