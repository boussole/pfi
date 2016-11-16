/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include <common/common.h>
#include "thread.h"

using namespace std;
using namespace conq_th;

/**********************************************************
 * \brief Using compare-and-swap create mutex (spinlock)
 **********************************************************/
TICKET_FN(70)
{
	cout << "#" << ticket << ": using compare-and-swap implement spinlock (mutex)\n";

	Spinlock<SpinlockCASImpl> s;

	bool res = false;

	// test 1: live lock, skip it
//	s.lock();
//	s.lock();

	// test 2: dual try lock, unlock
	res = s.tryLock();
	assert(res == true);
	res = s.tryLock();
	assert(res == false);
	s.unlock();

	// test 3: lock, tryLock, unlock
	s.lock();
	res = s.tryLock();
	assert(res == false);
	s.unlock();

	// test 4: assert
	// s.unlock();
}

/**********************************************************
 * \brief #276: Producer-Consumer problem
 **********************************************************/
TICKET_FN(276)
{
	cout << "#" << ticket << ": producer-consumer problem\n";

	if (argc < 5) {
		cout << "usage: " << *argv << " <producer quantity> <consumer quantity> <buffer size> <quantity>\n";
		return;
	}

	int p = atoi(argv[1]), c = atoi(argv[2]), bs = atoi(argv[3]), q = atoi(argv[4]);
	if (p <= 0 || c <= 0 || bs <= 0 || q <= 0) {
		cout << "invalid params, must be positive numbers only\n";
		return;
	}

	cout << "-------------------"
	     << "\nproducer = " << p << "\nconsumer = " << c << "\nbuffer size = " << bs << "\nquanity = " << q
		 << "\n-------------------\n";

	producer_consumer :: run(p, c, bs, q);
}

/**********************************************************
 * \brief #275: the Dining Philosophers problem
 **********************************************************/
TICKET_FN(275)
{
	cout << "#" << ticket << ": the dining philosophers problem\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <philosopher quantity>\n";
		return;
	}

	int q = atoi(argv[1]);
	if (q <= 1) {
		cout << "invalid input param\n";
		return;
	}

	philosophers :: run(q);
}

int main(int argc, char ** argv)
{
	ticket_275(argc, argv);

//	ticket_276(argc, argv);

//	ticket_70(argc, argv);

//	OrderThreadTask algo;
//
//	algo.doTask(argc, argv);

	return 0;
}


