/**
 * \file    rod_widget.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef ROD_WIDGET_H_
#define ROD_WIDGET_H_

#include <QWidget>
#include <QGridLayout>
#include <QStack>
#include <QSharedPointer>

class DiskWidget;

class RodWidget: public QWidget
{
public:
	/**
	 * \brief Constructor
	 */
	RodWidget(QWidget * parent = nullptr);

	/*
	 * \brief Destructor
	 */
	virtual ~RodWidget();

	/**
	 * \brief Fill rod by disks
	 */
	void fill(std :: size_t diskQuantity);

	/**
	 * \brief Clear rod
	 */
	void clear();

	/**
	 * \brief Get top diskId or 0 in case of empty rod
	 */
	std :: size_t diskId();

	/**
	 * \brief Put disk to top
	 */
	void push(QSharedPointer<DiskWidget> disk);

	/**
	 * \brief Get top disk
	 */
	QSharedPointer<DiskWidget> pop();

protected:
	/**
	 * \brief Rendering picture
	 */
	void paintEvent(QPaintEvent * event);

private:
	QGridLayout * _grid;
	QStack<QSharedPointer<DiskWidget> > _disk;
};

#endif /* ROD_WIDGET_H_ */
