/**
 * \file    main_window.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>

class KochSnowflakeCanvas;
class QSpinBox;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget * parent = 0);
	virtual ~MainWindow();
	void show();

private:
	KochSnowflakeCanvas * _koch;
	QSpinBox * _dimen;
};

#endif /* MAIN_WINDOW_H_ */
