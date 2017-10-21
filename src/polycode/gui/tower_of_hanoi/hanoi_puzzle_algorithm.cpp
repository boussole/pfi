/*
 * \file    hanoi_puzzle_algorithm.cpp
 * \brief  
 * \details
 * \author  boussole
 */

#include "hanoi_puzzle_algorithm.h"

/**
 * \brief Constructor init start state
 */
HanoiPuzzleAlgorithm :: HanoiPuzzleAlgorithm(std :: size_t diskQuantity)
{
	 reset(diskQuantity);
}

/**
 * \brief Destructor
 */
HanoiPuzzleAlgorithm :: ~HanoiPuzzleAlgorithm()
{

}

/**
 * \brief Set start state using disk quantity
 */
void HanoiPuzzleAlgorithm :: reset(std :: size_t diskQuantity)
{
	Q_ASSERT(diskQuantity > 0);

	_diskQuantity = diskQuantity;

	for (int i = 0; i < 3; ++i)
		_rods[i].clear();

	while (diskQuantity > 0) {
		_rods[0].push(diskQuantity--);
	}
}

/**
 * \brief Start game
 */
void HanoiPuzzleAlgorithm :: start(std :: function<void(int, int, int, void *)> fn, void * args)
{
	_fn = fn;
	_args = args;
	moveTo(_diskQuantity, 0, 2);
}

/**
 * \brief Recoursive algorighm
 */
void HanoiPuzzleAlgorithm :: moveTo(int diskId, int src, int dst)
{
	if (diskId == 0)
		return;

	int unused_rod = 3 - (dst + src);

	if (_rods[src].top() != diskId) {
		moveTo(diskId - 1, src, unused_rod);
	}

	_rods[dst].push(_rods[src].top());

	_rods[src].pop();

	_fn(src, dst, _rods[dst].top(), _args);

	moveTo(diskId - 1, unused_rod, dst);
}
