/*
 * Thread.cpp
 *
 *  Created on: 11.10.2010
 *      Author: knight
 */

#include "thread.h"

namespace thread
{

	/** конструктор */
	Thread :: Thread() :
		m_ThreadId(0)
	{
		pthread_mutex_init(&m_Mutex, 0);
	}

	/** деструктор */
	Thread :: ~Thread()
	{
		pthread_mutex_destroy(&m_Mutex);
	}

	/** вспомогательная функция потока */
	void * Thread :: start_routine(void * arg)
	{
		int old = 0;
		Thread * object = static_cast<Thread *>(arg);
		pthread_cleanup_push(cleanup_routine, object);
	    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old);
	    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old);
		object->run();
		pthread_cleanup_pop(1);
		return 0;
	}

	/** завершающая фукнция */
	void Thread :: cleanup_routine(void * arg)
	{
		Thread * object = static_cast<Thread *>(arg);
		pthread_mutex_lock(&object->m_Mutex);
		object->m_ThreadId = 0;
		pthread_mutex_unlock(&object->m_Mutex);
	}

} /** namespace */
