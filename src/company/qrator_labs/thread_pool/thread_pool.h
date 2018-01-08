/**
 * \file    ThreadPool.h
 * \brief
 * \details
 * \author  conquistador
 */
#ifndef THREAD_POOL_THREAD_POOL_H_
#define THREAD_POOL_THREAD_POOL_H_

//-
#include <cstddef>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/syscall.h>
//-
#include <boost/thread/thread.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/shared_ptr.hpp>
//-

namespace __details {
	class ITask {
	public:
		/**
		 * \brief Constructor
		 */
		ITask() {}

		/**
		 * \brief Destructor
		 */
		virtual ~ITask() {}

		/**
		 * \brief   Common interface
		 * \details 'do' is reserved word
		 */
		virtual void execute() = 0;
	};
} /** namespace __details */

class ThreadPool
{
public:
	enum Priority {
		HIGH,
		NORMAL,
		LOW,
		__MAX_PRIORITY
	};

	/**
	 * \brief Constructor takes thread workers quantity
	 */
	ThreadPool(std :: size_t quantity = 1);

	/**
	 * \brief Destructor
	 */
	virtual ~ThreadPool();

	/**
	 * \brief Enqueue task
	 * \todo  Queue size control
	 */
	bool enqueue(boost :: shared_ptr<__details :: ITask> task, Priority p);

	/**
	 * \brief Stop
	 */
	void stop();

protected:

	/**
	 * \brief   Schedule next task
	 * \warning NOT Thread safe
	 */
	boost :: shared_ptr<__details :: ITask> schedTask();

	/**
	 * \brief Worker thread
	 */
	void threadWork();

private:
	std :: list<boost :: shared_ptr<__details :: ITask> > _taskQueue[__MAX_PRIORITY];
	boost :: thread_group _workers;
	boost :: mutex _lock;
	boost :: interprocess::interprocess_semaphore _waitTaskSem;
	bool _stopped;
	std :: size_t _highPriorityCounter;
	//-
	static const std :: size_t HighPriorityLimit = 3;
};

#endif /* THREAD_POOL_THREAD_POOL_H_ */
