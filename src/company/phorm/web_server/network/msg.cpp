/*
 * Msg.cpp
 *
 *  Created on: 15.10.2010
 *      Author: knight
 */

#include "msg.h"

namespace network
{

	/** конструктор */
	Msg :: Msg() :
		m_Data(0),
		m_Sz(0),
		m_Offset(0)
	{

	}

	/** конструктор принимающий */
	Msg :: Msg(char * data, unsigned int dataSz) : m_Offset(0)
	{
		m_Data = data;
		m_Sz = dataSz;
	}

	/** деструктор */
	Msg :: ~Msg()
	{
		clear();
	}

	/** вернуть указатель на начальный блок данных */
	char * Msg :: data()
	{
		return &(m_Data[m_Offset]);
	}

	/** вернуть длину для записи */
	unsigned int Msg :: len()
	{
		return (m_Sz - m_Offset);
	}

	/** проверить остались ли данные для записи */
	bool Msg :: is_empty()
	{
		return (m_Offset >= m_Sz);
	}

	/** вычистить оставшиеся данные для записи */
	void Msg :: calc_offset(unsigned int bytesWritten)
	{
		m_Offset += bytesWritten;
		assert(m_Offset <= m_Sz);
	}

}
