/**
 * \file    priotity_queue.h
 * \brief
 * \details
 * \author  boussole
 */
#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <common/common.h>
#include <heap/heap.h>

namespace conq_queue {

template <typename T, typename Compare = std :: greater_equal<int> >
class PrioriryQueue : public conq_heap :: BinaryHeap<std :: pair<int, T> > {
	typedef std :: pair<int, T> _Unit;
	typedef conq_heap :: BinaryHeap<_Unit> _Parent;

	struct CompareUnit : public Compare {
		_GLIBCXX14_CONSTEXPR
		bool
		operator()(const _Unit & __x, const _Unit & __y) const
		{ return Compare :: operator()(__x.first, __y.first); }
	};

public:
	/**
	 * \brief Constructor
	 */
	PrioriryQueue(std :: size_t size) :
		_Parent(size) {}

	/**
	 * \brief Destructor
	 */
	~PrioriryQueue() {}

	/**
	 * \brief Check heap (debug only)
	 */
	void check() { _Parent :: check(CompareUnit()); }

	/**
	 * \brief Print elements (debug only)
	 */
	void print()
	{
		std :: cout << "priority queue:";
		for (std :: size_t i = 0; i < _Parent :: _filled; i++)
			std :: cout << " " << _Parent :: get()[i].second << "(" << _Parent :: get()[i].first << ");";
		std :: cout << std :: endl;
	}

	/**
	 * \brief Head element
	 */
	T & top()
	{
		assert(this->size() > 0);
		return this->get()[0].second;
	}

	/**
	 * \brief Enqueue value with priotity
	 */
	void enqueue(const T && value, int priority)
	{
		_Parent :: upHeap(*static_cast<_Parent *>(this), std :: make_pair(priority, value), CompareUnit());
	}

	/**
	 * \brief Dequeue head element
	 */
	void dequeue()
	{
		_Parent :: downHeap(*static_cast<_Parent *>(this), CompareUnit());
	}

	/** extention interfaces */

	/**
	 * \brief Change priority
	 */
	void changePriority(const T & value, int newPriority)
	{
		std :: size_t pos = find(value);
		if ((pos == this->size()) || (_Parent :: get()[pos].first == newPriority))
			return;

		int old_priority = _Parent :: get()[pos].first;

		_Parent :: get()[pos].first = newPriority;

		if (Compare()(old_priority, newPriority))
			_Parent :: restoreDownProperties(*static_cast<_Parent *>(this), pos, CompareUnit());
		else
			_Parent :: restoreUpProperties(*static_cast<_Parent *>(this), pos, CompareUnit());
	}

	/**
	 * \brief Remove value
	 */
	void remove(const T & value)
	{
		std :: size_t pos = find(value);
		if (pos == this->size())
			return;

		if (pos == _Parent :: _filled - 1) {
			--_Parent ::_filled;
			return;
		}

		_Parent :: restoreDownProperties(*static_cast<_Parent *>(this), pos, CompareUnit());
	}

protected:
	/**
	 * \brief  Find element
	 * \return Element index in heap array
	 * \todo   Use fast search (for example hash (element<->index) )
	 */
	std :: size_t find(const T & value)
	{
		std :: size_t pos;
		for (pos = 0; pos < this->size(); ++pos) {
			if (this->get()[pos].second == value)
				break;
		}

		return pos;
	}
};

} /* namespace conq_queue*/

#endif /* PRIORITY_QUEUE_H_ */
