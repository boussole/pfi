/*
 * test_string_utils.h
 *
 *  Created on: 17.10.2010
 *      Author: knight
 */

#ifndef TEST_STRING_UTILS_H_
#define TEST_STRING_UTILS_H_

#include "algorithm.h"

void test_split()
{
	//std :: string str ("preved\r\ndrujog\r\npoka");
	//std :: string str ("preved\r\ndrujog\r\np");
	//std :: string str ("p\r\n");
	//std :: string str ("\r\n");
	//std :: string str ("\r\npreved");
	std :: string str ("preved");
	std :: list<std :: string> l;
	string_utils::split(str, l, "\r\n");
	std :: list<std :: string> :: iterator it = l.begin();
	while (it != l.end())
	{
		printf("String: %s\n", it->c_str());
		it++;
	}
}

void test_str_length()
{
	const char str[] = "wqer";
	printf("len: %d\n", string_utils:: str_length(str));
}

#endif /* TEST_STRING_UTILS_H_ */
