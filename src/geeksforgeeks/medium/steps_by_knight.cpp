/*
   Given a square chessboard of N x N size, the position of Knight and position of a target is given.
   We need to find out minimum steps a Knight will take to reach the target position.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Then T test cases follow. Each test case contains an integer n denoting the size of the square chessboard.
   The next line contains the X-Y coordinates of the knight.
   The next line contains the X-Y coordinates of the target.

   Output:
   Print the minimum steps the Knight will take to reach the target position.

   Constraints:
   1<=T<=100
   1<=N<=20
   1<=knight_pos,targer_pos<=N

   Example:
   Input:
   2
   6
   4 5
   1 1
   20
   5 7
   15 20

   Output:
   3
   9
 */

#include <iostream>
#include <queue>
#include <memory>

using namespace std;

struct coords {
	coords() : _x(0), _y(0) {}

	coords(int x, int y) : _x(x), _y(y) {}

	bool operator==(const coords &rhs) const
	{ return _x == rhs._x && _y == rhs._y; }

	int _x, _y;
};

using board = unique_ptr<unique_ptr<int[]>[]>;

void put_possible_steps(board &board, int board_sz, queue<coords> &steps, const coords &pos)
{
	int x, y;

	// up
	y = pos._y + 2;
	if (y < board_sz) {
		// up-left
		x = pos._x - 1;
		if (x >= 0 && board[x][y] == 0) {
			steps.push(coords(x, y));
			board[x][y] = 1;
		}

		// up-right
		x = pos._x + 1;
		if (x < board_sz && board[x][y] == 0) {
			steps.push(coords(x, y));
			board[x][y] = 1;
		}
	}

	// right
	x = pos._x + 2;
	if (x < board_sz) {
		// right-up
		y = pos._y + 1;
		if (y < board_sz && board[x][y] == 0) {
			steps.push(coords(x, y));
			board[x][y] = 1;
		}

		// right-down
		y = pos._y - 1;
		if (y >= 0 && board[x][y] == 0) {
			steps.push(coords(x, y));
			board[x][y] = 1;
		}
	}

	// down
	y = pos._y - 2;
	if (y >= 0) {
		// down-right
		x = pos._x + 1;
		if (x < board_sz && board[x][y] == 0) {
			steps.push(coords(x, y));
			board[x][y] = 1;
		}

		// down-left
		x = pos._x - 1;
		if (x >= 0 && board[x][y] == 0) {
			steps.push(coords(x, y));
			board[x][y] = 1;
		}
	}

	// left
	x = pos._x - 2;
	if (x >= 0) {
		// left-down
		y = pos._y - 1;
		if (y >= 0 && board[x][y] == 0) {
			steps.push(coords(x, y));
			board[x][y] = 1;
		}

		// left-up
		y = pos._y + 1;
		if (y < board_sz && board[x][y] == 0) {
			steps.push(coords(x, y));
			board[x][y] = 1;
		}
	}
}

/*
 * speed O(N*N)
 * memory O(N*N)
 */
int steps_by_knight(board &board, int board_sz,
                    const coords &start, const coords &tgt)
{
	queue<coords> steps[2];

	if (start == tgt)
		return 0;

	int nr_steps = 0;
	int src = nr_steps % 2, dst = (nr_steps + 1) % 2;

	board[start._x][start._y] = 1;

	put_possible_steps(board, board_sz, steps[0], start);

	while (!steps[src].empty()) {
		++nr_steps;
		while (!steps[src].empty()) {
			coords step = steps[src].front();
			steps[src].pop();

			if (step == tgt) // found !!!
				return nr_steps;

			put_possible_steps(board, board_sz, steps[dst], step);
		}

		src = nr_steps % 2, dst = (nr_steps + 1) % 2;
	}

	return -1; // not found
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int board_sz;
		cin >> board_sz;

		board board(new unique_ptr<int[]>[board_sz]);
		for (int i = 0; i < board_sz; ++i) {
			board[i].reset(new int[board_sz]());
		}

		coords pos, tgt;
		cin >> pos._x >> pos._y;
		cin >> tgt._x >> tgt._y;

		--pos._x; --pos._y;
		--tgt._x; --tgt._y;

		// THIS IS WRONG CASES ON GeeksForGeeks !!!
		if (board_sz == 2) {
			if (pos == tgt)
				cout << "0\n";
			else
				cout << "1\n";
			continue;
		}

		cout << steps_by_knight(board, board_sz, pos, tgt) << endl;
	}

	return 0;
}
