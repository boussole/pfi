/**
 * \file    thread.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include "thread.h"
//-
#include <sys/types.h>
#include <unistd.h>
#include <boost/scoped_array.hpp>
//-

namespace conq_th {

/**************************************************
 * \brief Producer-Consumer problem
 **************************************************/
namespace producer_consumer {

struct Arg {
	int _id, * _pos, _max;
	sem_t * _underrun, * _overrun, * _flag;
	pthread_mutex_t * _lock;
	std :: string * _buff;
};

void * producer_fn(void * arg)
{
	Arg * a = static_cast<Arg *>(arg);
//	std :: cout << "P" << a->_id << " started\n";
	sem_post(a->_flag);

	while (sem_wait(a->_overrun) == 0) {
		pthread_mutex_lock(a->_lock);
		if (*a->_pos < a->_max) {
			(*a->_buff)[(*a->_pos)++ % a->_buff->size()] = '+';
			std :: cout << "P" << a->_id << " " << *a->_buff << std :: endl;
			sem_post(a->_underrun);
		}
		else {
			std :: cout << "P" << a->_id << " finished\n"	;
			pthread_mutex_unlock(a->_lock);
			break;
		}

		pthread_mutex_unlock(a->_lock);
	}

	sem_post(a->_flag); // some producer stopped working

	return nullptr;
}

void * consumer_fn(void * arg)
{
	Arg * a = static_cast<Arg *>(arg);
//	std :: cout << "C" << a->_id << " started\n";
	sem_post(a->_flag);

	while (sem_wait(a->_underrun) == 0) {
		pthread_mutex_lock(a->_lock);
		if (*a->_pos < a->_max) {
			(*a->_buff)[(*a->_pos)++ % a->_buff->size()] = '-';
			std :: cout << "C" << a->_id << " " << *a->_buff << std :: endl;
			sem_post(a->_overrun);
		}
		else {
			std :: cout << "C" << a->_id << " finished\n";
			pthread_mutex_unlock(a->_lock);
			break;
		}

		pthread_mutex_unlock(a->_lock);
	}

	sem_post(a->_flag);	// some consumer stopped working

	return nullptr;
}

void run(int producerQuantity, int consumerQuantity, int bufferSz, int quantity)
{
	assert(producerQuantity > 0 && consumerQuantity > 0 && bufferSz > 0);

	sem_t underrun, overrun, flag;
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

	if (sem_init(&underrun, 0, 0)) {
		std :: cout << "fail to create underrun sem\n";
		return;
	}

	if (sem_init(&overrun, 0, static_cast<unsigned int>(bufferSz))) {
		sem_destroy(&underrun);
		std :: cout << "fail to create overrun sem\n";
		return;
	}

	if (sem_init(&flag, 0, 0)) {
		sem_destroy(&underrun);
		sem_destroy(&overrun);
		std :: cout << "fail to create flag sem\n";
		return;
	}

	std :: unique_ptr<pthread_t[]> producer(new pthread_t[producerQuantity]);
	std :: unique_ptr<Arg[]> producer_args(new Arg[producerQuantity]);
	std :: unique_ptr<pthread_t[]> consumer(new pthread_t[consumerQuantity]);
	std :: unique_ptr<Arg[]> consumer_args(new Arg[consumerQuantity]);

	std :: string buff(static_cast<std :: size_t>(bufferSz), '-');

	int res = 0, in = 0, out = 0;
	for (int i = 0; i < producerQuantity; ++i) {
		producer_args[i]._id = i;
		producer_args[i]._pos = &in;
		producer_args[i]._max = quantity;
		producer_args[i]._underrun = &underrun;
		producer_args[i]._overrun = &overrun;
		producer_args[i]._flag = &flag;
		producer_args[i]._lock = &lock;
		producer_args[i]._buff = &buff;
		res = pthread_create(&producer[i], nullptr, producer_fn, &producer_args[i]);
		assert(res == 0);
		sem_wait(&flag); // wait for creation of producer thread
	}

	for (int i = 0; i < consumerQuantity; ++i) {
		consumer_args[i]._id = i;
		consumer_args[i]._pos = &out;
		consumer_args[i]._max = quantity;
		consumer_args[i]._underrun = &underrun;
		consumer_args[i]._overrun = &overrun;
		consumer_args[i]._flag = &flag;
		consumer_args[i]._lock = &lock;
		consumer_args[i]._buff = &buff;
		int res = pthread_create(&consumer[i], nullptr, consumer_fn, &consumer_args[i]);
		assert(res == 0);
		sem_wait(&flag); // wait for creation of consumer thread
	}

	sem_wait(&flag); // wait finishing of some producer

	void * status = nullptr;
	// wake up other producers
	for (int i = 0; i < producerQuantity; ++i)
		sem_post(&overrun);

	for (int i = 0; i < producerQuantity; ++i)
		pthread_join(producer[i], &status);

	sem_post(&underrun);
	sem_wait(&flag); // wait finishing of some consumer

	// wake up other consumers
	for (int i = 0; i < consumerQuantity; ++i)
		sem_post(&underrun);

	for (int i = 0; i < consumerQuantity; ++i)
		pthread_join(consumer[i], &status);

	sem_destroy(&underrun);
	sem_destroy(&overrun);
	sem_destroy(&flag);
}

} /** namespace producer_consumer */

namespace philosophers {

using namespace std;

constexpr size_t MAX = 100;

struct philosopher {
	enum class state {
		no_fork,
		l_fork,
		r_fork,
		both_fork,
		__max_state
	};

	philosopher() : _s(state :: no_fork), _lFork(nullptr), _rFork(nullptr), _id(-1), _counter(0) {}

	state _s;

	pthread_mutex_t *_lFork, *_rFork;

	int _id;
	size_t _counter;
};

void * philosopher_fn(void *arg)
{
	philosopher *p = static_cast<philosopher *>(arg);

	string msg(to_string(p->_id));
	msg += ": hello\n";
	cout << msg.c_str();

	while (p->_s != philosopher :: state :: __max_state) {
		switch (p->_s) {
			case (philosopher :: state :: no_fork): {
				p->_s = philosopher :: state :: l_fork;
				pthread_mutex_lock(p->_lFork);
				break;
			}

			case (philosopher :: state :: l_fork): {
				if (pthread_mutex_trylock(p->_rFork) == 0) {
					p->_s = philosopher :: state :: both_fork;
				}
				else {
					pthread_mutex_unlock(p->_lFork);
					p->_s = philosopher :: state :: r_fork;
					pthread_mutex_lock(p->_rFork);
				}

				break;
			}

			case (philosopher :: state :: r_fork): {
				if (pthread_mutex_trylock(p->_lFork) == 0) {
					p->_s = philosopher :: state :: both_fork;
				}
				else {
					pthread_mutex_unlock(p->_rFork);
					p->_s = philosopher :: state :: l_fork;
					pthread_mutex_lock(p->_lFork);
				}

				break;
			}

			case (philosopher :: state :: both_fork): {
				msg = to_string(p->_id);
				msg += ": eating\n";
				cout << msg.c_str();
				p->_s = (++p->_counter < MAX) ? (philosopher :: state :: no_fork) : (philosopher :: state :: __max_state);
				pthread_mutex_unlock(p->_rFork);
				pthread_mutex_unlock(p->_lFork);
				break;
			}

			default: ;
		}
	}

	msg = to_string(p->_id);
	msg += ": good bye\n";
	cout << msg.c_str();

	return nullptr;
}

void run(int philosopherQuantity)
{
	assert(philosopherQuantity > 1);

	unique_ptr<pthread_mutex_t[]> forks = make_unique<pthread_mutex_t[]>(philosopherQuantity);

	unique_ptr<pthread_t[]> philosopher_th = make_unique<pthread_t[]>(philosopherQuantity);

	unique_ptr<philosopher[]> ph = make_unique<philosopher[]>(philosopherQuantity);

	for (int i = 0; i < philosopherQuantity; ++i) {
		ph[i]._lFork = &forks[i];
		ph[i]._rFork = &forks[(i + 1) % philosopherQuantity];
		ph[i]._id = i;
		cout << "[" << i << "] left = " << ph[i]._lFork << " right = " << ph[i]._rFork << endl;
		int res = pthread_create(&philosopher_th[i], nullptr, philosopher_fn, &ph[i]);
		assert(res == 0);
	}

	void *status = nullptr;
	for (int i = 0; i < philosopherQuantity; ++i)
		pthread_join(philosopher_th[i], &status);
}

} /** namespace philosophers */

} /** namespaec conq_th */

/* +++ #85: thread order  +++ */

bool OrderThreadTask :: doTask(int argc, char ** argv)
{
	if (argc < 3) {
		usage(*argv);
		return false;
	}

	_threadNum = atoi(argv[1]);
	_timeout = atoi(argv[2]);

	if (!_threadNum || !_timeout) {
		usage(*argv);
		return false;
	}

	doWithPthreadCond();
	doWithPthreadJoin();

	return true;
}

/**
 * pthread_cond method
 */
void OrderThreadTask :: doWithPthreadCond()
{
	int res = pthread_mutex_init(&_mutex, NULL);
	BOOST_ASSERT(res == 0);

	boost :: scoped_array<pthread_t> th(new pthread_t [_threadNum]);
	boost :: scoped_array<pthread_cond_t> cond(new pthread_cond_t [_threadNum + 1]); /** +1 for us */

	_cond = cond.get();

	boost :: scoped_array<WorkerCondArg> arg(new WorkerCondArg [_threadNum]);

	std :: cout << "#85 Thread order - cond: main thread pid = " << getpid() << std :: endl;

	/** _threadNum + 1 for parent thread */
	for (int i = 0; i < _threadNum + 1; i++) {
		res = pthread_cond_init(&cond[i], NULL);
		BOOST_ASSERT(res == 0);
	}

	for (int i = 0; i < _threadNum; i++) {
		arg[i].id = i;
		arg[i].me = this;
		res = pthread_create(&th[i], NULL, workerCond, &arg[i]);
		BOOST_ASSERT(res == 0);
	}

	std :: cout << "main thread wait child threads, pid = " << getpid() << std :: endl;
	/** wait while child thread acquire mutex */
	for (int i = 0; i < _threadNum; i++) {
		sem_wait(&_joiner);
	}

	/** wait while child threads go to sleep and release sem */
	pthread_mutex_lock(&_mutex);
	/** wake up thread number 0 */
	pthread_cond_signal(&cond[0]);
	std :: cout << "wait child threads, pid " << getpid() << std :: endl;
	/** release mutex and wait last thread */
	pthread_cond_wait(&cond[_threadNum], &_mutex);

	std :: cout << "wake up parent, pid " << getpid() << std :: endl;

	/** wait termination of all child threads */
	for (int i = 0; i < _threadNum; i++) {
		pthread_join(th[i], NULL);
		pthread_cond_destroy(&cond[i]);
	}

	pthread_cond_destroy(&cond[_threadNum]); /** parent cond */
	pthread_mutex_destroy(&_mutex);

	std :: cout << "main thread exit, pid = " << getpid() << std :: endl;
}

/**
 * pthread_join method
 */
void OrderThreadTask :: doWithPthreadJoin()
{
	std :: cout << "#85 Thread order - join: main thread pid = " << getpid() << std :: endl;

	boost :: scoped_array<pthread_t> th(new pthread_t [_threadNum]);
	boost :: scoped_array<WorkerJoinArg> arg(new WorkerJoinArg [_threadNum]);

	/** create threads and wait it start*/
	for (int i = 0; i < _threadNum; i++) {
		arg[i].me = this;
		arg[i].id = i;
		/*int res = */ pthread_create(&th[i], NULL, workerJoin, &arg[i]);
		sem_wait(&_joiner);
	}

	/** set waiters */
	arg[0].th = NULL;
	for (int i = 1; i < _threadNum; i++) {
		arg[i].th = &th[i - 1];
	}

	/** wake up childs */
	for (int i = 0; i < _threadNum; i++) {
		sem_post(&_starter);
	}

	/** wait all child threads */
	for (int i = 0; i < _threadNum; i++) {
		sem_wait(&_joiner);
	}

	std :: cout << "main thread exit,  pid = " << getpid() << std :: endl;
}

/**
 * thread func
 */
void * OrderThreadTask :: workerCond(void * a)
{
	WorkerCondArg * arg = static_cast<WorkerCondArg *>(a);
	OrderThreadTask * me = arg->me;
	int id = arg->id;

	std :: cout << "child thread pid = " << getpid() << " ( " << id << " )" << std :: endl;

	/** lock mutex */
	pthread_mutex_lock(&me->_mutex);
	/** notice parent about locked mutex */
	sem_post(&me->_joiner);
	/** unlock mutex and wait signal - notice another thread or parent about that */
	pthread_cond_wait(&me->_cond[id], &me->_mutex);

	int timeout = 0;

	while (timeout < me->_timeout) {
		std :: cout << "child thread is working now, pid = " << getpid() << " ( " << id << " )" << std :: endl;
		sleep(1);
		timeout++;
	}

	/** wake up next thread or parent */
	pthread_cond_signal(&me->_cond[id + 1]);
	/** release mutex */
	pthread_mutex_unlock(&me->_mutex);

	std :: cout << "child thread exit pid = " << getpid() << " ( " << id << " )" << std :: endl;

	return NULL;
}

void * OrderThreadTask :: workerJoin(void * a)
{
	WorkerJoinArg * arg = static_cast<WorkerJoinArg *>(a);

	OrderThreadTask * me = arg->me;

	std :: cout << "child thread has started, pid = " << getpid() << " ( " << arg->id << " )" << std :: endl;

	/** notice parent about self start */
	sem_post(&me->_joiner);

	/** wait next action from parent*/
	sem_wait(&me->_starter);

	/** only number 1 thread doesn't wait anyone */
	if (arg->th) {
		pthread_join(*arg->th, NULL);
	}

	int timeout = 0;

	while (timeout < me->_timeout) {
		std :: cout << "child thread is working now, pid = " << getpid() << " ( " << arg->id << " )" << std :: endl;
		sleep(1);
		timeout++;
	}

	std :: cout << "child thread exit, pid = " << getpid() << " ( " << arg->id << " )"  << std :: endl;

	sem_post(&me->_joiner);

	return NULL;
}

/* --- #85: thread order  --- */
