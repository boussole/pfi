/**
 * \file    main_window.cpp
 * \brief
 * \details
 * \author  conquistador
 */

#include <QDebug>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDesktopWidget>
#include "main_window.h"
#include "koch_snowflake_canvas.h"

MainWindow :: MainWindow(QWidget * parent) : QMainWindow(parent)
{
	setCentralWidget(new QWidget);

	centralWidget()->setLayout(new QVBoxLayout);

	_koch = new KochSnowflakeCanvas(this);
	_dimen = new QSpinBox(this);
	_dimen->setMinimum(0);
	_dimen->setMaximum(7);
	connect(_dimen, SIGNAL(valueChanged(int)), _koch, SLOT(setDimension(int)));

	centralWidget()->layout()->addWidget(_koch);
	centralWidget()->layout()->addWidget(_dimen);
}

MainWindow :: ~MainWindow()
{

}

void MainWindow :: show()
{
	QMainWindow :: show();

	/* alight form */
	QDesktopWidget w;
	QRect resolution = w.availableGeometry();
	QPoint top_left((resolution.width() - geometry().width()) / 2, (resolution.height() - geometry().height()) / 2);
	QPoint bottom_right(top_left.x() + geometry().width(), top_left.y() + geometry().height());
	setGeometry(QRect(top_left, bottom_right));
}
