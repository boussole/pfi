/**
 * \file    console_visualizer.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "console_visualizer.h"

using namespace std;

ConsoleVisualizer::ConsoleVisualizer(std :: size_t diskQuantity) : Visualizer(diskQuantity)
{
	createInterface(diskQuantity);
}

ConsoleVisualizer::~ConsoleVisualizer()
{

}

void ConsoleVisualizer :: show(const Rods & rods)
{
	for (int level = _height; level >= 0; --level) {
		for (int rod_id = 0; rod_id < 3; ++rod_id) {
			cout << "     " << _lines[rods.diskId(rod_id, level)].constData();
		}
		cout << endl;
	}

	// underside
	for (int rod_id = 0; rod_id < 3; ++rod_id) {
		cout << "     " << _underside.constData();
	}
	cout << endl << endl << endl;
}

void ConsoleVisualizer :: createInterface(std :: size_t diskQuantity)
{
	setDiskQuantity(diskQuantity);

	int line_sz = diskQuantity + 1; /** empty pos + underside */
	_lines.reset(new QByteArray[line_sz]);

	std :: size_t half_underside = _maxDiskSize / 2;

	QByteArray fill_ba;
	// empty position
	fill_ba.fill(' ', half_underside + 1);
	_lines[0] += fill_ba + '|' + fill_ba;

	for (std :: size_t i = 1; i < diskQuantity + 1; ++i) {
		// left empty
		fill_ba.fill(' ', half_underside - i + 1);
		_lines[i] += fill_ba;
		// left payload + center + right payload
		fill_ba.fill('+', i * 2 + 1);
		_lines[i] += fill_ba;
		fill_ba.fill(' ', half_underside - i + 1);
		// right empty
		_lines[i] += fill_ba;
	}

	_underside.fill('-', _maxDiskSize + 2);
}
