/*
 * main.cpp
 *
 *  Created on: 11.10.2010
 *      Author: knight
 */


//-
//#include "thread/test_thread.h"
//#include "network/test_network.h"
//#include "string_utils/test_string_utils.h"
//#include "http/test_http.h"

#include "main.h"
//-

int main(int argc, char ** argv)
{
	try
	{
		if (check_cmd_args(argc, argv))
			{   run(argv[1], atoi(argv[2]));   }
	}
	catch(...)
	{
		fprintf(stderr, "Exception catched\n");
	}
	fprintf(stderr, "Stoping web_server\n");
	return 0;
}

/** чтение параметров командной строки */
bool check_cmd_args(int argv, char ** argc)
{
	if (argv != 3)
	{
		usage(*argc);
		return false;
	}
	// можно добавить проверку адреса и порта
	return true;
}

/** запуск сервера */
void run(const char * address, unsigned short port)
{
	web_server :: Acceptor acceptor;
	acceptor.start(address, port);
}
