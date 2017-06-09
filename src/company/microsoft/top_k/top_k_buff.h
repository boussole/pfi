/****************************************************************
 * Copyright (c) 2016 boussole (x dotty conquistador dotty x at gmail dotty com)
 * All rights reserved.
 *
 * This file is part of top_k.
 *
 * top_k is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * https://github.com/boussole/top_k
 *
 * \file      top_k_buff.h
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/

#ifndef TOP_K_BUFF_H_
#define TOP_K_BUFF_H_

// std
#include <queue>
// custom
#include "top_k.h"

/**************************************************************************
 * \class   top_k_buf
 *
 * \brief   This class collects strings in order of them frequencies.
 * \details Class has limited internal storage and new elements can replace
 *          old elements.
 *
 *          High frequency element stores at the top of queue.
 *
 *          In situation with more than one element with identical frequency
 *          last refreshed element has maximal priority.
 *
 *          Class has additional storage for statistic of a few (or more) last
 *          input elements
 *
 *          Replace policy: statistic
 *          This situation happens when storage is full.
 *          New element can replace the oldest element only if it has frequency
 *          in the buffer more the oldest element in storage
 *************************************************************************/

template <int k, int buff_size>
class top_k_buff: public top_k<k>
{
public:

	/**
	 * \breif Constructor
	 */
	top_k_buff() : _current_buff_freq(0) {}

	/**
	 * \brief Destructor
	 */
	virtual ~top_k_buff() {}

	/**
	 * \brief   Add new string
	 * \details O(1) - in average case
	 */
	virtual void add(const std :: string &s) override
	{
		_current_buff_freq = update_buff(s);

		top_k<k> :: add(s);
	}

	/**
	 * \brief Clear internals
	 */
	virtual void clear() override {
		top_k<k> :: clear();
		_buff = std :: queue<std :: string>();
		_current_buff_freq = 0;
	}

	/**
	 * \brief Print internals to std :: cout
	 * \note  Debug only
	 */
	virtual void debug() override;

protected:
	/**
	 * \brief   Replace the oldest element by new element with respect to buffer frequency
	 * \details O(1) - in average case
	 *          Trick: update the oldest element to move it to the next frequency group, then change it by new element
	 */
	virtual void replace(const std :: string &s) override
	{//	std :: cout << __PRETTY_FUNCTION__ << ": " << s << "(" << _current_buff_freq << ")" << std :: endl;
		if (top_k<k> :: _groups.back()._frequency < _current_buff_freq) {
			__details :: position pos(std :: move(top_k<k> :: oldest()));
			top_k<k> :: update(pos);
			// remove from hash table => O(1) in average case
			top_k<k> :: _tbl.erase(*(pos._id));
			// insert to hash table => O(1) in average case
			top_k<k> :: _tbl.insert({s, pos});
			// change top element in frequency group => O(1)
			pos._gid->_s.front() = s;
		}
	}

	/**
	 * \brief   Update buff
	 * \details O(1) - in average case
	 * \return  Counter of new buffered string
	 */
	std :: size_t update_buff(const std :: string &s)
	{
		assert(_counter_map.size() <= buff_size);

		std :: unordered_map<std :: string, size_t> :: iterator it;

		// queue is full, remove the oldest
		if (_buff.size() == buff_size) {
			std :: unordered_map<std :: string, size_t> :: iterator it = _counter_map.find(_buff.front());

			assert(it != _counter_map.end());

			if (--it->second == 0)
				_counter_map.erase(it);

			_buff.pop();
		}

		_buff.push(s);

		return ++_counter_map[s];
	}

private:
	std :: queue<std :: string> _buff; /**< use queue, like you told me */
	std :: unordered_map<std :: string, size_t> _counter_map; /** but if the buff is small, we can use linier search */
	std :: size_t _current_buff_freq;
};

/**
 * \brief Print internals to std :: cout
 * \note  Debug only
 */
template <int k, int buff_size>
void top_k_buff<k, buff_size> :: debug()
{
	top_k<k> :: debug();

	std :: queue<std :: string> q = _buff;

	std :: cout << "buf:";
	while (!q.empty()) {
		std :: cout << " " << q.front();
		q.pop();
	}

	std :: cout << std :: endl;
}

#endif /* TOP_K_BUFF_H_ */
