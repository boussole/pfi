/*
 * Answer.cpp
 *
 *  Created on: 17.10.2010
 *      Author: knight
 */

#include "answer.h"

namespace http
{
	const char Answer :: s_RootDir[] = ".";
	const char Answer :: s_GetRequest[] = "GET";
	const size_t Answer :: s_GetRequestLen = sizeof(s_GetRequest) - 1;

	/** конструктор */
	Answer :: Answer() :
		m_Answer(0),
		m_Length(0)
	{

	}

	/** деструктор */
	Answer :: ~Answer()
	{
		clear();
	}

	/** сформировать ответ */
	void Answer :: make(const request_list & request)
	{
		std :: string filename;
		clear();
		if (search_get_request(request, filename))
		{
			if (filename == "./")
				{   create_empty();   }
			else
				{   create(filename);   }
		}
		else
			{   CREATE_ANSWER(s_400_Bad_Request, m_Answer, m_Length);   }
	}

	/** поиск запроса GET */
	bool Answer :: search_get_request(const request_list & request, std :: string & fileName)
	{
		bool result = false;
		request_list ::const_iterator it = request.begin();
		while (it != request.end())
		{
			if (!it->compare(0, s_GetRequestLen, s_GetRequest) && extract_filename(*it, fileName))
			{
				prepare_filename(fileName);
				result = true;
				break;
			}
		}
		return result;
	}

	/** извлечь имя запрашиваемого файла */
	bool Answer :: extract_filename(const std :: string & str, std :: string & fileName)
	{
		std :: list<std :: string> list;
		string_utils :: split(str, list, " ");
		if (list.size() == 3)
		{
			list.pop_front();
			fileName = list.front();
			return true;
		}
		return false;
	}

	/** подготовить аргумент */
	void Answer :: prepare_filename(std :: string & fileName)
	{
		fileName.insert(0, s_RootDir);
		// удалить двойные точки и другое
	}

	/** создать пустой ответ */
	void Answer :: create_empty()
	{
		assert(m_Answer == 0);
		m_Answer = new char[sizeof(s_200_Ok) + sizeof(s_ItWorksMsg) + 10]; // число 10 с запасом на длину содержимого
		m_Length = sprintf(m_Answer, s_200_Ok, (sizeof(s_ItWorksMsg) - 1));
		strcat(m_Answer, s_ItWorksMsg);
		m_Length += sizeof(s_ItWorksMsg) - 1;
	}

	/** создать ответ на основании файла */
	void Answer :: create(std :: string & fileName)
	{
		assert(m_Answer == 0);
		FILE * file_stream = 0;
		int file_size = -1;
		if ((file_stream = fopen(fileName.c_str(), "r")))
		{
			if ((file_size = filesystem:: get_file_size(fileName.c_str())) != -1)
			{
				m_Answer = new char [sizeof(s_200_Ok) + file_size + 10]; // 10 на размер файла
				m_Length = sprintf(m_Answer, s_200_Ok, file_size);
				if (fread(&m_Answer[m_Length], 1, file_size, file_stream) == (size_t)file_size)
				{
					m_Length += file_size;
					fclose(file_stream);
					goto l_AnswerCreateExit;
				}
			}
			fclose(file_stream);
		}
		clear();
		CREATE_ANSWER(s_404_Not_Found, m_Answer, m_Length);
		l_AnswerCreateExit:;
	}

} /** namespace */
