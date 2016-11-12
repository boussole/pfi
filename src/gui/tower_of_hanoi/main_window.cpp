/**
 * \file    main_window.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "main_window.h"

#include <QGridLayout>
#include <QtMath>
#include <QDebug>
#include <QPushButton>
#include "rod_widget.h"

/**
 * \brief Constructor creates interface
 */
MainWindow :: MainWindow(QWidget * p) : QMainWindow(p), _finished(true)
{
	createInterface();
}

/**
 * \brief Destructor
 */
MainWindow :: ~MainWindow()
{
	_thread.terminate();
}

/**
 * \brief Move disk from rod number 'src' to 'dst'
 */
bool MainWindow :: moveDisk(int src, int dst)
{
	Q_ASSERT(src >= 0 && src < 3 && dst >= 0 && src < 3 && src != dst);

	if (_rods[src]->diskId() == 0)
		return false;

	if (_rods[dst]->diskId() == 0 || _rods[src]->diskId() < _rods[dst]->diskId()) {
		QSharedPointer<DiskWidget> d = _rods[src]->pop();
		_rods[dst]->push(d);
		return true;
	}

	return false;
}

void MainWindow :: createInterface()
{
	setCentralWidget(new QWidget);

	QWidget * cw = centralWidget();

	cw->setLayout(new QGridLayout);

	QGridLayout * l = static_cast<QGridLayout *>(cw->layout());

	for (int i = 0; i < 3; ++i) {
		_rods[i] = new RodWidget;
		l->addWidget(_rods[i], 0, i);
	}

	_diskQuantity = new QSpinBox(this);
	connect(_diskQuantity, SIGNAL(valueChanged(int)), SLOT(valueChanged(int)), Qt::QueuedConnection);
	_diskQuantity->setMinimum(1);
	_diskQuantity->setMaximum(10);
	_diskQuantity->setValue(6);
	l->addWidget(_diskQuantity, 1, 0);

	_minStepQuantity = new QSpinBox(this);
	_minStepQuantity->setReadOnly(true);
	_minStepQuantity->setMaximum(1500);
	l->addWidget(_minStepQuantity, 1, 1);

	_control = new QPushButton(tr("run"), this);
	connect(_control, SIGNAL(pressed()), SLOT(pressed()));
	l->addWidget(_control, 1, 2);

	connect(&_thread, SIGNAL(nextStep(int, int)), SLOT(nextStep(int, int)));
}

void MainWindow :: valueChanged(int i)
{
	_rods[0]->fill(i);
	_minStepQuantity->setValue(qPow(2, i) - 1);
}

void MainWindow :: pressed()
{
	// start
	if (_finished) {
		reset();
		_control->setText(tr("finish"));
		_finished = false;
		_diskQuantity->setDisabled(true);
		_thread.start(_diskQuantity->value());
	}
	else {
		_thread.terminate();
		_thread.wait(3);
		_diskQuantity->setEnabled(true);
		_control->setText(tr("run"));
		_finished = true;
		reset();
	}
}

void MainWindow :: nextStep(int src, int dst)
{
	bool ok = moveDisk(src, dst);
	Q_ASSERT(ok);
}

/**
 * \brief Reset to base state
 */
void MainWindow :: reset()
{
	for (int i = 0 ; i < 3; ++i) {
		_rods[i]->clear();
	}

	_rods[0]->fill(_diskQuantity->value());
}
