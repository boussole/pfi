/**
 * \file    main_window.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>
#include <QMap>

#include "types.h"
#include "planet.h"

class QSpinBox;
class QPushButton;
class QDialogButtonBox;
class Robot;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget * p = nullptr);
	virtual ~MainWindow();

protected:

protected slots:
	void start();
	void stop();
	void tick();
	void distanceChanged(int val);

private:
	Planet * _planet;
	QSpinBox * _distance;
	QDialogButtonBox * _control;
	QPushButton * _start, * _stop;
	QTimer * _timer;
	Robot * _lr, * _rr;
	RobotFirmwareV1 * _fwl, * _fwr;
	QMap<int, PlanetCell> _map;
};

#endif /* MAIN_WINDOW_H_ */
