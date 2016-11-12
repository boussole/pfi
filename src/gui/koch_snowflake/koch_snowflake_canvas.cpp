/**
 * \file    canvas.cpp
 * \brief
 * \details
 * \author  conquistador
 */

#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QLine>
#include <QDebug>
#include "koch_snowflake_canvas.h"

KochSnowflakeCanvas :: KochSnowflakeCanvas(QWidget * parent) : QFrame(parent), _dimension(0)
{
	// TODO Auto-generated constructor stub
	//setFixedSize(900, 300);
	setFrameShape(QFrame::Box);
}

KochSnowflakeCanvas :: ~KochSnowflakeCanvas()
{
	// TODO Auto-generated destructor stub
}

void KochSnowflakeCanvas :: paintEvent(QPaintEvent * event)
{
	QFrame :: paintEvent(event);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(Qt::darkBlue, 1));

	//painter.drawLine(0, height() - 10, width(), height() - 10);
	int part = width() / 3;
	QLine l(0, height() - 10, part, height() - 10);
	QLine m(part, height() - 10, 2 * part, height() - 10);
	QLine r(2 * part, height() - 10, 3 * part, height() - 10);

	drawSnowflake(&painter, l, m, r, _dimension);
}

void KochSnowflakeCanvas :: drawSnowflake(QPainter * p, QLine left, QLine middle, QLine right, int level)
{
	if (level == 0) {
		p->drawLine(left);
		p->drawLine(middle);
		p->drawLine(right);
		return;
	}

	QLine l, m, r; // new lines

	int x_step = (left.x2() - left.x1()) / 3;
	int y_step = (left.y2() - left.y1()) / 3;

	// preprocess left
	l.setLine(left.x1(), left.y1(), left.x1() + x_step, left.y1() + y_step);
	m.setLine(l.x2(), l.y2(), l.x2() + x_step, l.y2() + y_step);
	r.setLine(m.x2(), m.y2(), m.x2() + x_step, m.y2() + y_step);
	drawSnowflake(p, l, m, r, level - 1);

	#define COS_60 0.5
	#define SIN_60 -0.866

	QPoint move(middle.x2() - middle.x1(), middle.y2() - middle.y1());
	QPoint rotation(move.x() * COS_60 - move.y() * SIN_60, move.x() * SIN_60 + move.y() * COS_60);

	QLine lm(middle.x1(), middle.y1(), rotation.x() + middle.x1(), rotation.y() + middle.y1());
	QLine rm(lm.x2(), lm.y2(), middle.x2(), middle.y2());

	#undef COS_60
	#undef SIN_60

	x_step = (lm.x2() - lm.x1()) / 3;
	y_step = (lm.y2() - lm.y1()) / 3;
	l.setLine(lm.x1(), lm.y1(), lm.x1() + x_step, lm.y1() + y_step);
	m.setLine(l.x2(), l.y2(), l.x2() + x_step, l.y2() + y_step);
	r.setLine(m.x2(), m.y2(), lm.x2(), lm.y2());
	drawSnowflake(p, l, m, r, level - 1);

	x_step = (rm.x2() - rm.x1()) / 3;
	y_step = (rm.y2() - rm.y1()) / 3;
	l.setLine(rm.x1(), rm.y1(), rm.x1() + x_step, rm.y1() + y_step);
	m.setLine(l.x2(), l.y2(), l.x2() + x_step, l.y2() + y_step);
	r.setLine(m.x2(), m.y2(), middle.x2(), middle.y2());
	drawSnowflake(p, l, m, r, level - 1);

	// preprocess right
	x_step = (right.x2() - right.x1()) / 3;
	y_step = (right.y2() - right.y1()) / 3;
	l.setLine(right.x1(), right.y1(), right.x1() + x_step, right.y1() + y_step);
	m.setLine(l.x2(), l.y2(), l.x2() + x_step, l.y2() + y_step);
	r.setLine(m.x2(), m.y2(), right.x2(), right.y2());
	drawSnowflake(p, l, m, r, level - 1);
}

void KochSnowflakeCanvas :: setDimension(int dim)
{
	_dimension = dim;

	repaint(0, 0, width(), height());
}
