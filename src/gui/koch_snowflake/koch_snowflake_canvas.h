/**
 * \file    canvas.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef KOCH_SNOWFLAKE_CANVAS_H_
#define KOCH_SNOWFLAKE_CANVAS_H_

#include <QFrame>

class KochSnowflakeCanvas: public QFrame
{
	Q_OBJECT
public:
	KochSnowflakeCanvas(QWidget * parent = nullptr);
	virtual ~KochSnowflakeCanvas();

public slots:
	void setDimension(int);

protected:
	void paintEvent(QPaintEvent * /* event */);
	void drawSnowflake(QPainter * /* painter */, QLine left, QLine middle, QLine right, int level);

private:
	int _dimension;
};

#endif /* KOCH_SNOWFLAKE_CANVAS_H_ */
