/*
 * \file    chess_board.h
 * \brief  
 * \details
 * \author  boussole
 */

#ifndef CHESS_BOARD_H_
#define CHESS_BOARD_H_

#include "common.h"

namespace conq_common {
/**
 *   A B C D E F G H ...
 * 1
 * 2
 * 3
 * 4
 * 5
 * 6
 * 7
 * 8
 * \warning Tested only under linux utf8-r locale
 */

class ChessBoard
{
public:
	/*********************************************
	 * \enum
	 * \brief Figures type
	 *********************************************/
	enum class ChessMan {
		Empty,
		King_W,
		King_B,
		Queen_W,
		Queen_B,
		Rook_W,
		Rook_B,
		Bishop_W,
		Bishop_B,
		Knight_W,
		Knight_B,
		Pawn_W,
		Pawn_B,
		__Max_ChessMan
	};

	/********************************************
	 * \brief Create empty chess board size of 'sz'
	 ********************************************/
	ChessBoard(std :: size_t sz = 8);

	/********************************************
	 * \brief Destructor
	 ********************************************/
	virtual ~ChessBoard();

	/********************************************
	 * \brief Show board
	 ********************************************/
	std :: string show(const std :: string & indent = "");

	/********************************************
	 * \brief Put chess man
	 ********************************************/
	void add(char sym, std :: size_t num, ChessMan chm);

	/********************************************
	 * \brief Clear board
	 ********************************************/


private:
	std :: string _b;
	std :: size_t _sz, _sym_len, _row_len, _col_len, _chessman_offset, _border_len;
};

} /* namespace conq_common */

#endif /* CHESS_BOARD_H_ */
