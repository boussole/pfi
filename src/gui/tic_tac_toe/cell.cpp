/**
 * \file    cell.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "cell.h"

#include <QSizePolicy>
#include <QResizeEvent>

Cell::Cell(QPoint coord, QWidget * p) : QPushButton(p), _coord(coord), _isPressed(false)
{
	QSizePolicy s(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setSizePolicy(s);
	setDisabled(true);

	//setMinimumSize(QSize(30, 30));
	//setIconSize(QSize(60, 60));
}

Cell::~Cell()
{
}

void Cell::reset()
{
	_isPressed = false;
	setDisabled(true);
	setIcon(QIcon(""));
	setPalette(QPalette());
}

void Cell::press(QIcon & icon)
{
	setIcon(icon);
	_isPressed = true;
}

void Cell::resizeEvent(QResizeEvent * event)
{
	Q_UNUSED(event);
	setIconSize(QSize(width() / 2, height() / 2));
}
