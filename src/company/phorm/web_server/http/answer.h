/*
 * Answer.h
 *
 * Класс позволяет формировать html ответ от сервера на основании запроса
 *
 *  Created on: 17.10.2010
 *      Author: knight
 */

#ifndef ANSWER_H_
#define ANSWER_H_

//-
#include <string>
#include <list>
#include <assert.h>
#include <string.h>
#include <stdio.h>
//-
#include "http_answer_code.h"
#include "string_utils/algorithm.h"
#include "filesystem/file_utils.h"
//-

#define CREATE_ANSWER(text, buf, len) \
	buf = new char[sizeof(text)]; \
	strcpy(buf, text); \
	len = sizeof(text) - 1;

namespace http
{

	class Answer
	{
		typedef std :: list<std :: string> request_list;

		static const char s_RootDir[];
		static const char s_GetRequest[];
		static const size_t s_GetRequestLen;
	public:
		/** конструктор */
		Answer();
		/** деструктор */
		~Answer();
		/** сформировать ответ */
		void make(const request_list & request);
		/** вернуть ответ */
		const char * get() { return m_Answer; }
		/** вернуть длину ответа */
		size_t length() { return m_Length; }
		/** очистить внутренний буфер */
		inline void clear();

	protected:
		/** поиск запроса GET */
		bool search_get_request(const request_list & request, std :: string & fileName);
		/** извлечь имя запрашиваемого файла */
		bool extract_filename(const std :: string & str, std :: string & fileName);
		/** подготовить аргумент */
		void prepare_filename(std :: string & fileName);
		/** создать пустой ответ */
		void create_empty();
		/** создать ответ на основании файла */
		void create(std :: string & fileName);
		/** создать ответ, плохой запрос*/

	private:
		char * m_Answer; /**< строка с ответом */
		size_t m_Length; /**< длина строки с ответом */
	};

	/** очистить внутренний буфер */
	inline void Answer :: clear()
	{
		if (m_Answer)
		{
			delete [] m_Answer;
			m_Answer = 0;
			m_Length = 0;
		}
	}

}

#endif /* ANSWER_H_ */
