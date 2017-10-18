/*
 * test_network.h
 *
 *  Created on: 11.10.2010
 *      Author: knight
 */

#ifndef TEST_NETWORK_H_
#define TEST_NETWORK_H_

#include "socket_container.h"
#include "msg.h"

void test_listen()
{
	network :: ServerSocket sock;
	sock.start_listen("172.16.1.234", 12006);
	int new_sock = sock.get_next_connection();
	network :: reject_connection(new_sock);
}


void test_msg()
{
	char st[] = "preved_medved";
	char * tmp = new char[strlen(st) + 1];
	strcpy(tmp, st);
	network :: Msg msg(tmp, strlen(tmp));
	printf("%s - %d\n", msg.data(), msg.len());
	msg.calc_offset(2);
	printf("is_empty: %d\n", msg.is_empty());
	printf("%s - %d\n", msg.data(), msg.len());
	msg.calc_offset(12);
	printf("is_empty: %d\n", msg.is_empty());
}

#endif /* TEST_NETWORK_H_ */
