/*
 * \file    main.cpp
 * \brief  
 * \details
 * \author  boussole
 */

#include <common/common.h>
#include <common/chess_board.h>
#include "puzzle.h"

using namespace std;
using namespace conq_puzzle;
using namespace conq_common;

// test board framework
void test_chessBoard()
{
	ChessBoard board;
	board.add('a', 1, ChessBoard :: ChessMan :: Rook_W);
	board.add('b', 1, ChessBoard :: ChessMan :: Knight_W);
	board.add('c', 1, ChessBoard :: ChessMan :: Bishop_W);
	board.add('d', 1, ChessBoard :: ChessMan :: Queen_W);
	board.add('e', 1, ChessBoard :: ChessMan :: King_W);
	board.add('f', 1, ChessBoard :: ChessMan :: Bishop_W);
	board.add('g', 1, ChessBoard :: ChessMan :: Knight_W);
	board.add('h', 1, ChessBoard :: ChessMan :: Rook_W);
	board.add('a', 2, ChessBoard :: ChessMan :: Pawn_W);
	board.add('b', 2, ChessBoard :: ChessMan :: Pawn_W);
	board.add('c', 2, ChessBoard :: ChessMan :: Pawn_W);
	board.add('d', 2, ChessBoard :: ChessMan :: Pawn_W);
	board.add('e', 2, ChessBoard :: ChessMan :: Pawn_W);
	board.add('f', 2, ChessBoard :: ChessMan :: Pawn_W);
	board.add('g', 2, ChessBoard :: ChessMan :: Pawn_W);
	board.add('h', 2, ChessBoard :: ChessMan :: Pawn_W);
	//-
	board.add('a', 8, ChessBoard :: ChessMan :: Rook_B);
	board.add('b', 8, ChessBoard :: ChessMan :: Knight_B);
	board.add('c', 8, ChessBoard :: ChessMan :: Bishop_B);
	board.add('d', 8, ChessBoard :: ChessMan :: Queen_B);
	board.add('e', 8, ChessBoard :: ChessMan :: King_B);
	board.add('f', 8, ChessBoard :: ChessMan :: Bishop_B);
	board.add('g', 8, ChessBoard :: ChessMan :: Knight_B);
	board.add('h', 8, ChessBoard :: ChessMan :: Rook_B);
	board.add('a', 7, ChessBoard :: ChessMan :: Pawn_B);
	board.add('b', 7, ChessBoard :: ChessMan :: Pawn_B);
	board.add('c', 7, ChessBoard :: ChessMan :: Pawn_B);
	board.add('d', 7, ChessBoard :: ChessMan :: Pawn_B);
	board.add('e', 7, ChessBoard :: ChessMan :: Pawn_B);
	board.add('f', 7, ChessBoard :: ChessMan :: Pawn_B);
	board.add('g', 7, ChessBoard :: ChessMan :: Pawn_B);
	board.add('h', 7, ChessBoard :: ChessMan :: Pawn_B);
	cout << board.show() << endl;
}

/************************************************************
 * \brief #107: Triangle type
 ************************************************************/
TICKET_FN(107)
{
	cout << "#" << ticket << ": triangle type\n";

	cout << "a = " << 0 << ", b = " << 0 << ", c = " << 1 << " => " << triangleType(0, 0, 1) << endl;

	cout << "a = " << 2 << ", b = " << 2 << ", c = " << 3 << " => " << triangleType(2, 2, 3) << endl;

	cout << "a = " << 3 << ", b = " << 3 << ", c = " << 3 << " => " << triangleType(3, 3, 3) << endl;

	cout << "a = " << 5 << ", b = " << 3 << ", c = " << 4 << " => " << triangleType(5, 3, 4) << endl;

	cout << "a = " << 12 << ", b = " << 5 << ", c = " << 13 << " => " << triangleType(12, 5, 13) << endl;

	cout << "a = " << 3 << ", b = " << 2 << ", c = " << 4 << " => " << triangleType(3, 2, 4) << endl;

	cout << "a = " << 7 << ", b = " << 8 << ", c = " << 6 << " => " << triangleType(7, 8, 6) << endl;

	cout << "a = " << 7 << ", b = " << 2 << ", c = " << 3 << " => " << triangleType(7, 2, 3) << endl;
}

/************************************************************
 * \brief #10: Eight queens problem
 ************************************************************/
TICKET_FN(10)
{
	cout << "#" << ticket << ": eight queens problem\n";

	//test_chessBoard();

	std :: size_t board_sz = 8;

	if (argc == 2) {
		int bs = atoi(argv[1]);
		if (bs <= 0) {
			cout << "invalid board size param, using default\n";
			cout << "usage: " << *argv << " <board size>\n";
		}
		else
			board_sz = static_cast<std :: size_t>(bs);
	}

	queenProblem(board_sz);
}


/************************************************************
 * \brief #306: Sentence with numbers
 ************************************************************/
TICKET_FN(306)
{
	cout << "#" << ticket << ": sentence with numbers\n";

	sentenceWithNumbersProblem();
}

/************************************************************
 * \brief #241: Knight's tour problem
 ************************************************************/
TICKET_FN(241)
{
	cout << "#" << ticket << ": knight's tour 8x8 board\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <SYM> <NUM> (a 3)\n";
		return;
	}

	knightsTourProblem(*argv[1], atoi(argv[2]));
}

int main(int argc, char *argv[])
{
	/* uncomment one of them */

//	test_chessBoard();

//	ticket_241(argc, argv);

//	ticket_306(argc, argv);

//	ticket_10(argc, argv);

//	ticket_107(argc, argv);

	return 0;
}
