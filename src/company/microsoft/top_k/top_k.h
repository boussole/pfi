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
 * \file      top_k.h
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/

#ifndef TOP_K_H_
#define TOP_K_H_

#include <unordered_map>
#include <list>
#include <string>
#include <iostream>
#include <assert.h>

/**************************************************************************
 * \class   top_k
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
 *          Replace policy: fair
 *          This situation happens when storage is full.
 *          New element replaces the oldest element with lowest frequency
 *************************************************************************/

namespace __details {

/**
 * \brief   Frequency group structure
 * \details Contains frequence and list of strings in order of age: head = the youngest, tail = the oldest
 * \todo    Move it to __details namespace
 */
struct freq_grp {
	freq_grp(const std :: string &s) : _frequency(1), _s(1, s) {}
	freq_grp(int f, const std :: string &s) : _frequency(f), _s(1, s) {}
	//-
	std :: size_t _frequency;
	std :: list<std :: string> _s;
};

using groups = std :: list<freq_grp>;
using group_id = typename groups :: iterator;
using string_id   = typename std :: list<std :: string> :: const_iterator;

/**
 * \brief  Position of element (freq_grp + position in the list)
 * \todo   Move it to __details namespace
 */
struct position
{
	position() {}

	position(const position &rhs) :
	   _gid(rhs._gid),
	   _id(rhs._id) { }

	position(position &&rhs) :
	   _gid(std :: move(rhs._gid)),
	   _id(std :: move(rhs._id)) {}

	position(const group_id &gid, const string_id &id) :
	   _gid(gid),
	   _id(id) {}

	bool operator==(const position &rhs) const
	{ return _gid == rhs._gid && _id == rhs._id; }

	position & operator=(const position &rhs)
	{
		if (&rhs != this) {
			_gid = rhs._gid;
			_id = rhs._id;
		}

		return *this;
	}

	position & operator=(position && rhs)
	{
		if (&rhs != this) {
			_gid = std :: move(rhs._gid);
			_id = std :: move(rhs._id);
		}

		return *this;
	}

	//-
	group_id _gid;
	string_id _id;
};

} /** namespace top_k_details */

template <int K>
class top_k
{
	using h_tbl = std :: unordered_map<std :: string, __details :: position>;
	using h_tbl_unit = typename h_tbl :: iterator;

public:
	/**
	 * \brief   Iterator class
	 * \details Implemented basic methods only, very very FAST solution!!!
	 */
	class iterator
	{
	public:
		/**
		 * \brief Default constructor for user
		 */
		iterator()
		{}

		/**
		 * \brief Copy constructor
		 */
		iterator(const iterator &rhs) : _groups(rhs._groups)
		{
			if (this != &rhs)
				_pos = rhs._pos;
		}

		/**
		 * \brief Constructor for begin()
		 */
		iterator(__details :: groups &grps) : _groups(grps)
		{
			if (_groups.empty())
				_pos._gid = _groups.end();
			else {
				_pos._gid = _groups.begin();
				_pos._id = _groups.begin()->_s.begin();
			}
		}

		/**
		 * \brief Constructor for end()
		 */
		iterator(__details :: groups &grps, bool) : _groups(grps)
		{ _pos._gid = _groups.end(); }

		/**
		 * \brief Destructor
		 */
		~iterator()
		{}

		/**
		 * \brief Pre-increment
		 */
		iterator & operator++()
		{
			if (_pos._gid == _groups.end())
				return *this;

			++_pos._id;
			if (_pos._id != _pos._gid->_s.end())
				return *this;

			++_pos._gid;
			if (_pos._gid != _groups.end())
				_pos._id = _pos._gid->_s.begin();

			return *this;
		}

		/**
		 * \brief operator=
		 */
		iterator & operator=(const iterator &rhs)
		{
			if (&rhs != this) {
				_groups = rhs._groups;
				_pos = rhs._pos;
			}
			return *this;
		}

		/**
		 * \brief operator==
		 */
		bool operator==(const iterator &rhs) const
		{
			if (_pos._gid == rhs._pos._gid) {
				if (_pos._gid != _groups.end())
					return _pos._id == rhs._pos._id;
				else
					return true;
			}

			return false;
		}

		/**
		 * \brief operator!=
		 */
		bool operator!=(const iterator &rhs) const
		{ return !operator==(rhs); }

		/**
		 * \brief operator*
		 * \note  Unsafe
		 * \todo  Throw exception
		 */
		std :: string operator*()
		{ return *(_pos._id); }

	private:
		__details :: groups &_groups;
		__details :: position _pos;
	};

	/**
	 * \brief Constructor
	 */
	top_k() {}

	/**
	 * \brief Destructor
	 */
	virtual ~top_k() {}

	/**
	 * \brief Add new string
	 */
	virtual void add(const std :: string &s);

	/**
	 * \brief Clear internals
	 */
	virtual void clear() {
		_tbl.clear();
		_groups.clear();
	}

	/**
	 * \brief Print internals to std :: cout
	 * \note  Debug only
	 */
	virtual void debug();

	/**
	 * \brief Iterator to TOP element in k sequence
	 */
	iterator begin()
	{
		if (!_groups.empty())
			return iterator(_groups);
		return end();
	}

	/**
	 * \brief Iterator to elememnt after last
	 * \todo  Not ready
	 */
	iterator end()
	{ return iterator(_groups, false); }

protected:

	/**
	 * \brief  Return position of the oldest element
	 */
	__details :: position oldest() {
		assert(!_groups.empty());
		__details :: group_id gid = --_groups.end();
		__details :: string_id sid = --gid->_s.end();

		return __details :: position(gid, sid);
	}

	/**
	 * \brief   Force insert NEW string without respect to limit
	 * \details O(1) in average case
	 */
	void insert(const std :: string &s);

	/**
	 * \brief Replace the oldest element by new element
	 * \details O(1) - in average case
	 */
	virtual void replace(const std :: string &s);

	/**
	 * \brief   Update element with respect to new frequency
	 * \details O(1)
	 */
	void update(__details :: position &pos);

// private:
	h_tbl _tbl;
	__details :: groups _groups; /**< head = maximal frequence; tail = minimal. */
};

/**
 * \brief   Add new string
 * \details O(1) - in average case
 */
template <int k>
void top_k<k> :: add(const std :: string &s)
{
	assert(_tbl.size() <= k);

	// find string in hash table => O(1) - in average case
	h_tbl_unit u = _tbl.find(s);

	// it a new string
	if (u == _tbl.end()) {
		// storage isn't full
		if (_tbl.size() < k)
			insert(s);
		else
			replace(s);
	}
	// string exists in the storage
	else
		update(u->second);
}

/**
 * \brief   Force insert NEW string without respect to limit
 * \details O(1) in average case
 */
template <int k>
void top_k<k> :: insert(const std :: string &s)
{
	if (_groups.empty() || _groups.back()._frequency != 1) {
		// create group with frequence == 1 => O(1)
		_groups.emplace_back(__details :: freq_grp(s));
	}
	else {
		// add string to the head of list (NEW element) => O(1)
		_groups.back()._s.push_front(s);
	}

	__details :: group_id gid = --_groups.end();
	__details :: string_id sid = _groups.back()._s.cbegin();

	// insert new record to the hash table => O(1) - in average case
	bool ok = _tbl.insert({s, __details :: position(gid, sid)}).second;
	assert(ok); // :-)
}

/**
 * \brief Replace the oldest element by new element
 * \details O(1) in average case
 */
template <int k>
void top_k<k> :: replace(const std :: string &s)
{
	assert(_groups.size() > 0);

	// find the oldest element => O(1)
	// remove from hash table => O(1) in average case
	_tbl.erase(_groups.back()._s.back());

	// remove from frequency group => O(1)
	_groups.back()._s.pop_back();

	// frequency group is empty, remove it => O(1)
	if (_groups.back()._s.size() == 0)
		_groups.pop_back();

	insert(s);
}

/**
 * \brief   Update element with respect to new frequency
 * \details O(1)
 */
template <int k>
void top_k<k> :: update(__details :: position &pos)
{
	// this is maximal frequency group
	if (pos._gid == _groups.cbegin()) {
		// optimization: if we are alone, use the same group (changing frequency only)
		if (pos._gid->_s.size() == 1)
			++pos._gid->_frequency;
		// create new frequency group and delete old string from previous group (using iterator) = > O(1)
		else {
			_groups.push_front(__details :: freq_grp(pos._gid->_frequency + 1, *(pos._id)));
			pos._gid->_s.erase(pos._id);
			pos._gid = _groups.begin();
			pos._id = pos._gid->_s.cbegin();
		}
	}
	else {
		__details :: group_id next_gid = pos._gid;
		--next_gid;
		// we have a gap
		if (next_gid->_frequency != pos._gid->_frequency + 1) {
			// optimization: if we are alone, use the same group (changing frequency only)
			if (pos._gid->_s.size() == 1)
				++pos._gid->_frequency;
			else {
				next_gid = _groups.insert(pos._gid, __details :: freq_grp(pos._gid->_frequency + 1, *(pos._id)));
				pos._gid->_s.erase(pos._id);
				pos._gid = next_gid;
				pos._id = pos._gid->_s.cbegin();
			}
		}
		else {
			// next group is our
			next_gid->_s.push_front(*(pos._id));
			pos._gid->_s.erase(pos._id);
			pos._id = next_gid->_s.cbegin();
			// remove frequency group if it's empty => O(1)
			if (pos._gid->_s.size() == 0)
				_groups.erase(pos._gid);
			pos._gid = next_gid;
		}
	}
}

/**
 * \brief Print internals to std :: cout
 * \note  Debug only
 */
template <int k>
void top_k<k> :: debug()
{
	size_t quantity = 0;

	std :: cout << "---\n";
	for (auto &grp : _groups) {

		std :: cout << "freq = " << grp._frequency << " (size = " << grp._s.size() << "):";

		for (auto &i : grp._s) {
			std :: cout << " " << i;
			++quantity;
		}

		std :: cout << std :: endl;
	}

//	std :: cout << "tbl size = " << _tbl.size() << " quantity = " << quantity << std :: endl;

	assert(_tbl.size() == quantity);
}

#endif /* TOP_K_H_ */
