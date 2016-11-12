/**
 * \file    Rods.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef RODS_H_
#define RODS_H_

#include <QVector>

// template <std :: size_t RodQuantity>
class Rods
{
public:
	/**
	 * \brief Constructor fill start state
	 */
	Rods(std :: size_t diskQuantity);

	/**
	 * \brief Destructor
	 */
	virtual ~Rods();

	/**
	 * \brief DiskId by level or 0 in case of empty level
	 */
	std :: size_t diskId(int rodId, int level) const;

	/**
	 * \brief Move disk from rod number 'src' to 'dst'
	 */
	bool moveDisk(int src, int dst);

	/**
	 * \brief Restore start state
	 */
	void reset(std :: size_t diskQuantity);

	/**
	 * \brief Check whether game is finished
	 */
	bool isFinished() const;

private:
	QVector<std :: size_t> _rods[3];
};

#endif /* RODS_H_ */
