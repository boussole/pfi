/*
 * Segment.cpp
 *
 *  Created on: 12.10.2010
 *      Author: knight
 */

#include "segment.h"

namespace web_server
{
	const size_t Segment :: s_EpollTimeout = 1000;

	/** конструктор */
	Segment :: Segment(Handle * handleList, size_t segmentSize) :
			m_SegmentSize(segmentSize),
			m_Stop(false)
	{
		assert(segmentSize > 0);
		m_HandleList = handleList;
		m_EpollHandle = epoll_create(m_SegmentSize);
		assert(m_EpollHandle >= 0);
		m_Events = new epoll_event[m_SegmentSize];
		m_FreeCellNum = m_SegmentSize;
	}

	/** деструктор */
	Segment :: ~Segment()
	{
		delete [] m_Events;
		close(m_EpollHandle);
	}

	/** дочерняя нить */
	void Segment :: run()
	{
		while (!m_Stop)
		{
			check_new_connections();
			wait_event();
		}
	}

	/** обработка чтения */
	void Segment :: do_read(Handle * handle)
	{
		if (!handle->read_incomming_data())
		{
			do_close(handle);
		}
	}

	/** обработка записи, только для незаписанных с первого раза данных */
	void Segment :: do_write(Handle * handle)
	{
		// отправить данные и проанализировать результат
		// если все данные отправлены, то правим режим epoll MOD
	}

	/** обработка закрытия */
	void Segment :: do_close(Handle * handle)
	{
		// epoll_ctl(EPOLL_CTL_DEL) не нужно, поскольку дескриптор удаляется из набора после закрытия
		assert(m_FreeCellNum < m_SegmentSize);
		handle->close_socket();
		m_FreeCellNum++;
	}

	/** проверить новые подключения */
	void Segment :: check_new_connections()
	{
		struct epoll_event event;
		for (size_t i = 0; i < m_SegmentSize; i++)
		{
			if (m_HandleList[i].state() == Handle :: Ready)
			{
				assert(m_FreeCellNum > 0);
				memset(&event, 0, sizeof(struct epoll_event));
				event.events = EPOLLIN | EPOLLHUP | EPOLLERR | EPOLLRDHUP;
				event.data.ptr = &m_HandleList[i];
				int result = epoll_ctl(m_EpollHandle, EPOLL_CTL_ADD, m_HandleList[i].socket_descriptor(), &event);
				assert(!result);
				m_HandleList[i].set_init_state();
				m_FreeCellNum--;
			}
		}
	}

	/** ожидать события */
	void Segment :: wait_event()
	{
		int ready_num = epoll_wait(m_EpollHandle, m_Events, m_SegmentSize, s_EpollTimeout);
		if (ready_num > 0)
		{
			for (int i = 0; i < ready_num; i++)
			{
				if (m_Events[i].events & EPOLLHUP || m_Events[i].events & EPOLLERR || m_Events[i].events & EPOLLRDHUP)
					{   do_close((Handle *)m_Events[i].data.ptr); continue;   }
				if (m_Events[i].events & EPOLLIN)
					{   do_read((Handle *)m_Events[i].data.ptr);   }
				if (m_Events[i].events & EPOLLOUT)
					{   do_write((Handle *)m_Events[i].data.ptr);  }
			}
		}
//		else if (ready_num == -1)
//			{   // обработка ошибки - EINTR }
	}

}
