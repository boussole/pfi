/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */

#ifndef GUI_HANOI
#	include "tower_of_hanoi_console.h"
#else
#	include <QApplication>
#	include "main_window.h"
#endif

int main(int argc, char ** argv)
{
#ifndef GUI_HANOI
	TowerOfHanoiConsole app(argc, argv);
#else
	QApplication app(argc, argv);

	MainWindow w;

	w.show();
#endif

	return app.exec();
}
