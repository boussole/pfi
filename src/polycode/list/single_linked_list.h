/*
 * \file    single_linked_list.h
 * \brief
 * \details
 * \author  boussole
 */

#ifndef SINGLE_LINKED_LIST_H_
#define SINGLE_LINKED_LIST_H_

#include <common/common.h>
#include <unordered_map>
#include <boost/function.hpp>

namespace conq_list {

template <typename T>
class SingleLinkedList {
public:
	template <typename U>
	struct Unit {
		Unit() : value(U()), next(nullptr) {}
		Unit(U v) : value(v), next(nullptr) {}
		U value;
		Unit<U> * next;
	};

	typedef Unit<T> _Node;

	SingleLinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}

	// SingleLinkedList(const SingleLinkedList<T> & rhs) {}

	~SingleLinkedList() { clear(); }

	void pushHead(const T & value);

	void pushTail(const T & value);

	bool isEmpty() { return _head == nullptr; }

	void clear();

	template <class Function>
	void forEach(Function fn);

	//SingleLinkedList & operator==(const SingleLinkedList<T> & rhs) {}

	/********************************************
	 * \brief #41: Revert
	 *******************************************/
	void revert();

	/********************************************
	 * \brief #226: Swap neighbours
	 *******************************************/
	void swapNeighbours();

	/********************************************
	 * \brief #227: Find loop, start of loop and len of loop
	 ********************************************/
	static bool findLoop(const _Node * head, _Node *& loop, std :: size_t & loopLen);

	/********************************************
	 * \brief #61: Common part of two single linked lists
	 ********************************************/
	static _Node * findCommonPart(const _Node * l1, const _Node * _l2);

	/********************************************
	 * \brief           #95: Merge sorted lists
	 * \details         in1 and in2 are merged into 'merged' and cleared after call
	 * \param [in, out] in1
	 * \param [in, out] in2
	 * \param [out]     merged
	 *******************************************/
	template <typename Compare>
	static void mergeSortedLists(SingleLinkedList<T> & in1, SingleLinkedList<T> & in2, SingleLinkedList<T> & merged, const Compare & cmp);

	/*******************************************
	 * \brief #232: Merge sort (natural merge)
	 *******************************************/
	template <typename Compare>
	void sortNaturalMerge(Compare cmp = Compare());

	/*******************************************
	 * \brief #232: Merge sort
	 *******************************************/
	template <typename Compare>
	void sortMerge(Compare cmp = Compare());

protected:
	/*******************************************
	 * \brief Merge two lists
	 * \note  List shouldn't be empty
	 *******************************************/
	template <typename Compare> inline
	Unit<T> * merge(Unit<T> * l, Unit<T> * le, Unit<T> * r, Unit<T> *& re, Compare cmp = Compare())
	{
		Unit<T> * list = nullptr, * iterator = nullptr, * last = re->next;

		if (!cmp(r->value, l->value)) {
			list = l;
			l = l->next;
		}
		else {
			list = r;
			r = r->next;
		}

		iterator = list;

		while ((l != le->next) && (r != re->next)) {
			if (!cmp(r->value, l->value)) {
				iterator->next = l;
				iterator = iterator->next;
				l = l->next;
			} else {
				iterator->next = r;
				iterator = iterator->next;
				r = r->next;
			}
		}

		// residue
		if (l != le->next) {
			iterator->next = l;
			le->next = last;
			re = le;
		} else
			iterator->next = r;

		return list;
	}

private:
	Unit<T> * _head, * _tail;
	int _size;
};

template <typename T>
void SingleLinkedList<T> :: pushHead(const T & value)
{
	Unit<T> * new_unit = new Unit<T>(value);
	BOOST_ASSERT(new_unit);
	new_unit->next = _head;
	_head = new_unit;

	if (!_tail) {
		_tail = _head;
	}

	++_size;
}

template <typename T>
void SingleLinkedList<T> :: pushTail(const T & value)
{
	Unit<T> * new_unit = new Unit<T>(value);
	BOOST_ASSERT(new_unit);

	if (!_tail) {
		_head = _tail = new_unit;
	} else {
		_tail->next = new_unit;
		_tail = new_unit;
	}

	++_size;
}

template <typename T>
void SingleLinkedList<T> :: clear()
{
	while (_head) {
		Unit<T> * del_unit = _head;
		_head = _head->next;
		delete(del_unit);
	}

	_tail = nullptr;
	_size = 0;
}

template <typename T>
	template <class Function>
void SingleLinkedList<T> :: forEach(Function fn)
{
	Unit<T> * iterator = _head;

	while (iterator) {
		fn(iterator->value);
		iterator = iterator->next;
	}
}

/********************************************
 * \brief #41: Revert
 *******************************************/
template <typename T>
void SingleLinkedList<T> :: revert()
{
	if (_head == _tail) { return; }

	_tail = _head;

	Unit<T> * new_head = _head;

	while (_head->next) {
		Unit<T> * tmp = _head->next;
		_head->next = _head->next->next;
		tmp->next = new_head;
		new_head = tmp;
	}

	_head = new_head;
}

/********************************************
 * \brief #226: swap neighbours
 *******************************************/
template <typename T>
void SingleLinkedList<T> :: swapNeighbours()
{
	if (_head == _tail) return;

	Unit<T> fake;
	Unit<T> * cur = _head, * pcur = &fake; /** trick for first iteration */

	std :: size_t pos = 0;

	_head = _head->next;

	while (cur->next) {
		if ((pos % 2) == 0) {
			Unit<T> * next = cur->next;
			cur->next = cur->next->next;
			next->next = cur;
			pcur->next = next;
			pcur = cur;
		}
		else
			cur = cur->next;

		pos++;
	}

	_tail = cur;
}

/*******************************************
 * \brief           #95: Merge sorted lists
 * \details         in1 and in2 are merged into 'merged' and cleared after call
 * \param [in, out] in1
 * \param [in, out] in2
 * \param [out]     merged
 *******************************************/
template <typename T>
	template <typename Compare>
void SingleLinkedList<T> :: mergeSortedLists(SingleLinkedList<T> & in1, SingleLinkedList<T> & in2, SingleLinkedList<T> & merged, const Compare & cmp)
{
	SingleLinkedList<T> * candidate = &in1;

	if (!in2.isEmpty()) {
		if (in1.isEmpty() || cmp(in2._head->value, in1._head->value))
			candidate = &in2;
	}

	if (!candidate->isEmpty()) {
		merged._head = candidate->_head;
		candidate->_head = candidate->_head->next;
		merged._head->next = nullptr;
		merged._tail = merged._head;
	}

	while (!in1.isEmpty() && !in2.isEmpty()) {
		candidate = (cmp(in1._head->value, in2._head->value) ? &in1 : &in2);
		merged._tail->next = candidate->_head;
		merged._tail = merged._tail->next;
		candidate->_head = candidate->_head->next;
		merged._tail->next = nullptr;
	}

	if (!in1.isEmpty()) {
		merged._tail->next = in1._head;
		in1._head = nullptr;
	}

	if (!in2.isEmpty()) {
		merged._tail->next = in2._head;
		in2._head = nullptr;
	}

	in1._tail = nullptr;
	in2._tail = nullptr;

	merged._size = in1._size + in2._size;
	in1._size = in2._size = 0;
}

/*******************************************
 * \brief #232: Merge sort (natural merge)
 *******************************************/
template <typename T>
	template <typename Compare>
void SingleLinkedList<T> :: sortNaturalMerge(Compare cmp)
{
	bool do_again = true;
	while (do_again) {
		Unit<T> * l = _head, * le = l, * prev = NULL;
		do_again = false;
		// search unsorted part
		while (le) {
			if (le->next && cmp(le->next->value, le->value)) {
				// search end of right stand unsorted part
				Unit<T> * r = le->next, * re = r;
				while (re->next && !cmp(re->next->value, re->value))
					re = re->next;

				Unit<T> * tail = re->next, * new_list = merge<Compare>(l, le, r, re);
				if (!prev)
					_head = new_list;
				else
					prev->next = new_list;

				_tail = prev = re;
				l = le = tail;
				do_again = true;
			}
			else {
				_tail = le;
				le = le->next;
			}
		}
	}
}

/*******************************************
 * \brief #232: Merge sort
 *******************************************/
template <typename T>
	template <typename Compare>
void SingleLinkedList<T> :: sortMerge(Compare cmp)
{
	std :: function<Unit<T>*(Unit<T>*, int)> sort = [&](Unit<T> * lst, int size) {
		BOOST_ASSERT(size >= 0);
		if (size <= 1)
			return lst;

		int piece = size / 2;
		Unit<T> * l = sort(lst, piece), * le = l;
		int counter = piece;
		while (--counter > 0)
			le = le->next;

		counter = size - piece;
		Unit<T> * r = sort(le->next, counter);
		_tail = r;
		while (--counter > 0)
			_tail = _tail->next;

		if (l && r)
			return merge(l, le, r, _tail, cmp);

		if (l) {
			_tail = le;
			return l;
		}
		else
			return r;
	};

	_head = sort(_head, _size);
}

/*******************************************
 *
 *******************************************/
//template <typename T>
//std::ostream& operator<<(std::ostream& ostr, const SingleLinkedList<T> & list)
//{
//    for (auto &i : list) {
//        ostr << " " << i;
//    }
//    return ostr;
//}

/***********************************************************
 * \brief  Filling of array from string where values are splitted by space
 * \return true in case of correct string | false in other case
 ***********************************************************/
static inline
bool fillFromString(SingleLinkedList<int> & lst, int size, char * str)
{
	std :: cout << "parse list [" << size << "] = " << str << std :: endl;

	int idx = 0;
	char * token = strtok(str, " \t");

	while (token) {
		if (idx == size) return false;
		lst.pushTail(atoi(token));
		idx++;
		token = strtok(nullptr, " \t");
	}

	return (idx == size);
}

/***********************************************************
 * \brief Test sorting order
 ***********************************************************/
template <typename T, typename Compare = std :: less<T> >
static inline
void testSortOrder(SingleLinkedList<T> & lst, const Compare & cmp = Compare())
{
	T const * prev = nullptr;

	lst.forEach(boost :: bind<void>(
		[&](const T & unit)->void {
			if (!prev)
				prev = &unit;
			else if (cmp(unit, *prev)) {
				std :: cout << "\ninvalid order => " << unit << " " << *prev << std :: endl;
				BOOST_ASSERT(false);
			}
		}, _1));
}

/********************************************
 * \brief #227: Find loop, start of loop and len of loop
 ********************************************/
template <typename T>
//	template <typename U>
bool SingleLinkedList<T> :: findLoop(const SingleLinkedList<T> :: _Node * head,
                                     SingleLinkedList<T> :: _Node *& loop, std :: size_t & loopLen)
{
	if (!head)
		return false;

	if (head->next == head) {
		loop = const_cast<SingleLinkedList<T> :: _Node *>(head);
		loopLen = 1;
		return true;
	}

	SingleLinkedList<T> :: _Node * fast = const_cast<SingleLinkedList<T> :: _Node *>(head);
	SingleLinkedList<T> :: _Node * slow = fast;

	// find loop fact
	while (true) {
		if ((fast->next == nullptr) || (fast->next->next == nullptr))
			return false;

		fast = fast->next->next;
		slow = slow->next;
		if (slow == fast)
			break;
	}

	// find start of loop
	for (loop = const_cast<SingleLinkedList<T> :: _Node *>(head);
	     loop != fast; loop = loop->next, fast = fast->next);
	for (slow = loop->next, loopLen = 1; slow != loop; slow = slow->next, ++loopLen);

	return true;
}

/********************************************
 * \brief #61: Common part of two single linked lists
 ********************************************/
template <typename T>
typename SingleLinkedList<T> :: _Node * SingleLinkedList<T> :: findCommonPart(
      const SingleLinkedList<T> :: _Node * l1, const SingleLinkedList<T> :: _Node * l2)
{
	if (!l1 || !l2)
		return nullptr;

	_Node * it1 = const_cast<_Node *>(l1), * res = nullptr;

	while (it1->next) {
		_Node * prev = it1;
		it1 = it1->next;
		prev->next = (_Node *)((std :: uintptr_t)prev->next | 1);
	}

	_Node * it2 = const_cast<_Node *>(l2);
	while (it2->next) {
		if ((std :: uintptr_t)it2->next & 1) {
			res = it2;
			break;
		}
		it2 = (_Node *)((std :: uintptr_t)it2->next & ~1);
	}

	if (!res && ((it2 == l1) || (it2 == it1))) {
		res = it1;
	}

	it1 = const_cast<_Node *>(l1);
	while (it1->next) {
		it1->next = (_Node *)((std :: uintptr_t)it1->next & ~1);
		it1 = it1->next;
	}

	return res;
}

template <typename T>
struct SingleLinkedListWithRandomPointer : public SingleLinkedList<T> :: _Node
{
	SingleLinkedListWithRandomPointer() : _random(nullptr)
	{}

	SingleLinkedListWithRandomPointer(const T & v) : SingleLinkedList<T> :: _Node(v), _random(nullptr)
	{}

	SingleLinkedListWithRandomPointer * _random;
};

/****************************************************************
 * \brief #34 Clone single linked list with
 ****************************************************************/
template <typename T>
void cloneSingleLinkedListWithRandomPointer(const SingleLinkedListWithRandomPointer<T> * orig, SingleLinkedListWithRandomPointer<T> *& clone)
{
	std :: unordered_map<std :: uint64_t, std :: uint64_t> tbl;

	const SingleLinkedListWithRandomPointer<T> * p = orig;
	SingleLinkedListWithRandomPointer<T> * p_cp = nullptr;

	while (p) {
		if (!clone) {
			clone = p_cp = new SingleLinkedListWithRandomPointer<T>(p->value);
			tbl.insert(std :: make_pair<std :: uint64_t, std :: uint64_t>((std :: uint64_t)p, (std :: uint64_t)p_cp));
		}
		else {
			std::unordered_map<std :: uint64_t, std :: uint64_t> :: const_iterator got = tbl.find((std :: uint64_t)p);

			if (got != tbl.end()) {
				p_cp->next = (SingleLinkedListWithRandomPointer<T> *)got->second;
			}
			else {
				p_cp->next = new SingleLinkedListWithRandomPointer<T>(p->value);
				tbl.insert(std :: make_pair<std :: uint64_t, std :: uint64_t>((std :: uint64_t)p, (std :: uint64_t)p_cp->next));
			}

			p_cp = static_cast<SingleLinkedListWithRandomPointer<int> *>(p_cp->next);
		}

		if (p->_random == p) {
			p_cp->_random = p_cp;
		}
		else {
			std :: unordered_map<std :: uint64_t, std :: uint64_t> :: const_iterator got = tbl.find((std :: uint64_t)p->_random);
			if (got != tbl.end()) {
				p_cp->_random = (SingleLinkedListWithRandomPointer<T> *)got->second;
			}
			else {
				p_cp->_random = new SingleLinkedListWithRandomPointer<T>(p->_random->value);
				tbl.insert(std :: make_pair<std :: uint64_t, std :: uint64_t>((std :: uint64_t)p->_random, (std :: uint64_t)p_cp->_random));
			}
		}

		p = static_cast<SingleLinkedListWithRandomPointer<int> *>(p->next);
	}
}

} /* namespace conq_list */

#endif /* SINGLE_LINKED_LIST_H_ */
