/**
 * \file    main_window.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "main_window.h"

#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include <QWidget>
#include <QGraphicsView>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTimer>

MainWindow :: MainWindow(QWidget * p) : QMainWindow(p)
{
	QGraphicsView * view = new QGraphicsView(this);

	view->setFixedHeight(865);

	_planet = new Planet(view);

	view->setScene(_planet);

	view->setBackgroundBrush(QImage(":/img/space.jpg"));

	setCentralWidget(new QWidget);

	centralWidget()->setLayout(new QVBoxLayout);

	centralWidget()->layout()->addWidget(view);

	_distance = new QSpinBox(this);
	_distance->setValue(1);
	_distance->setMinimum(0);
	_distance->setMaximum(7);
	connect(_distance, SIGNAL(valueChanged(int)), SLOT(distanceChanged(int)));
	centralWidget()->layout()->addWidget(_distance);

	_control = new QDialogButtonBox(this);
	_start = _control->addButton(tr("Start"), QDialogButtonBox::AcceptRole);
	_stop = _control->addButton(tr("Stop"), QDialogButtonBox::RejectRole);
	connect(_control, SIGNAL(accepted()), SLOT(start()));
	connect(_control, SIGNAL(rejected()), SLOT(stop()));

	centralWidget()->layout()->addWidget(_control);

	view->show();

	_lr = _planet->addRobot(0, Robot :: Color :: Green);
	_rr = _planet->addRobot(1, Robot :: Color :: Blue);

	_timer = new QTimer(this);
	_timer->setInterval(1000);
	connect(_timer, SIGNAL(timeout()), SLOT(tick()));
}

MainWindow :: ~MainWindow()
{
	// TODO Auto-generated destructor stub
}

void MainWindow :: distanceChanged(int i)
{
	_planet->clear();

	if (i > 0) {
		_lr = _planet->addRobot(0, Robot :: Color :: Green);
		_rr = _planet->addRobot(i, Robot :: Color :: Blue);
		_control->setEnabled(true);
	}
	else
		_control->setDisabled(true);
}

void MainWindow :: start()
{
	int offset = _distance->value() * 2;

	_map.clear();
	_map[0].isParachute = true;
	_map[0].setRobot();
	_map[offset].isParachute = true;
	_map[offset].setRobot();

	_fwl = new RobotFirmwareV1(_map, 0);
	_fwr = new RobotFirmwareV1(_map, offset);

	_lr->loadFirmware(_fwl);
	_rr->loadFirmware(_fwr);

	_start->setDisabled(true);
	_stop->setEnabled(true);
	_distance->setDisabled(true);

	_timer->start();
}

void MainWindow :: stop()
{
	_timer->stop();
	_start->setEnabled(true);
	_stop->setDisabled(true);
	_distance->setEnabled(true);

	distanceChanged(_distance->value());
}

void MainWindow :: tick()
{
	_fwl->preAction();
	_fwr->preAction();

	bool run = _fwl->action() | _fwr->action();

	// cross collision
	if (!run)
		_timer->stop();

	run = _fwl->postAction() | _fwr->postAction();
	// cell collision
	if (!run)
		_timer->stop();
}
