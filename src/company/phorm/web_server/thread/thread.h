/*
 * Thread.h
 * Класс для работы с потоком
 * Использование:
 * - создать новый класс наследник Thread
 * - перегрузить метод run у наследника
 * - запустить start()
 *
 *  Created on: 11.10.2010
 *      Author: knight
 */

#ifndef THREAD_H_
#define THREAD_H_

//-
#include <pthread.h>
//-
//-

namespace thread
{
	class Thread
	{
	public:
		/** конструктор */
		Thread();
		/** деструктор */
		~Thread();
		/** запустить поток на выполнение */
		inline bool start();
		/** остановить поток */
		inline bool stop();
		/** подождать поток */
		inline void wait() { pthread_join(m_ThreadId, 0); }

	protected:
		/** функция, которая должна выполняться в дочернем потоке */
		virtual void run() = 0;

	private:
		/** вспомогательная функция потока */
		static void * start_routine(void * arg);
		/** завершающая функция */
		static void cleanup_routine(void * arg);
		//-
		pthread_t m_ThreadId; /**< идентификатор нити */
		pthread_mutex_t m_Mutex; /**< доступ к объекту */
	};

	/** запустить поток на выполнение */
	inline bool Thread :: start()
	{
		bool result = false;
		pthread_mutex_lock(&m_Mutex);
		if (!m_ThreadId)
			{   result = !pthread_create(&m_ThreadId, 0, &start_routine, this);   }
		pthread_mutex_unlock(&m_Mutex);
		return result;
	}

	/** остановить поток */
	inline bool Thread :: stop()
	{
		bool result = false;
		pthread_mutex_lock(&m_Mutex);
		if (m_ThreadId)
			{   result = !pthread_cancel(m_ThreadId);   }
		pthread_mutex_unlock(&m_Mutex);
		return result;
	}

} /** namespace s*/

#endif /* THREAD_H_ */
