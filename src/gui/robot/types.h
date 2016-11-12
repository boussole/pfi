/*
 * \file    types.h
 * \brief  
 * \details
 * \author  boussole
 */

#ifndef TYPES_H_
#define TYPES_H_

struct PlanetCell {
	PlanetCell() : isParachute(false), robotQuantity(0)
	{ }

	void setRobot()
	{ ++robotQuantity; }

	void leaveRobot()
	{ Q_ASSERT(robotQuantity > 0); --robotQuantity; }

	bool isParachute;
	int robotQuantity;
};

class AbstractRobot
{
public:
	enum class Color {
		Green, Blue, Black
	};

	AbstractRobot() {}
	virtual ~AbstractRobot() = 0;
	virtual void changeColor(Color color) = 0;
	virtual void left(int ratio = 1) = 0;
	virtual void right(int ratio = 1) = 0;
	virtual void move(int pos) = 0;
	virtual void stay() = 0;
};

#endif /* TYPES_H_ */
