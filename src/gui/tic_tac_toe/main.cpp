/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include <QApplication>
#include "main_window.h"

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	MainWindow w;

	w.show();

//    QDesktopWidget dw;
//    QRect resolution = dw.availableGeometry();
//    QPoint top_left((resolution.width() - w.geometry().width()) / 2, (resolution.height() - w.geometry().height()) / 2);
//    QPoint bottom_right(top_left.x() + w.geometry().width(), top_left.y() + w.geometry().height());
//    w.setGeometry(QRect(top_left, bottom_right));

	return app.exec();
}
