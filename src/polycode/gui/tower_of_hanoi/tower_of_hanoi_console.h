/**
 * \file    tower_of_hanoi_console.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef TOWER_OF_HANOI_CONSOLE_H_
#define TOWER_OF_HANOI_CONSOLE_H_

#include "rods.h"
#include "console_visualizer.h"

class TowerOfHanoiConsole
{
public:
	TowerOfHanoiConsole(int argc, char ** argv);
	virtual ~TowerOfHanoiConsole();
	int exec();

private:
	Rods _rods;
	ConsoleVisualizer _visual;
	std :: size_t _diskQuantity;
	int _retval;
};

#endif /* TOWER_OF_HANOI_CONSOLE_H_ */
