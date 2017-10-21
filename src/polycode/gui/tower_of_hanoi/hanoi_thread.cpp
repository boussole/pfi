/**
 * \file    hanoi_thread.cpp
 * \brief
 * \details
 * \author  boussole
 */
#include "hanoi_thread.h"

#include <QDebug>

HanoiThread::HanoiThread() : _algo(6)
{
	// TODO Auto-generated constructor stub

}

HanoiThread::~HanoiThread()
{
	// TODO Auto-generated destructor stub
}

void HanoiThread :: run()
{
	_algo.start([&](int src, int dst, int id, void * arg) {
		Q_UNUSED(id);
		Q_UNUSED(arg);
		emit nextStep(src, dst);
		sleep(1);
	}, nullptr);
}
