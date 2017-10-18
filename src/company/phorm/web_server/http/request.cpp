/*
 * Request.cpp
 *
 *  Created on: 17.10.2010
 *      Author: knight
 */

#include "request.h"

namespace http
{

	const char Request :: s_RequestSep[] = "\r\n\r\n";
	const size_t Request :: s_RequestSepLen = sizeof(Request :: s_RequestSep) - 1;
	const char Request :: s_RequestNewLine[] = "\r\n";

	/** констурктор */
	Request :: Request()
	{

	}

	/** деструктор */
	Request :: ~Request()
	{
		clear();
	}

	/** добавить данные */
	void Request :: add(char * data, size_t dataSz)
	{
		m_PreviousData.append(data, dataSz);
		while (search_request())
		{
		}
	}

	/** поиск запросов */
	bool Request :: search_request()
	{
		size_t pos_start = m_PreviousData.find(s_RequestSep);
		if (pos_start != std :: string :: npos)
		{
			m_RequestList.push_back(new std :: list<std :: string>);
			string_utils :: split(m_PreviousData.substr(0, pos_start), *m_RequestList.back(), s_RequestNewLine);
			m_PreviousData.erase(0, pos_start + s_RequestSepLen);
			return true;
		}
		return false;
	}

	/** очистить объект */
	void Request :: clear()
	{
		std :: list<std :: list<std :: string> *> :: iterator it = m_RequestList.begin();
		while (it != m_RequestList.end())
		{
			delete *it;
			it++;
		}
		m_RequestList.clear();
		m_PreviousData.clear();
	}

} /** namespace */
