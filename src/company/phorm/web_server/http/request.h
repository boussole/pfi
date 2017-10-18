/*
 * Request.h
 *
 * Запрос html потока байтов
 * - хранит запросы
 * - ищет запросы в потоке постушающих байтов
 *
 *  Created on: 17.10.2010
 *      Author: knight
 */

#ifndef REQUEST_H_
#define REQUEST_H_

//-
#include <list>
#include <string>
//-
#include "string_utils/algorithm.h"
//-

namespace http
{

	class Request
	{
		static const char s_RequestSep[]; /**< разделитель запросов */
		static const size_t s_RequestSepLen;
		static const char s_RequestNewLine[]; /**< разделитель предолжений http */
	public:
		/** констурктор */
		Request();
		/** деструктор */
		~Request();
		/** добавить данные */
		void add(char * data, size_t dataSz);
		/** очистить объект */
		void clear();
		/** вернуть количество готовых запросов */
		size_t request_num() { return m_RequestList.size(); }
		/** вернуть первый готовый запрос */
		inline std :: list<std :: string> * get_first();
		/** удалить готовый запрос из начала списка */
		inline void remove_first();

	protected:
		/** поиск запросов */
		bool search_request();

	private:
	//public:
		std :: list<std :: list<std :: string> *> m_RequestList; /**< список готовых запросов */
		std :: string m_PreviousData; /**< данные пришедшие с предыдещих запросов */
	};

	/** вернуть первый готовый запрос */
	inline std :: list<std :: string> * Request :: get_first()
	{
		if (!m_RequestList.empty())
			{   return m_RequestList.front();   }
		return 0;
	}

	/** удалить готовый запрос из начала списка */
	inline void Request :: remove_first()
	{
		if (!m_RequestList.empty())
		{
			delete m_RequestList.front();
			m_RequestList.pop_front();
		}
	}

} /** namespace */

#endif /* REQUEST_H_ */
