/*
 * main.h
 *
 *  Created on: 11.10.2010
 *      Author: knight
 */

#ifndef MAIN_H_
#define MAIN_H_

//-
#include <stdio.h>
#include <libgen.h>
#include <unistd.h>
#include <stdlib.h>
//-
#include "acceptor.h"
//-

/** запуск сервера */
void run(const char * address, unsigned short port);

/** чтение параметров командной строки */
bool check_cmd_args(int argv, char ** argc);

/** вывод помощи */
inline void usage(char * appName)
{
	fprintf(stderr, "Usage: %s <local interface address> <port number>\n", basename(appName));
}


#endif /* MAIN_H_ */
