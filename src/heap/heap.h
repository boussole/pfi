/**
 * \file    binary_heap.h
 * \brief
 * \details
 * \author  boussole
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <common/common.h>

namespace conq_heap {

template <typename T>
class BinaryHeap {
public:
	/************************************
	 * \brief Constructor Create empty heap of size
	 ************************************/
	BinaryHeap(std :: size_t size) :
		_heap(new T[size]),
		_size(size),
		_filled(0) {}

	/*************************************
	 * \brief Constructor with external array
	 *************************************/
	template <typename Compare = std :: greater_equal<T> >
	BinaryHeap(T * arr, std :: size_t size, const Compare & cmp = Compare())
	{
		buildHeap(arr, size, *this, cmp);
	}

	/**
	 * \brief Destructor Free memory if it hasn't been released
	 */
	~BinaryHeap() {}

	/*************************************
	 * \brief create Create new heap
	 *************************************/
	void create(std :: size_t size)
	{
		_heap.reset(new T[size]);
		_size = size;
		_filled = 0;
	}

	/*************************************
	 * \brief parent Calculate parent node
	 *************************************/
	static int parent(int pos) { return (pos - 1) / 2;  }

	/*************************************
	 * \brief children Calculate left and right nodes
	 *************************************/
	static void children(int parent, int & left, int & right) { left = parent * 2 + 1; right = left + 1; }

	/*************************************
	 * \brief size Quantity of elements in heap
	 *************************************/
	std :: size_t size() { return _filled; }

	/*************************************
	 * \brief release Don't free memory in
	 *                destructor
	 *************************************/
	T * release() { _size = 0; _filled = 0; return _heap.release(); }

	/*************************************
	 * \brief check Check valid heap (debug only)
	 *************************************/
	template <typename Compare = std :: greater<T> >
	void check(const Compare & cmp = Compare())
	{
		for (int i = 0; i < static_cast<int>(_filled) / 2; i++) {
			int l = 0, r = 0;
			children(i, l, r);
			if (l < static_cast<int>(_filled))
				assert(cmp(_heap.get()[i], _heap.get()[l]) || (_heap.get()[i] == _heap.get()[l]));
			if (r < static_cast<int>(_filled))
				assert(cmp(_heap.get()[i], _heap.get()[r]) || (_heap.get()[i] == _heap.get()[r]));
		}
	}

	/*************************************
	 * \brief print Print as array (debug only)
	 *************************************/
	void print()
	{
		std :: cout << "binary heap:";
		for (int i = 0; i < static_cast<int>(_filled); i++)
			std :: cout << " " << _heap.get()[i];
		std :: cout << std :: endl;
	}

	/*************************************
	 * \brief upHeap Insert to binary heap (aka UP-HEAP)
	 *************************************/
	template <typename Compare = std :: greater_equal<T> >
	static void upHeap(BinaryHeap<T> & heap, const T && newUnit, const Compare & cmp = Compare())
	{
		assert(heap._filled < heap._size);

		T * mem = heap._heap.get();
		int pos = heap._filled++;

		mem[pos] = newUnit;

		restoreUpProperties(heap, pos, cmp);
	}

	/*************************************
	 * \brief downHeap Delete element from binary heap (aka DOWN-HEAP)
	 *************************************/
	template <typename Compare = std :: greater_equal<T> >
	static void downHeap(BinaryHeap<T> & heap, const Compare & cmp = Compare())
	{
		assert(heap._filled > 0);

		T * mem = heap._heap.get();

		mem[0] = mem[--heap._filled];

		restoreDownProperties(heap, 0, cmp);
	}

	/*************************************
	 * \brief build Build binary heap from array
	 *************************************/
	template <typename Compare = std :: greater_equal<T> >
	static void buildHeap(T * arr, std :: size_t size, BinaryHeap<T> & heap, const Compare & cmp = Compare())
	{
		heap._heap.reset(arr);
		heap._size = size;
		heap._filled = size;

		int leaf = size / 2;
		for (int base = leaf - 1; base >= 0; --base) {
			for (int candidate, right, nbase = base; nbase < leaf; nbase = candidate) {
				BinaryHeap<T> :: children(nbase, candidate, right);

				if ((right < static_cast<int>(size)) && (cmp(arr[right], arr[candidate])))
					candidate = right;

				if (cmp(arr[nbase], arr[candidate]))
					break;

				std :: swap(arr[nbase], arr[candidate]);
			}
		}
	}

	/**************************************
	 * \brief Data access
	 **************************************/
	T * get() { return _heap.get(); }

protected:
	/**
	 * \brief Fix properties from position to down
	 */
	template <typename Compare = std :: greater_equal<T> >
	static void restoreDownProperties(BinaryHeap<T> & heap, int pos, const Compare & cmp = Compare())
	{
		T * mem = heap._heap.get();

		for (int i = pos, candidate = 0, r = 0, leaf = heap._filled / 2; i < leaf; i = candidate) {
			BinaryHeap<T> :: children(i, candidate, r);
			if (r < static_cast<int>(heap._filled) && cmp(mem[r], mem[candidate]))
				candidate = r;

			if (cmp(mem[i], mem[candidate]))
				break;

			std :: swap(mem[i], mem[candidate]);
		}
	}

	/**
	 * \brief Fix properties from position to up
	 */
	template <typename Compare = std :: greater_equal<T> >
	static void restoreUpProperties(BinaryHeap<T> & heap, int pos, const Compare & cmp = Compare())
	{
		T * mem = heap._heap.get();
		int parent = BinaryHeap<T> :: parent(pos);

		while ((parent >= 0) && (!cmp(mem[parent], mem[pos]))) {
			std :: swap(mem[parent], mem[pos]);
			pos = parent;
			parent = BinaryHeap<T> :: parent(pos);
		}
	}

	std :: unique_ptr<T[]> _heap; /**< data storage */
	std :: size_t _size;          /**< size of data storage */
	std :: size_t _filled;        /**< quantity of elements in heap */
};

} /* namespace heap */

#endif /* HEAP_H_ */
