/*
 * \file    planet.cpp
 * \brief  
 * \details
 * \author  boussole
 */

#include "planet.h"

#include <QPainter>
#include <QDebug>

Planet :: Planet(QObject * p) :
	QGraphicsScene(p)
{
	setSceneRect(0, 0, 1920, 845);
	int w = width();
	_zeroPosition = (w / 4);
	_zeroPosition -= _zeroPosition % 70;
	_bottomOffset = height() - 5;
	_serifLen = _bottomOffset - 5;
}

Planet :: ~Planet()
{

}

void Planet :: drawForeground(QPainter * painter, const QRectF & rect)
{
	QPen p(QBrush(Qt :: SolidPattern), 2);
	painter->setPen(p);
	painter->drawLine(rect.bottomLeft().x(), _bottomOffset, rect.bottomRight().x(), _bottomOffset);

	int start = rect.bottomLeft().x(), finish = rect.bottomRight().x();
	start = start - start % 70;
	while (start < finish) {
		painter->drawLine(start, _bottomOffset, start, _serifLen);
		start += 70;
	}
}

Robot * Planet :: addRobot(int pos, Robot :: Color color)
{
	Robot * robot = new Robot(70, color, nullptr);

	addItem(robot);

	QPointF p(_zeroPosition + (pos * 70), _bottomOffset - 70);

	robot->setPos(p);

	QGraphicsPixmapItem * parachute = new QGraphicsPixmapItem(QPixmap(":img/parachute2.png").scaled(70, 70));

	addItem(parachute);

	p.setY(p.y() - 70);

	parachute->setPos(p);

	return robot;
}
