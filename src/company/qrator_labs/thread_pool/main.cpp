/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  conquistador
 */

#include <boost/make_shared.hpp>
//-
#include "thread_pool.h"

using namespace std;

#define WAIT_CLASS_PATTERN(usec) \
	class wait_##usec##_u : public __details :: ITask \
	{ \
		public: \
		wait_##usec##_u() {} \
		~wait_##usec##_u() {} \
		void execute() { stringstream os; os << "[" << syscall(SYS_gettid) << "]: " << __PRETTY_FUNCTION__ << endl; cout << os.str(); usleep(usec); } \
	};

WAIT_CLASS_PATTERN(500000);

WAIT_CLASS_PATTERN(250000);

WAIT_CLASS_PATTERN(100000);


int main(int argc, char *argv[])
{
	ThreadPool pool(3);

	// wait starting of each thread ???
	sleep(1);

	pool.enqueue(boost :: make_shared<wait_250000_u>(), ThreadPool :: NORMAL);

	pool.enqueue(boost :: make_shared<wait_250000_u>(), ThreadPool :: NORMAL);

	pool.enqueue(boost :: make_shared<wait_250000_u>(), ThreadPool :: NORMAL);

	pool.enqueue(boost :: make_shared<wait_500000_u>(), ThreadPool :: HIGH);

	pool.enqueue(boost :: make_shared<wait_250000_u>(), ThreadPool :: NORMAL);

	pool.enqueue(boost :: make_shared<wait_500000_u>(), ThreadPool :: HIGH);

	pool.enqueue(boost :: make_shared<wait_500000_u>(), ThreadPool :: HIGH);

	pool.enqueue(boost :: make_shared<wait_500000_u>(), ThreadPool :: HIGH);

	pool.enqueue(boost :: make_shared<wait_250000_u>(), ThreadPool :: NORMAL);

	pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	pool.enqueue(boost :: make_shared<wait_500000_u>(), ThreadPool :: HIGH);

	pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	pool.enqueue(boost :: make_shared<wait_500000_u>(), ThreadPool :: HIGH);

	pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	usleep(1500000);

	pool.stop();

	bool res = pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	assert(!res);

	res = pool.enqueue(boost :: make_shared<wait_100000_u>(), ThreadPool :: LOW);

	assert(!res);

	return 0;
}

