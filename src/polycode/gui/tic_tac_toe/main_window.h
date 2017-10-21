/**
 * \file    main_window.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>
#include <QGridLayout>
#include <QButtonGroup>
#include <QPushButton>
#include <QSpinBox>
#include <QScopedArrayPointer>
#include <QIcon>

class MainWindow : public QMainWindow
{
	Q_OBJECT
	enum class Step { Cross, Zero };
public:
	MainWindow(QWidget * p = nullptr);
	virtual ~MainWindow();
	void show();

protected slots:
	void start();
	void stop();
	void resizeBoard(int);
	void cellClicked(QAbstractButton * button);

private:
	QIcon _cross, _zero;
	//int _oldBoardSize;
	QGridLayout * _board;
	QButtonGroup * _buttons;
	QPushButton * _start, * _stop;
	QSpinBox * _boardSize;
	int _free, _diag1, _diag2;
	Step _step;
	QScopedArrayPointer<int> _v, _h;
};

#endif /* MAIN_WINDOW_H_ */
