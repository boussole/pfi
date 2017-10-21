/**
 * \file    cell.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef CELL_H_
#define CELL_H_

#include <QPoint>
#include <QPushButton>
#include <QPalette>

class Cell : public QPushButton
{
public:
	Cell(QPoint coord, QWidget * p = nullptr);
	virtual ~Cell();
	QPoint & coord() { return _coord; }
	void resizeEvent(QResizeEvent * event);
	void reset();
	void press(QIcon & icon);
	bool isPressed() { return _isPressed; }

private:
	QPoint _coord;
	bool _isPressed;
	QPalette _pallete;
};

#endif /* CELL_H_ */
