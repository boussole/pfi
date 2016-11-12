/*
 * \file    hanoi_puzzle_algorithm.h
 * \brief  
 * \details
 * \author  boussole
 */

#ifndef HANOI_PUZZLE_ALGORITHM_H_
#define HANOI_PUZZLE_ALGORITHM_H_

#include <QStack>
#include <functional>

class HanoiPuzzleAlgorithm {
public:
	/**
	 * \brief Constructor init start state
	 */
	HanoiPuzzleAlgorithm(std :: size_t diskQuantity);

	/**
	 * \brief Destructor
	 */
	virtual ~HanoiPuzzleAlgorithm();

	/**
	 * \brief Set start state using disk quantity
	 */
	void reset(std :: size_t diskQuantity);

	/**
	 * \brief Start game
	 */
	void start(std :: function<void(int, int, int, void *)> fn, void * args);

protected:
	/**
	 * \brief Recoursive algorighm
	 */
	void moveTo(int diskId, int src, int dst);

private:
	QStack<int> _rods[3];
	std :: size_t _diskQuantity;
	std :: function<void(int, int, int, void *)> _fn;
	void * _args;
};

#endif /* HANOI_PUZZLE_ALGORITHM_H_ */
