/*
 * test_thread.h
 *
 *  Created on: 11.10.2010
 *      Author: knight
 */

#ifndef TEST_THREAD_H_
#define TEST_THREAD_H_

//-
#include <unistd.h>
#include <stdio.h>
//-
#include "thread.h"
//-

#define TICK_COUNT 6

class MyThread : public thread :: Thread
{
public:
	MyThread() : m_Counter(TICK_COUNT) {}
	~MyThread() {}

protected:
	void run();
private:
	int m_Counter;
};

void MyThread :: run()
{
	while (m_Counter--)
	{
		printf("threadId: %d\n", pthread_self());
		sleep(2);
	}
}

void test_thread()
{
	MyThread my;
	my.start();
	int counter = 3;
	while (counter--)
	{
		printf("Wait thread\n");
		sleep(1);
	}
	printf("stoping\n");
	my.stop();
	printf("waiting\n");
	my.wait();
	printf("exit\n");
}

#endif /* TEST_THREAD_H_ */
