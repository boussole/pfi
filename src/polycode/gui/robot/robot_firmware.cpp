/**
 * \file    robot_firmware.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "robot_firmware.h"
#include <QDebug>

AbstractRobot :: ~AbstractRobot()
{
}

RobotFirmware :: RobotFirmware(QMap<int, PlanetCell> & map, int pos) :
	_map(map),
	_pos(pos),
	_run(true)
{
}

RobotFirmware :: ~RobotFirmware()
{
}

/****************************************
 * Robot firmware version
 *****************************************/

RobotFirmwareV1 :: RobotFirmwareV1(QMap<int, PlanetCell> & map, int pos) :
	RobotFirmware(map, pos),
	_speed(Speed :: Slow),
	_direction(Direction :: Right)
{

}

RobotFirmwareV1 :: ~RobotFirmwareV1()
{

}

void RobotFirmwareV1 :: moveRobot()
{
	if (_direction == Direction :: Left) {
		_map[_pos--].leaveRobot();
		_map[_pos].setRobot();
	}
	else {
		_map[_pos++].leaveRobot();
		_map[_pos].setRobot();
	}
}

bool RobotFirmwareV1 :: preAction()
{
	if (!_run)
		return false;

	moveRobot();

	return _run;
}

bool RobotFirmwareV1 :: action()
{
	if (!_run)
		return false;

	// found another robot in the middle of cell
	if (_map[_pos].robotQuantity > 1) {
		(_direction == Direction :: Left) ? _robot->left(2) : _robot->right(2);
		_robot->changeColor(AbstractRobot :: Color :: Black);
		_run = false;
		return _run;
	}

	moveRobot();

	return _run;
}

bool RobotFirmwareV1 :: postAction()
{
	if (!_run)
		return false;

	switch (_speed) {
		// search parachute
		case (Speed :: Slow): {
			if (_direction == Direction :: Left) {
				_robot->left();
				_direction = Direction :: Right2;
			}
			else {
				if (_direction == Direction :: Right) {
					_robot->right();
					_direction = Direction :: Left;
				}
				else if (_direction == Direction :: Right2) {
					_robot->right();
					_direction = Direction :: Right;
				}
				// found parachute
				if (_map[_pos].isParachute) {
					_speed = Speed :: Fast;
					_direction = Direction :: Right;
				}
			}
			break;
		}
		// search robot
		case (Speed :: Fast): {
			_robot->right(); //< always right
			break;
		}

		default : break;
	};

	// found another robot in the cell
	if (_map[_pos].robotQuantity > 1) {
		_robot->changeColor(AbstractRobot :: Color :: Black);
		_run = false;
		return _run;
	}

	return _run;
}
