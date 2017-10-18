/*
 * Acceptor.h
 *
 * Слушающий сокет и распределение новых подключений по потокам
 *
 *  Created on: 14.10.2010
 *      Author: knight
 */

#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_

//-
#include <vector>
//-
#include "segment.h"
//-

namespace web_server
{

	class Acceptor
	{
		static const size_t s_ConnectionPerThread; /**< количество подключений на нить */
		static const size_t s_MaxConnectionNum; /**< максимально допустимое количество подключений */

	public:
		/** констукртор */
		Acceptor();
		/** деструктор */
		~Acceptor();
		/** запуск сервера*/
		void start(const char * address, unsigned short port);

	protected:
		/** вставка нового подключения */
		void insert_new_connection(int sock);
		/** поиск свободного места в сегменте */
		int search_free_cell(Handle * handle);
		/** очистка всех сегментов */
		void clear_segments();

	private:
		network :: ServerSocket m_ListenSocket; /**< слушающий сокет */
		std :: vector<std :: pair<Segment *, Handle *> > m_ConnectionList; /** сегменты рабочих потоков и их матрицы */
		volatile bool m_Stop; /**< признак останова сервера */
	};

} /** namespace */

#endif /* ACCEPTOR_H_ */
