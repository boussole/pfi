/*
 * Segment.h
 *
 * Класс поток, хранит определенное количество сокетов, обслуживая их
 *
 *  Created on: 12.10.2010
 *      Author: knight
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

//-
#include <sys/epoll.h>
#include <assert.h>
//-
#include "thread/thread.h"
#include "handle.h"
//-

namespace web_server
{

	class Segment : public thread :: Thread
	{
		static const size_t s_EpollTimeout; /**< время ожидания событий в миллисекундах */

	public:
		/** конструктор */
		Segment(Handle * handleList, size_t segmentSize);
		/** деструктор */
		~Segment();
		/** вернуть количество свободных ячеек */
		size_t free_cell_num() { /** mutex */ return m_FreeCellNum; }

	protected:
		/** дочерняя нить */
		void run();
		/** обработка чтения */
		void do_read(Handle * handle);
		/** обработка записи */
		void do_write(Handle * handle);
		/** обработка закрытия */
		void do_close(Handle * handle);
		/** проверить новые подключения */
		void check_new_connections();
		/** ожидать события */
		void wait_event();

	private:
		const size_t m_SegmentSize; /**< размер сегмента */
		//-
		Handle * m_HandleList; /**< описатели сегмента подключений */
		int m_EpollHandle; /**< описатель epoll */
		struct epoll_event * m_Events; /**< структура с событиями */
		volatile size_t m_FreeCellNum; /**< количество свободных ячеек в сегменте */
		volatile bool m_Stop; /**< признак выхода из потока */
	};

}

#endif /* SEGMENT_H_ */
