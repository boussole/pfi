/*
 * algorithm.h
 *
 * Алгоритмы дополняющие работу с stl строками
 *  Created on: 17.10.2010
 *      Author: knight
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

//-
#include <string>
#include <list>
//-
//-

namespace string_utils
{
	/** найти длину строки */
	template <typename T>
	size_t str_length(const T * str)
	{
		size_t len = 0;
		while (*str++)
		{
			len++;
		}
		return len;
	}

	/** расщепить строку по заданной последовательности */
	template <typename T>
	void split(const std :: basic_string<T> & str, std :: list<std :: basic_string<T> > & strList, const T * seq)
	{
		size_t old_pos = 0, pos = 0;
		size_t len = str_length(seq);
		bool found = false;
		while ((pos = str.find(seq, pos, len)) != std :: basic_string<T> :: npos)
		{
			if (old_pos != pos)
				{   strList.push_back(std :: basic_string<T>(str.substr(old_pos, pos - old_pos)));   }
			pos += len;
			old_pos = pos;
			found = true;
		}
		if (found)
		{
			if (old_pos != str.length())
				{   strList.push_back(std :: basic_string<T>(str.substr(old_pos, str.length() - old_pos)));   }
		}
		else if (!str.empty())
			{   strList.push_back(std :: basic_string<T>(str));   }
	}

} /** namespace */

#endif /* ALGORITHM_H_ */
