/*
 * \file    puzzle.cpp
 * \brief  
 * \details
 * \author  boussole
 */

#include "puzzle.h"
#include <math.h>
#include <common/chess_board.h>

namespace conq_puzzle {

std::ostream &operator << (std::ostream &o, const TriangleType &type)
{
	static const char * name[] = {
		/*[TriangleType :: Equilateral] = */"equilateral",
		/*[TriangleType :: Isosceles] = */"isosceles",
		/*[TriangleType :: Isosceles] = */"basic",
		/*[TriangleType :: Impossible] = */"impossible",
	};

	o << name[static_cast<std :: size_t>(type)];

	return o;
}

/**
 * \brief Identify triangle type by egdes
 */
TriangleType triangleType(double a, double b, double c)
{
	if (a == b && b == c)
		return TriangleType :: Equilateral;

	if ((a < b + c) && (a > fabs(b - c)) &&
	    (b < a + c) && (b > fabs(a - c)) &&
	    (c < a + b) && (c > fabs(a - b))) {
		if (a == b || b == c || a == c)
			return TriangleType :: Isosceles;
		return TriangleType :: Basic;
	}

	return TriangleType :: Impossible;
}

/**
 * \brief Queen problem
 * \note  Actual for board size > 4
 */
void queenProblem(int boardSize)
{
	assert(boardSize >= 4);

	conq_common :: ChessBoard b(static_cast<std :: size_t>(boardSize));

	std :: unique_ptr<int[]> position(new int[boardSize]);

	int position_num = 0;

	std :: function<bool(int, int)> is_safe_position = [&](int row, int col)->bool {
		int offset = 1;
		while (--row >= 0) {
			int diag1 = col + offset, diag2 = col - offset;
			if ((position[row] == col) || (position[row] == diag1) || (position[row] == diag2))
				return false;
			++offset;
		}

		return true;
	};

	std :: function<void(int)> bt = [&](int row) {
		if (row < boardSize) {
			for (int col = 0; col < boardSize; ++col) {
				if (is_safe_position(row, col)) {
					position[row] = col;
					b.add('a' + col, row + 1, conq_common :: ChessBoard :: ChessMan :: Queen_W);
					bt(row + 1);
					b.add('a' + col, row + 1, conq_common :: ChessBoard :: ChessMan :: Empty);
				}
			}
		}
		else
			std :: cout << ++position_num << ".\n" << b.show() << std :: endl;
	};

	bt(0);
}

/**
 * \brief Sentence with numbers problem
 */
void sentenceWithNumbersProblem()
{
	#define NUMBER_MAX 10

	std :: array<int, NUMBER_MAX> numbers_tbl;
	numbers_tbl.fill(1);

	std :: string sentence;
	auto build_sentence_fn = [&]() {
		sentence.clear();
		for (int i = 0; i < NUMBER_MAX; ++i)
			sentence += std :: to_string(numbers_tbl[i]) + " " + std :: to_string(i) + "\n";
	};

	auto is_logicaly_true = [&]()->bool {
		std :: array<int, NUMBER_MAX> tbl;
		tbl.fill(1);
		for (int i = 0; i < NUMBER_MAX; ++i)
			++tbl[numbers_tbl[i]];
		return (numbers_tbl == tbl);
	};

	while (numbers_tbl[NUMBER_MAX] != NUMBER_MAX) {
		for (int i = 1; i < NUMBER_MAX - 1; ++i) {
			if (is_logicaly_true()) {
				build_sentence_fn();
				std :: cout << "sentence\n" << sentence << std :: endl;
				return;
			}
			++numbers_tbl[1];
		}

		++numbers_tbl[1];
		for (int i = 0; i < NUMBER_MAX - 1; ++i) {
			if (numbers_tbl[i] == NUMBER_MAX) {
				numbers_tbl[i] = 1;
				++numbers_tbl[i + 1];
			}
		}
	}

	#undef NUMBER_MAX
}

#define B_SZ 8
#define B_QUAD B_SZ * B_SZ

namespace conq_knights_tour_problem {
	typedef int step_t[2];
	typedef step_t step_list_t[8];

	std :: size_t findAvailiableSteps(int board[B_SZ][B_SZ], const step_t & step, step_list_t & steps, bool withWarnsdor = true);

	void make_step(int board[B_SZ][B_SZ], const step_t & step, step_t hist[B_QUAD], std :: size_t & histSz)
	{
		assert(step[0] >= 0 && step[0] < B_SZ);
		assert(step[1] >= 0 && step[1] < B_SZ);
		assert(board[step[0]][step[1]] == 0);

		hist[histSz][0] = step[0];
		hist[histSz][1] = step[1];

		board[step[0]][step[1]] = ++histSz;
#if 0
		std :: cout << "step = " << histSz << " " << step[0] << " " << step[1] << std :: endl;
		for (std :: size_t i = 0; i < B_SZ; ++i) {
			for (std :: size_t j = 0; j < B_SZ; ++j)
				std :: cout << " " << board[i][j];
			std :: cout << std :: endl;
		}
#endif
	}

	void undo_step(int board[B_SZ][B_SZ], step_t hist[B_QUAD], std :: size_t & histSz)
	{
		--histSz;
		board[hist[histSz][0]][hist[histSz][1]] = 0;
#if 0
		std :: cout << "UNDO step = " << histSz << std :: endl;
		for (std :: size_t i = 0; i < B_SZ; ++i) {
			for (std :: size_t j = 0; j < B_SZ; ++j)
				std :: cout << " " << board[i][j];
			std :: cout << std :: endl;
		}
#endif
	}

	void warnsdorfsRule(int board[B_SZ][B_SZ], step_list_t & steps, std :: size_t stepSz)
	{
		std :: size_t avail[8];
		step_list_t hist; // fake history
		std :: size_t hist_sz = 0; // fake history size
		step_list_t next_steps;
		for (std :: size_t i = 0; i < stepSz; ++i) {
			make_step(board, steps[i], hist, hist_sz);
			avail[i] = findAvailiableSteps(board, steps[i], next_steps, false);
			undo_step(board, hist, hist_sz);
		}

		// bubble sort
		for (std :: size_t i = 1; i < stepSz; ++i) {
			step_t s = { steps[i][0], steps[i][1] };
			int cur = i;
			std :: size_t a = avail[i];

			while (cur > 0) {
				if (a < avail[cur - 1]) {
					avail[cur] = avail[cur - 1];
					steps[cur][0] = steps[cur - 1][0];
					steps[cur][1] = steps[cur - 1][1];
				}
				else
					break;

				cur--;
			}

			avail[cur] = a;
			steps[cur][0] = s[0];
			steps[cur][1] = s[1];
		}
	}

	std :: size_t findAvailiableSteps(int board[B_SZ][B_SZ], const step_t & step, step_list_t & steps, bool withWarnsdor)
	{
		// not opmimal move
//		static const int x_move[8] = {-2, -2, -1, 1,  2, 2, -1,  1};
//		static const int y_move[8] = {-1, 1,   2, 2, -1, 1, -2, -2};

		// opmimal move to
		static const int x_move[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
		static const int y_move[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

		std :: size_t counter = 0;
		for (int i = 0; i < 8; ++i) {
			step_t candidate;
			candidate[0] = step[0] + x_move[i];
			if (candidate[0] >= 0 && candidate[0] < B_SZ) {
				candidate[1] = step[1] + y_move[i];
				if (candidate[1] >= 0 && candidate[1] < B_SZ && board[candidate[0]][candidate[1]] == 0) {
					steps[counter][0] = candidate[0];
					steps[counter][1] = candidate[1];
					++counter;
				}
			}
		}

		if (withWarnsdor)
			warnsdorfsRule(board, steps, counter);

		return counter;
	}

	bool resolveKnightsTourProblem(int board[B_SZ][B_SZ], step_t & step, step_t hist[B_QUAD], std :: size_t & histSz)
	{
		make_step(board, step, hist, histSz);

		if (histSz == B_QUAD)
			return true;

		step_list_t steps;

		std :: size_t steps_sz = findAvailiableSteps(board, step, steps);
		for (std :: size_t i = 0; i < steps_sz; ++i) {
			if (resolveKnightsTourProblem(board, steps[i], hist, histSz)) {
				return true;
			}
		}

		undo_step(board, hist, histSz);

		return false;
	}
} /** namespace conq_knights_tour_problem */

/**
 * \brief Knight's tour problem on 8x8 board
 */
void knightsTourProblem(char sym, std :: size_t num)
{
	assert(sym >= 'a' && sym < 'a' + B_SZ);

	assert(num >= 1 && num <= B_SZ);

	conq_common :: ChessBoard b(B_SZ);

	conq_knights_tour_problem :: step_t history[B_QUAD];

	int board[B_SZ][B_SZ]; // state 0 => empty, 1 => visited
	for (int i = 0; i < B_SZ; ++i)
		for (int j = 0; j < B_SZ; ++j) board[i][j] = 0;

	std :: size_t history_sz = 0;

	int i = static_cast<int>(sym - 'a');
	int j = static_cast<int>(B_SZ - num);
	conq_knights_tour_problem :: step_t pos = { i, j };

	if (!conq_knights_tour_problem :: resolveKnightsTourProblem(board, pos, history, history_sz)) {
		std :: cout << "impossible to resolve knight's tour problem\n";
	}
	else {
		for (std :: size_t i = 0; i < history_sz; ++i) {
			b.add('a' + history[i][0], B_SZ - history[i][1], conq_common :: ChessBoard :: ChessMan :: Knight_W);
			std :: cout << b.show() << std :: endl;
			sleep(1);
		}
	}
}

#undef B_QUAD
#undef B_SZ

} /* namespace conq_puzzle */
