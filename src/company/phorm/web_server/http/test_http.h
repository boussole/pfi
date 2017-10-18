/*
 * test_http.h
 *
 *  Created on: 17.10.2010
 *      Author: knight
 */

#ifndef TEST_HTTP_H_
#define TEST_HTTP_H_

#include "http/request.h"

void test_http_request()
{
	http :: Request r;
	const char t[] = "preved\r\nmedved\r\n\r\npoka\r\nmedved\r\n";
	r.add((char *)t, sizeof(t) - 1);
}


#endif /* TEST_HTTP_H_ */
