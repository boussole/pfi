/*
 * \file    planet.h
 * \brief  
 * \details
 * \author  boussole
 */

#ifndef PLANET_H_
#define PLANET_H_

#include <QGraphicsScene>
#include "robot.h"

class Planet: public QGraphicsScene
{
public:
	Planet(QObject * p = nullptr);
	virtual ~Planet();
	Robot * addRobot(int pos, Robot :: Color color);

protected:
	void drawForeground(QPainter * painter, const QRectF & rect);

private:
	int _zeroPosition;
	int _bottomOffset;
	int _serifLen;
};

#endif /* PLANET_H_ */
