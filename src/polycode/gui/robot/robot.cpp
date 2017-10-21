/**
 * \file    robot.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "robot.h"
#include <QDebug>

Robot::Robot(int step, Color color, QGraphicsPixmapItem * parent) : QGraphicsPixmapItem(parent)
{
	_step = step;

	changeColor(color);
}

Robot::~Robot()
{
//	qDebug("robot destroy\n");
}

void Robot :: changeColor(Color color)
{
	QString filename;

	switch (color) {
		case(Color :: Green): filename = ":img/android-green.png"; break;
		case(Color :: Blue): filename = ":img/android-blue.png"; break;
		case(Color :: Black): filename = ":img/android-black.png"; break;
		default: break;
	};

	setPixmap(QPixmap(filename).scaled(_step, _step));
}

void Robot :: left(int ratio)
{
	Q_ASSERT(pos().x() > _step / ratio);

	setPos(pos().x() - _step / ratio, pos().y());
}

void Robot :: right(int ratio)
{
	setPos(pos().x() + _step / ratio, pos().y());
}

void Robot :: move(int pos)
{
	Q_UNUSED(pos);
}

void Robot :: stay()
{

}
