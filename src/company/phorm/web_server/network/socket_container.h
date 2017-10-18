/*
 * SocketContainer.h
 *
 * Классы для работы с сокетом:
 * - серверная сторона
 * - клиентская сторона
 *
 *  Created on: 11.10.2010
 *      Author: knight
 */

#ifndef SOCKETCONTAINER_H_
#define SOCKETCONTAINER_H_

//-
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
//-
#include "network_tools.h"
#include "http/http_answer_code.h"
//-

namespace network
{
	/**
	 * Базовый класс сокета
	 */
	class Socket
	{
	public:
		/** конструктор */
		Socket();
		/** конструктор - принимающий дескриптор сокета */
		Socket(int sock);
		/** деструктор */
		~Socket();
		/** проверить валидность сокета */
		bool is_valid() { return (m_Socket != -1); }
		/** закрыть */
		void close();
		/** задать неблокируемый режим */
		bool set_nonblocking_mode();
		/** задать размер буфера для отправки */
		bool set_send_buf_size(size_t newSize);
		/** записать в сокет данные */
		int write(const void * data, size_t dataSz);

	protected:
		int m_Socket; /**< дескриптор сокета */
	};

	/**
	 * Серверная сторона сокета (TCP)
	 */
	class ServerSocket : public Socket
	{
	public:
		/** конструктор */
		ServerSocket();
		/** деструктор */
		~ServerSocket();
		/** начать прослушивание интерфейса */
		bool start_listen(const char * address, unsigned int port);
		/** вернуть следующее подключение из очереди ожидания */
		int get_next_connection();

	protected:

	private:
	};

	/**
	 * Клиентская сторона сокета
	 */
	class ClientSocket : public Socket
	{
	public:
		/** конструктор */
		ClientSocket();
		/** деструктор */
		~ClientSocket();
		/** задать дескриптор сокета */
		void set_socket_descriptor(int socketDesc);

	private:
	};

}

#endif /* SOCKETCONTAINER_H_ */
