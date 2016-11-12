/**
 * \file    visualizer.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include <cstddef>
#include "rods.h"

class Visualizer
{
public:
	Visualizer(std :: size_t diskQuantity);
	virtual ~Visualizer();
	virtual void show(const Rods & rods) = 0;
	void setDiskQuantity(std :: size_t diskQuantity);

protected:
	std :: size_t _diskQuantity, _maxDiskSize;
	int _height;
};

#endif /* VISUALIZER_H_ */
