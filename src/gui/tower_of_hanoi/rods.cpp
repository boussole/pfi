/**
 * \file    Rods.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "rods.h"

/**
 * \brief Constructor fill start state
 */
Rods :: Rods(std :: size_t diskQuantity)
{
	reset(diskQuantity);
}

/**
 * \brief Destructor
 */
Rods :: ~Rods()
{

}

/**
 * \brief DiskId by level or 0 in case of empty level
 */
std :: size_t Rods :: diskId(int rodId, int level) const
{
	Q_ASSERT(rodId >= 0 && rodId < 3);

	return (level < _rods[rodId].count()) ? _rods[rodId][level] : 0;
}

/**
 * \brief Move disk from rod number 'src' to 'dst'
 */
bool Rods :: moveDisk(int src, int dst)
{
	Q_ASSERT(src >= 0 && dst >= 0 && src < 3 && dst < 3);

	if (_rods[src].isEmpty())
		return false;

	if (!_rods[dst].isEmpty() && _rods[dst].last() < _rods[src].last())
		return false;

	_rods[dst].push_back(_rods[src].last());

	_rods[src].pop_back();

	return true;
}

/**
 * \brief Restore start state
 */
void Rods :: reset(std :: size_t diskQuantity)
{
	// foreach
	_rods[0].clear();
	_rods[1].clear();
	_rods[2].clear();

	for (int i = diskQuantity; i > 0; --i)
		_rods[0].push_back(i);
}

/**
 * \brief Check whether game is finished
 */
bool Rods :: isFinished() const
{
	return _rods[0].isEmpty() && _rods[1].isEmpty();
}
