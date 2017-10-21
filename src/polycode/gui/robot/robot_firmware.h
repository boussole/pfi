/**
 * \file    robot_firmware.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef ROBOT_FIRMWARE_H_
#define ROBOT_FIRMWARE_H_

#include <QMap>
#include "types.h"

class RobotFirmware
{
public:
	RobotFirmware(QMap<int, PlanetCell> & map, int pos);
	virtual ~RobotFirmware() = 0;
	virtual bool preAction() = 0;
	virtual bool action() = 0;
	virtual bool postAction() = 0;
	void grantAccess(AbstractRobot * robot)
	{ _robot = robot; }

protected:
	AbstractRobot * _robot;
	QMap<int, PlanetCell> & _map;
	int _pos;
	bool _run;
};

class RobotFirmwareV1 : public RobotFirmware
{
	enum class Speed {
		Slow,
		Fast
	};

	enum class Direction {
		Right,
		Right2,
		Left
	};

public:
	RobotFirmwareV1(QMap<int, PlanetCell> & map, int pos);
	~RobotFirmwareV1();
	bool preAction();
	bool action();
	bool postAction();

protected:
	void moveRobot();

private:
	Speed _speed;
	Direction _direction;
};

#endif /* ROBOT_FIRMWARE_H_ */
