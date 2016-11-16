/**
 * \file    thread.h
 * \brief
 * \details
 * \author  boussole
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>
#include <iostream>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <boost/assert.hpp>
#include <memory>

/**
 * \namespace conq_th
 * \brief Thread data structures and tasks
 */
namespace conq_th {

/**
 * \class Spinlock basic
 */
class SpinlockInterface {
public:
	/**
	 * \brief Constructor
	 */
	SpinlockInterface(bool locked = false) {}

	/**
	 * \brief Destructor
	 */
	virtual ~SpinlockInterface() {}

	/**
	 * \brief Lock
	 */
	virtual void lock() = 0;

	/**
	 * brief Unlock
	 */
	virtual void unlock() = 0;

	/**
	 * \brief Try to lock without blocking
	 */
	virtual bool tryLock() = 0;
};

/**
 * \brief Spinlock using compare-and-swap (compare-and-set)
 */
class SpinlockCASImpl : public SpinlockInterface
{
public:
	SpinlockCASImpl(bool locked = false) : SpinlockInterface(locked), _lock(locked) {}

	~SpinlockCASImpl() {}

	/**
	 * \brief Lock
	 * \note  Also can be implemented through __sync_bool_compare_and_swap
	 */
	void lock()
	{
		while (__sync_val_compare_and_swap(&_lock, false, true))
//		while (__sync_bool_compare_and_swap(&_lock, false, true))
		{
			// we can sleep in case of mutex implementation
		}
	}

	/**
	 * brief Unlock
	 */
	void unlock()
	{
		bool locked = __sync_val_compare_and_swap(&_lock, true, false);
		assert(locked == true);
	}

	/**
	 * \brief Try to lock without blocking
	 */
	bool tryLock()
	{
		return (__sync_val_compare_and_swap(&_lock, false, true) == false);
	}

private:
	bool _lock;
};

template <class Impl>
class Spinlock : public Impl
{
public:
	/**
	 * \brief Constructor
	 */
	Spinlock(bool locked = false) : Impl(locked) {}

	/**
	 * \brief Destructor
	 */
	~Spinlock() {}
};


/**************************************************
 * \brief Producer-Consumer problem
 **************************************************/
namespace producer_consumer {
	void run(int producerQuantity, int consumerQuantity, int bufferSz, int quantity);
} /* namespace producer_consumer */

/**************************************************
 * \brief Dining philosopher problem
 **************************************************/
namespace philosophers {
	void run(int philosopherQuantity);
} /* namespace philosophers */

} /* namespace conq_th */

class ThreadTask {
public:
	ThreadTask() {}
	virtual ~ThreadTask()  {}
	virtual bool doTask(int argc, char ** argv) = 0;
};

/**
 * #85: thread order
 */
class OrderThreadTask : public ThreadTask
{
public:
	OrderThreadTask() {
		int res = sem_init(&_joiner, 0, 0); BOOST_ASSERT(res == 0);
		res = sem_init(&_starter, 0, 0); BOOST_ASSERT(res == 0);
	}
	~OrderThreadTask() { sem_destroy(&_joiner); sem_destroy(&_starter); }
	bool doTask(int argc, char ** argv);

private:
	static inline void usage(char * app) {
		std :: cout << "#85 \"thread order\" usage: " << app << " <thread num> <timeout sec>" << std :: endl;
	}

	/**
	 * pthread_cond method
	 */
	void doWithPthreadCond();

	/**
	 * pthread_join method
	 */
	void doWithPthreadJoin();

	struct WorkerCondArg {
		OrderThreadTask * me;
		int id;
	};

	static void * workerCond(void *);

	struct WorkerJoinArg {
		OrderThreadTask * me;
		pthread_t * th;
		int id;
	};
	static void * workerJoin(void *);

	int _threadNum;
	int _timeout;
	pthread_cond_t * _cond;
	pthread_mutex_t _mutex;
	sem_t _starter;
	sem_t _joiner;
};


#endif /* THREAD_H_ */
