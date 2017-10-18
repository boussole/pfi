/*
 * network_tools.cpp
 *
 *  Created on: 11.10.2010
 *      Author: knight
 */

//-
#include "network_tools.h"
//-

namespace network
{

	/** включить возможность повторного использования адреса */
	bool reuse_address_on(int sock)
	{
		int i = 1;
		return !setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
	}

	/** отказать в соединении */
	void reject_connection(int sock)
	{
		write(sock, http :: s_503_Service_Unavialable, sizeof(http :: s_503_Service_Unavialable) - 1);
		close(sock);
	}

	/** задать неблокируемый режим */
	bool set_nonblocking_mode(int sock)
	{
		bool result = false;
		int flags = fcntl(sock, F_GETFL, 0);
		if (flags != -1)
		{
			result = fcntl(sock, F_SETFL, flags | O_NONBLOCK);
		}
		return result;
	}
}
