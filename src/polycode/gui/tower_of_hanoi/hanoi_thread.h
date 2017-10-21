/**
 * \file    hanoi_thread.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef HANOI_THREAD_H_
#define HANOI_THREAD_H_

#include <QThread>
#include "hanoi_puzzle_algorithm.h"


class HanoiThread: public QThread
{
	Q_OBJECT
public:
	HanoiThread();
	virtual ~HanoiThread();
	void start(std :: size_t quantity)
	{
		_algo.reset(quantity);
		QThread :: start();
	}

signals:
	void nextStep(int src, int dst);

protected:
	void run();

private:
	HanoiPuzzleAlgorithm _algo;
};

#endif /* HANOI_THREAD_H_ */
