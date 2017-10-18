/*
 * Handle.cpp
 *
 *  Created on: 12.10.2010
 *      Author: knight
 */

#include "handle.h"

namespace web_server
{
	/** конструктор */
	Handle :: Handle() : m_Socket(-1), m_State(Free)
	{

	}

	/** деструктор */
	Handle :: ~Handle()
	{
		close_socket();
	}

	/** выставить состояние "init" */
	void Handle :: set_init_state()
	{
		assert(m_State == Ready);
		m_State = Init;
	}

	/** прочитать данные из сокета */
	bool Handle :: read_incomming_data()
	{
		int bytes_num = read(m_Socket, m_Buffer, sizeof(m_Buffer));
		if (bytes_num > 0)
		{
			m_Request.add(m_Buffer, (size_t)bytes_num);
			std :: list<std :: string> * complete_request = 0;
			while ((complete_request = m_Request.get_first()))
			{
				m_Answer.make(*complete_request);
				if ((bytes_num = write(m_Socket, m_Answer.get(), m_Answer.length())) < 0)
				{
					return false;
				}
				m_Request.remove_first();
			}
			return true;
		}
		return false;
	}

	/** отправить данные в сокет */
	void Handle :: send_data()
	{

	}

	/** завершить работу с сокетом */
	void Handle :: close_socket()
	{
		close(m_Socket);
		m_Socket = -1;
		m_Buffer[0] = 0;
		m_State = Free;
		m_Request.clear();
		m_Answer.clear();
	}

	/** задать дескриптор сокета */
	void Handle :: set_socket_descriptor(int sock)
	{
		assert(m_State == Free);
		network :: set_nonblocking_mode(sock);
		m_Socket = sock;
		m_State = Ready;
	}

} /** namespace */
