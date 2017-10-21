/**
 * \file    main_window.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "main_window.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include "cell.h"

#define DEFAULT_BOARD_SIZE 3

MainWindow::MainWindow(QWidget * w) : QMainWindow(w), _cross(":/img/cross.png"), _zero(":img/zero.png")
{
	setWindowTitle(tr("Tic tac toe"));
	setCentralWidget(new QWidget);

	QVBoxLayout * vl = new QVBoxLayout;
	centralWidget()->setLayout(vl);

	_board = new QGridLayout;
	vl->addLayout(_board);

//	_oldBoardSize = 0;

	_boardSize = new QSpinBox(this);
	_boardSize->setValue(DEFAULT_BOARD_SIZE);
	_boardSize->setMinimum(2);
	_boardSize->setMaximum(20);
	connect(_boardSize, SIGNAL(valueChanged(int)), SLOT(resizeBoard(int)));
	vl->addWidget(_boardSize);

	QHBoxLayout * hl = new QHBoxLayout;
	vl->addLayout(hl);

	_start = new QPushButton(tr("Start"), this);
	connect(_start, SIGNAL(clicked()), SLOT(start()));
	hl->addWidget(_start);

	_stop = new QPushButton(tr("Stop"), this);
	connect(_stop, SIGNAL(clicked()), SLOT(stop()));
	_stop->setDisabled(true);
	hl->addWidget(_stop);

	_buttons = new QButtonGroup(this);
	connect(_buttons, SIGNAL(buttonClicked(QAbstractButton *)), SLOT(cellClicked(QAbstractButton *)));

	resizeBoard(DEFAULT_BOARD_SIZE);
}

MainWindow::~MainWindow()
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

/**
 * \todo Optimaze resizing
 */
void MainWindow :: resizeBoard(int newSize)
{
	QList<QAbstractButton *> list = _buttons->buttons();

	// clear previous grid
	while (!list.isEmpty()) {
		QAbstractButton * b = list.takeFirst();
		_board->removeWidget(b);
		delete b;
	}

	for (int i = 0; i < newSize; ++i)
	for (int j = 0; j < newSize; ++j) {
		Cell * c = new Cell(QPoint(i, j));
		_buttons->addButton(c);
		_board->addWidget(c, i, j);
	}

	_v.reset(new int[newSize]);
	_h.reset(new int[newSize]);

//	_oldBoardSize = newSize;
}

void MainWindow :: start()
{
	QList<QAbstractButton *> b = _buttons->buttons();

	for (int i = 0; i < b.length(); ++i) {
		Cell * c = static_cast<Cell*>(b[i]);
		c->setEnabled(true);
	}

	for (int i = 0; i < _boardSize->value(); ++i)
		_v[i] = _h[i] = 0;

	_start->setDisabled(true);
	_stop->setEnabled(true);
	_boardSize->setDisabled(true);
	_step = Step :: Cross;
	_free = b.length();
	_diag1 = _diag2 = 0;
}

void MainWindow :: stop()
{
	QList<QAbstractButton *> b = _buttons->buttons();

	for (int i = 0; i < b.length(); ++i) {
		Cell * c = static_cast<Cell*>(b[i]);
		c->reset();
	}

	_start->setEnabled(true);
	_stop->setDisabled(true);
	_boardSize->setEnabled(true);
}

void MainWindow :: cellClicked(QAbstractButton * button)
{

	Cell * c = static_cast<Cell *>(button);
//	qDebug("i = %d, j = %d\n", c->coord().rx(), c->coord().ry());
	if (_free == 0 || c->isPressed())
		return;

	--_free;

	int offset = 0;

	switch (_step) {
		case(Step :: Cross): {
			c->press(_cross);
			offset = +1;
			_step = Step :: Zero;
			break;
		}
		case(Step :: Zero): {
			c->press(_zero);
			offset = -1;
			_step = Step :: Cross;
			break;
		}
		default: break;
	};

	// check winner in O(1)
	// 1. line
	_h[c->coord().rx()] += offset;
	if (qAbs(_h[c->coord().rx()]) == _boardSize->value()) {
		_free = 0;
		QList<QAbstractButton *> l = _buttons->buttons();
		int row = c->coord().rx() * _boardSize->value();
		for (int i = 0; i < _boardSize->value(); ++i)
			static_cast<Cell *>(l[row + i])->setPalette(QPalette(Qt::black));
	}

	// 2. column
	_v[c->coord().ry()] += offset;
	if (qAbs(_v[c->coord().ry()]) == _boardSize->value()) {
		_free = 0;
		QList<QAbstractButton *> l = _buttons->buttons();
		int col = c->coord().ry();
		for (int i = 0; i < _boardSize->value(); ++i, col += _boardSize->value())
			static_cast<Cell *>(l[col])->setPalette(QPalette(Qt::black));
	}

	// 3. main diag
	if (c->coord().rx() - c->coord().ry() == 0) {
		_diag1 += offset;
		if (qAbs(_diag1) == _boardSize->value()) {
			_free = 0;
			QList<QAbstractButton *> l = _buttons->buttons();
			int diag_offset = _boardSize->value() + 1;
			for (int i = 0; i < l.length(); i += diag_offset)
				static_cast<Cell *>(l[i])->setPalette(QPalette(Qt::black));
		}
	}

	// 4. diag
	if (c->coord().rx() + c->coord().ry() == _boardSize->value() - 1){
		_diag2 += offset;
		if (qAbs(_diag2) == _boardSize->value()) {
			_free = 0;
			QList<QAbstractButton *> l = _buttons->buttons();
			int diag_offset = _boardSize->value() - 1;
			for (int i = 0, pos = diag_offset; i < _boardSize->value(); ++i, pos += diag_offset)
				static_cast<Cell *>(l[pos])->setPalette(QPalette(Qt::black));
		}
	}
}
