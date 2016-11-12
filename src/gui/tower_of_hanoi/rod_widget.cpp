/**
 * \file    rod_widget.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "rod_widget.h"

#include <QPen>
#include <QPainter>
#include <QPaintEvent>
#include <QRectF>
#include <QFrame>
#include <QScopedPointer>
#include <QDebug>

struct DiskView {
	Qt::GlobalColor _color;
	int _width;
};

DiskView View[] = {
	{ Qt::yellow, 30 },
	{ Qt::blue, 60 },
	{ Qt::red, 90 },
	{ Qt::green, 120 },
	{ Qt::magenta, 150 },
	{ Qt::cyan, 180 },
	{ Qt::gray, 210 },
	{ Qt::darkYellow, 240 },
	{ Qt::darkBlue, 270 },
	{ Qt::darkRed, 290 },
};

class DiskWidget : public QFrame
{
public:
	DiskWidget(int id, QWidget * parent = nullptr) :
		QFrame(parent), _id(id + 1)
	{
		setFrameShadow(QFrame::Raised);
		setFrameShape(QFrame::WinPanel);
		setAutoFillBackground(true);
		setPalette(QPalette(View[id]._color));
		setFixedWidth(View[id]._width);
		setFixedHeight(30);
	}

	~DiskWidget()
		{}

	int id() const
		{ return _id; }

private:
	int _id;
};

/**
 * \brief Constructor
 */
RodWidget::RodWidget(QWidget * p) : QWidget(p)
{
	_grid = new QGridLayout(this);
	_grid->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);
	_grid->setVerticalSpacing(0);
	setFixedWidth(400);
	setFixedHeight(700);
}

/*
 * \brief Destructor
 */
RodWidget::~RodWidget()
{
}

/**
 * \brief Rendering picture
 */
void RodWidget::paintEvent(QPaintEvent * event)
{
	QWidget :: paintEvent(event);

	QPainter painter(this);
	QPen p(QBrush(Qt :: SolidPattern), 5);
	painter.setPen(p);
	painter.drawRect(0, height() - 5, width(), 5);
	painter.drawLine(width() / 2, height() - 5, width() / 2, height() / 2);
}

/**
 * \brief Fill rod by disks
 */
void RodWidget::fill(std :: size_t diskQuantity)
{
	clear();

	for (std :: size_t row = 0, disk_id = diskQuantity; disk_id > 0; --disk_id, ++row) {
		_disk.push(QSharedPointer<DiskWidget>(new DiskWidget(disk_id - 1)));
		_grid->addWidget(_disk.top().data(), disk_id - 1, 0, Qt :: AlignCenter);
	}
}

/**
 * \brief Clear rod
 */
void RodWidget::clear()
{
	while (!_disk.isEmpty()) {
		_grid->removeWidget(_disk.top().data());
		_disk.pop();
	}
}

/**
 * \brief Get top diskId or 0 in case of empty rod
 */
std :: size_t RodWidget::diskId()
{
	if (!_disk.isEmpty())
		return _disk.top()->id();

	return 0;
}

/**
 * \brief Put disk to top
 */
void RodWidget::push(QSharedPointer<DiskWidget> disk)
{
	Q_ASSERT(_disk.isEmpty() || _disk.top()->id() > disk->id());

	for (int i = 0, row = _grid->rowCount(); i < _disk.count(); ++i, --row) {
//		qDebug() << "move №" << _disk[i].data()->id() << " to " << row << "i == " << i;
		_grid->removeWidget(_disk[i].data());
		_grid->addWidget(_disk[i].data(), row, 0, Qt :: AlignCenter);
	}

	_disk.push(disk);
	_grid->addWidget(_disk.top().data(), 0, 0, Qt :: AlignCenter);
}

/**
 * \brief Get top disk
 */
QSharedPointer<DiskWidget> RodWidget::pop()
{
	Q_ASSERT(!_disk.isEmpty());

	// remove
	_grid->removeWidget(_disk.top().data());
	QSharedPointer<DiskWidget> ptr = _disk.pop();

	// up widgets
	for (int row = 0, i = _disk.count() - 1; i >= 0; ++row, --i) {
//		qDebug() << "move №" << _disk[i].data()->id() << " to " << row;
		_grid->removeWidget(_disk[i].data());
		_grid->addWidget(_disk[i].data(), row, 0, Qt :: AlignCenter);
	}

	return ptr;
}
