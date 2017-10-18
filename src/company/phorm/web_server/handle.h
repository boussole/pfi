/*
 * Handle.h
 *
 * Описатель соединения, хранит подключение и буферы для него
 *
 * Заменой мьютексов для разграничения доступа к объекту Handle, используется
 * переменная целого типа State, которая гарантированно записывается целиком за
 * одну операцию на машинах x86/x86_64. Обязательным условием взаимодействия
 * потоков является изменение переменной m_State в конце всех операций.
 *
 *  Created on: 12.10.2010
 *      Author: knight
 */

#ifndef HANDLE_H_
#define HANDLE_H_

//-
#include <assert.h>
//-
#include "network/socket_container.h"
#include "http/request.h"
#include "http/answer.h"
//-

namespace web_server
{
	class Handle
	{
	public:
		enum State {
			Free = 0, // хендл пуст и готов для вставки
			Init,	// хендл занят
			Ready	// хендл занят, но не облуживается
		};
		/** конструктор */
		Handle();
		/** деструктор */
		~Handle();
		/** задать дескриптор сокета */
		void set_socket_descriptor(int sock);
		/** вернуть дескриптор сокета */
		int socket_descriptor() { return m_Socket; }
		/** состояние хендла */
		State state() { return m_State; }
		/** выставить состояние "init" */
		void set_init_state();
		/** прочитать данные из сокета */
		bool read_incomming_data();
		/** отправить данные в сокет */
		void send_data();
		/** завершить работу с сокетом */
		void close_socket();

	private:
		int m_Socket; /**< удаленное подключение */
		volatile State m_State; /**< состояние хендла */
		char m_Buffer[1042]; /**< внутренний буфер устройства */
		http :: Request m_Request; /**< обработчик запросов */
		http :: Answer m_Answer; /**< ответ */
		//std :: vector<Msg> m_SendMsgBuf; /**< буфер для отправления сообщений */
	};

}

#endif /* HANDLE_H_ */
