/*
 * \file    puzzle.h
 * \brief  
 * \details
 * \author  boussole
 */

#ifndef PUZZLE_H_
#define PUZZLE_H_

#include <ostream>

namespace conq_puzzle {

enum class TriangleType {
	Equilateral,
	Isosceles,
	Basic,
	Impossible
};

std::ostream &operator << (std::ostream &o, const TriangleType &type);

/**
 * \brief Identify triangle type by egdes
 */
TriangleType triangleType(double a, double b, double c);

/**
 * \brief Queen problem
 * \note  Actual for board size > 4
 */
void queenProblem(int boardSize = 8);

/**
 * \brief Sentence with numbers problem
 */
void sentenceWithNumbersProblem();

/**
 * \brief Knight's tour problem on 8x8 board
 */
void knightsTourProblem(char sym, std :: size_t num);

} /* namespace conq_puzzle */

#endif /* PUZZLE_H_ */
