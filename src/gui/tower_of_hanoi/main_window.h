/**
 * \file    main_window.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>
#include <QSpinBox>
#include "hanoi_thread.h"
#include "rod_widget.h"

class QPushButton;

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	/**
	 * \brief Constructor creates interface
	 */
	MainWindow(QWidget * p = nullptr);

	/**
	 * \brief Destructor
	 */
	~MainWindow();

	/**
	 * \brief Move disk from rod number 'src' to 'dst'
	 */
	bool moveDisk(int src, int dst);

	/**
	 * \brief Reset to base state
	 */
	void reset();

protected slots:
	void valueChanged(int i);
	void pressed();
	void nextStep(int src, int dst);

private:
	void createInterface();

private:
	QSpinBox * _diskQuantity, * _minStepQuantity;
	HanoiThread _thread;
	RodWidget * _rods[3];
	QPushButton * _control;
	bool _finished;
};

#endif /* MAIN_WINDOW_H_ */
