/**
 * \file    console_visualizer.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef CONSOLE_VISUALIZER_H_
#define CONSOLE_VISUALIZER_H_

#include "visualizer.h"
#include <iostream>
#include <QScopedArrayPointer>
#include <QByteArray>

class ConsoleVisualizer : protected Visualizer
{
public:
	ConsoleVisualizer(std :: size_t diskQuantity);
	virtual ~ConsoleVisualizer();
	void show(const Rods & rods) override;
	void createInterface(std :: size_t diskQuantity);

private:
	QScopedArrayPointer<QByteArray> _lines;
	QByteArray _underside;
};

#endif /* CONSOLE_VISUALIZER_H_ */
