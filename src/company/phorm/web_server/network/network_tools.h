/*
 * network_tools.h
 *
 * Полезные функции для работы с сетью
 *
 *  Created on: 11.10.2010
 *      Author: knight
 */

#ifndef NETWORK_H_
#define NETWORK_H_

//-
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
//-
#include "http/http_answer_code.h"
//-

namespace network
{

	/** включить возможность повторного использования адреса */
	bool reuse_address_on(int sock);

	/** отказать в соединении */
	void reject_connection(int sock);

	/** задать неблокируемый режим */
	bool set_nonblocking_mode(int sock);

}

#endif /* NETWORK_H_ */
