/*
 * Acceptor.cpp
 *
 *  Created on: 14.10.2010
 *      Author: knight
 */

#include "acceptor.h"

namespace web_server
{
	const size_t Acceptor :: s_ConnectionPerThread = 1;
	const size_t Acceptor :: s_MaxConnectionNum = 3; // услоно, можно вынести как настроечную опцию

	/** констукртор */
	Acceptor :: Acceptor() : m_Stop(false)
	{
	}

	/** деструктор */
	Acceptor :: ~Acceptor()
	{
		clear_segments();
	}

	/** запуск сервера*/
	void Acceptor :: start(const char * address, unsigned short port)
	{
		if (m_ListenSocket.start_listen(address, port))
		{
			int new_sock = -1;
			do {
				new_sock = m_ListenSocket.get_next_connection();
				insert_new_connection(new_sock);
			} while (!m_Stop && (new_sock != -1));
		}
	}

	/**
	 *  вставка нового подключения
	 *  - поиск наименее загруженной нити
	 *  - в случае отсутствия свободных мест обслуживания, создание нового сегмента
	 *  - в случае ограничения количества сегментов, отказ в обслуживании
	 */
	void Acceptor :: insert_new_connection(int sock)
	{
		int segment_num = -1;
		size_t free_cell_num = 0;
		for (size_t i = 0; i < m_ConnectionList.size(); i++)
		{
			if (m_ConnectionList[i].first->free_cell_num() > free_cell_num)
			{
				free_cell_num = m_ConnectionList[i].first->free_cell_num();
				segment_num = i;
			}
		}
		// создание нового сегмента обслуживания
		if (segment_num == -1)
		{
			if (m_ConnectionList.size() < s_MaxConnectionNum)
			{
				Handle * handle = new Handle[s_ConnectionPerThread];
				m_ConnectionList.push_back(std :: pair<Segment *, Handle *>(new Segment(handle, s_ConnectionPerThread), handle));
				m_ConnectionList.back().first->start();
				segment_num = m_ConnectionList.size() - 1;
			}
			else
				{   network :: reject_connection(sock); return;   }
		}
		int cell_num = search_free_cell(m_ConnectionList[segment_num].second);
		assert(cell_num != -1);
		m_ConnectionList[segment_num].second[cell_num].set_socket_descriptor(sock);
	}

	/** поиск свободного места в сегменте */
	int Acceptor :: search_free_cell(Handle * handle)
	{
		int handle_index = -1;
		for (size_t i = 0; i < s_ConnectionPerThread; i++)
		{
			if (handle[i].state() == Handle :: Free)
			{
				handle_index = i;
				break;
			}
		}
		return handle_index;
	}

	/** очистка всех сегментов */
	void Acceptor :: clear_segments()
	{
		for (size_t i = 0; i < m_ConnectionList.size(); i++)
		{
			m_ConnectionList[i].first->stop();
			m_ConnectionList[i].first->wait();
			delete m_ConnectionList[i].first;
			delete [] m_ConnectionList[i].second;
			m_ConnectionList[i].second = 0;
		}
		m_ConnectionList.clear();
	}

} /** namespace */
