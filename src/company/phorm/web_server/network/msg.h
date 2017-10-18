/*
 * Msg.h
 *
 * Сообщение для отправки данных
 * Хранит:
 * - сообщение
 *
 *
 *  Created on: 15.10.2010
 *      Author: knight
 */

#ifndef MSG_H_
#define MSG_H_

//-
#include <assert.h>
//-
//-

namespace network
{

	class Msg
	{
	public:
		/** конструктор */
		Msg();
		/** конструктор принимающий */
		Msg(char * data, unsigned int dataSz);
		/** деструктор */
		~Msg();
		/** очистка потока данных */
		inline void clear();
		/** вернуть указатель на начальный блок данных */
		char * data();
		/** вернуть длину для записи */
		unsigned int len();
		/** проверить остались ли данные для записи */
		bool is_empty();
		/** вычистить оставшиеся данные для записи */
		void calc_offset(unsigned int bytesWritten);

	private:
		char * m_Data; /**< поток данных */
		unsigned int m_Sz; /**< длина потока данных */
		unsigned int m_Offset; /**< смещение отправленных данных */
	};

	/** очистка потока данных */
	void Msg :: clear()
	{
		if (*m_Data)
		{
			delete [] m_Data;
			m_Data = 0;
		}
	}

} /** namespace */

#endif /* MSG_H_ */
