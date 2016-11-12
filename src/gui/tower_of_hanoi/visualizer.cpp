/**
 * \file    visualizer.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "visualizer.h"
#include <QtGlobal>

Visualizer::Visualizer(std :: size_t diskQuantity)
{
	setDiskQuantity(diskQuantity);
}

Visualizer::~Visualizer()
{
	// TODO Auto-generated destructor stub
}

void Visualizer :: setDiskQuantity(std :: size_t diskQuantity)
{
	_diskQuantity = diskQuantity;

	Q_ASSERT(_diskQuantity > 0);

	_maxDiskSize = _diskQuantity * 2 + 1;

	_height = _diskQuantity;
}
