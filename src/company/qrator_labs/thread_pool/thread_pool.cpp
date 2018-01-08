/**
 * \file    ThreadPool.cpp
 * \brief
 * \details
 * \author  conquistador
 */

#include <assert.h>
#include <string>
//-
//-
#include "thread_pool.h"

using namespace std;
using namespace boost::interprocess;

ThreadPool :: ThreadPool(std :: size_t quantity) :
	_waitTaskSem(0),
	_stopped(false),
	_highPriorityCounter(0)
{
	assert(quantity > 0);

	while (quantity--)
		_workers.create_thread(boost :: bind(&ThreadPool :: threadWork, this));

	// we can wait them
}

ThreadPool :: ~ThreadPool()
{
	stop();
}

/**
 * \brief Enqueue task
 * \todo  Queue size control
 */
bool ThreadPool :: enqueue(boost :: shared_ptr<__details :: ITask> task, Priority p)
{
	boost :: mutex :: scoped_lock sl(_lock);

	if (!_stopped) {
		_taskQueue[p].push_front(task);
		_waitTaskSem.post();
		return true;
	}

	return false;
}

/**
 * \brief Stop
 */
void ThreadPool :: stop()
{
	{	// mark stopping
		boost :: mutex :: scoped_lock sl(_lock);
		_stopped = true;
	}

	// wake up all sleeping threads
	for (size_t i = 0; i < _workers.size(); ++i)
		_waitTaskSem.post();

	// wait working tasks
	_workers.join_all();
}

/**
 * \brief Worker thread
 */
void ThreadPool :: threadWork()
{
	stringstream o;

	o << "[" << syscall(SYS_gettid) << "]: started\n";

	cout << o.str();

	o.str("");

	while (true) {
		// wait external event
		_waitTaskSem.wait();

		boost :: shared_ptr<__details :: ITask> task;

		// check task
		{
			boost :: mutex :: scoped_lock sl(_lock);

			if (_stopped)
				break;

			task = schedTask();
		}

		task->execute();
	}

	o << "[" << syscall(SYS_gettid) << "]: stopped\n";

	cout << o.str();
}

/**
 * \brief   Schedule next task
 * \warning NOT Thread safe
 */
boost :: shared_ptr<__details :: ITask> ThreadPool :: schedTask()
{
	boost :: shared_ptr<__details :: ITask> task;

	assert(!_taskQueue[HIGH].empty() || !_taskQueue[NORMAL].empty() || !_taskQueue[LOW].empty());

	Priority p = HIGH;

	if (!_taskQueue[HIGH].empty()) {
		if (_highPriorityCounter < HighPriorityLimit)
			++_highPriorityCounter;
		else if (!_taskQueue[NORMAL].empty()) {
			p = NORMAL;
			_highPriorityCounter = 0;
		}
	}
	else if (!_taskQueue[NORMAL].empty()) {
		p = NORMAL;
		_highPriorityCounter = 0;
	}
	else if (!_taskQueue[LOW].empty())
		p = LOW;

	task = _taskQueue[p].back();

	_taskQueue[p].pop_back();

	return task;
}
