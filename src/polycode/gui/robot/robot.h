/**
 * \file    robot.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef ROBOT_H_
#define ROBOT_H_

#include <QGraphicsPixmapItem>
#include "robot_firmware.h"

class QGraphicsItem;
class QGraphicsPixmapItem;
class Planet;

class Robot : public QGraphicsPixmapItem, public AbstractRobot
{
	friend class Planet;
public:
	virtual void changeColor(Color color);
	virtual void left(int ratio = 1);
	virtual void right(int ratio = 1);
	virtual void move(int pos);
	virtual void stay();
	void loadFirmware(RobotFirmware * firmware)
	{ firmware->grantAccess(this); }

protected:
	Robot(int step, Color color, QGraphicsPixmapItem * parent = 0);
	virtual ~Robot();
private:
	int _step;
};

#endif /* ROBOT_H_ */
