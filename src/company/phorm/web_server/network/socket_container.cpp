/*
 * SocketContainer.cpp
 *
 *  Created on: 11.10.2010
 *      Author: knight
 */

#include "socket_container.h"

namespace network
{

	/**
	 *  Базовый класс сокета
	 */
	/** конструктор */
	Socket :: Socket() : m_Socket(-1)
	{

	}

	/** конструктор - принимающий дескриптор сокета */
	Socket :: Socket(int sock) : m_Socket(sock)
	{

	}

	/** деструктор */
	Socket :: ~Socket()
	{
		close();
	}

	/** задать дескриптор сокета */
	//void set_socket_descriptor(int socketDesc);

	/** закрыть */
	void Socket :: close()
	{
		if (is_valid())
		{
			::close(m_Socket);
			m_Socket = -1;
		}
	}

	/** задать неблокируемый режим */
	bool Socket :: set_nonblocking_mode()
	{
		if (is_valid())
		{
			return network::set_nonblocking_mode(m_Socket);
		}
		return false;
	}

	/** задать размер буфера для отправки */
	bool Socket :: set_send_buf_size(size_t newSize)
	{
		if (is_valid())
		{
			return !setsockopt(m_Socket, SOL_SOCKET, SO_SNDBUF, &newSize, sizeof(newSize));
		}
		return false;
	}

	/** записать в сокет данные */
	int Socket :: write(const void * data, size_t dataSz)
	{
		int retval = -1;
		if (is_valid())
		{
			retval = ::write(m_Socket, data, dataSz);
		}
		return retval;
	}

	/** конструктор */
	ServerSocket :: ServerSocket()
	{

	}

	/** деструктор */
	ServerSocket :: ~ServerSocket()
	{

	}

	/** начать прослушивание интерфейса */
	bool ServerSocket :: start_listen(const char * address, unsigned int port)
	{
		close();
		m_Socket = socket(AF_INET, SOCK_STREAM, 0);
		if (is_valid() && reuse_address_on(m_Socket))
		{
			struct sockaddr_in addr;
			memset(&addr, 0, sizeof(struct sockaddr_in));
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			if (inet_aton(address, &addr.sin_addr) &&
				!bind(m_Socket, (const struct sockaddr *)&addr, sizeof(const struct sockaddr)) &&
				!listen(m_Socket, 0))
			{
				return true;
			}
		}
		close();
		return false;
	}

	/** вернуть следующее подключение из очереди ожидания */
	int ServerSocket :: get_next_connection()
	{
		int result = -1;
		if (is_valid())
		{
			result = accept(m_Socket, 0, 0);
		}
		return result;
	}

	/*
	 * Клиентская сторона
	 */
	/** конструктор */
	ClientSocket :: ClientSocket()
	{
	}

	/** деструктор */
	ClientSocket :: ~ClientSocket()
	{

	}

	/** задать дескриптор сокета */
	void ClientSocket :: set_socket_descriptor(int socketDesc)
	{
		if (is_valid())
			{   close();   }
		m_Socket = socketDesc;
	}

}
