/*
 * \file    chess_board.cpp
 * \brief  
 * \details
 * \author  boussole
 */

#include "chess_board.h"

namespace conq_common {

static const char * ChessManCode[] = {
	/* [Empty] = */ "\u2005",
	/* [King_W] = */ "\u2654",
	/* [King_B] = */ "\u265A",
	/* [Queen_W] = */ "\u2655",
	/* [Queen_B] = */ "\u265B",
	/* [Rook_W] = */ "\u2656",
	/* [Rook_B] = */ "\u265C",
	/* [Bishop_W] = */ "\u2657",
	/* [Bishop_B] = */ "\u265D",
	/* [Knight_W] = */ "\u2658",
	/* [Knight_B] = */ "\u265E",
	/* [Pawn_W] = */ "\u2659",
	/* [Pawn_B] = */ "\u265F",
};

/********************************************
 * \brief Create empty chess board size of 'sz'
 ********************************************/
ChessBoard :: ChessBoard(std :: size_t sz) : _sz(sz)
{
	assert(sz > 0 && sz <= 26);

	// make head
	for (std :: size_t i = 0, ch = 97; i < _sz; ++i, ++ch) {
		_b += "   ";
		_b += static_cast<char>(ch);
	}

	_b += '\n';

	_sym_len = _b.size();
	_row_len = 30 + 20 * (sz - 1);
	_col_len = 8;
	_chessman_offset = 4;

	std :: size_t s = _b.size();
	// high border
	_b += "\u250C";
	for (std :: size_t i = 0; i < sz - 1; ++i)
		_b += "\u2500\u2500\u2500\u252C";
	_b += "\u2500\u2500\u2500\u2510\n";

	_border_len = _b.size() - s;
	// middle
	for (std :: size_t i = 0; i < sz; ++i) {
		for (std :: size_t j = 0; j < sz; ++j)
			_b += "\u2502\u0020\u2005\u0020";
		_b += "\u2502\u0020" + std :: to_string(sz - i) + "\n";

		if (i + 1 != sz) {
			_b += "\u251C\u2500\u2500\u2500";
			for (std :: size_t j = 0; j < sz - 1; ++j)
				_b += "\u253C\u2500\u2500\u2500";
			_b += "\u2524\n";
		}
	}

	// low border
	_b += "\u2514";
	for (std :: size_t i = 0; i < sz - 1; ++i)
		_b += "\u2500\u2500\u2500\u2534";
	_b += "\u2500\u2500\u2500\u2518\n";
}

/********************************************
 * \brief Destructor
 ********************************************/
ChessBoard :: ~ChessBoard()
{

}

/********************************************
 * \brief Show board
 ********************************************/
std :: string ChessBoard :: show(const std :: string & indent)
{
	return _b;
}

/********************************************
 * \brief Put chess man
 ********************************************/
void ChessBoard :: add(char sym, std :: size_t num, ChessMan chm)
{
	if ((sym < 97) || (static_cast<unsigned char>(sym) > 97 + _sz) || (num > _sz) || (num == 0))
		return;

	std :: size_t row = _sz - num, col = sym - 97;
	std :: size_t pos = _sym_len + _row_len * row + _border_len + _col_len * col + _chessman_offset;

	_b.replace(pos, 3 /* magic utf8 */, ChessManCode[static_cast<int>(chm)], strlen(ChessManCode[static_cast<int>(chm)]));
}

} /* namespace conq_common */
