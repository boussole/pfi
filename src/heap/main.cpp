/**
 * \file    main.cpp
 * \brief   
 * \details 
 * \author  boussole
 */

#include "heap.h"

using namespace conq_heap;
using namespace std;

TICKET_FN(246)
{
	cout << "#" << ticket << ": binary heap\n";

	const int arr_sz = 8;

	// 11 5 8 3 4 15
	BinaryHeap<int> heap(arr_sz);
	heap.check();
	heap.print();
	BinaryHeap<int> :: upHeap(heap, 11);
	heap.check();
	heap.print();
	BinaryHeap<int> :: upHeap(heap, 5);
	heap.check();
	heap.print();
	BinaryHeap<int> :: upHeap(heap, 8);
	heap.check();
	heap.print();
	BinaryHeap<int> :: upHeap(heap, 3);
	heap.check();
	heap.print();
	BinaryHeap<int> :: upHeap(heap, 4);
	heap.check();
	heap.print();
	BinaryHeap<int> :: upHeap(heap, 15);
	heap.check();
	heap.print();
	// 15 5 11 3 4 8 12
	BinaryHeap<int> :: upHeap(heap, 12);
	heap.check();
	heap.print();
	// 15 5 12 3 4 8 12 4
	BinaryHeap<int> :: upHeap(heap, 4);
	heap.check();
	heap.print();

	// 15 5 12 4 4 8 11 3
	// delete 15
	BinaryHeap<int> :: downHeap(heap);
	heap.check();
	heap.print();

	// 12 5 11 4 4 8 3
	// delete 12
	BinaryHeap<int> :: downHeap(heap);
	heap.check();
	heap.print();

	// 11 5 8 4 4 3
	// delete 11
	BinaryHeap<int> :: downHeap(heap);
	heap.check();
	heap.print();

	// 8 5 3 4 4
	// delete 8
	BinaryHeap<int> :: downHeap(heap);
	heap.check();
	heap.print();

	// 5 4 3 4
	// delete 5
	BinaryHeap<int> :: downHeap(heap);
	heap.check();
	heap.print();

	// 4 4 3
	// delete 4
	BinaryHeap<int> :: downHeap(heap);
	heap.check();
	heap.print();

	// 4 3
	// delete 4
	BinaryHeap<int> :: downHeap(heap);
	heap.check();
	heap.print();

	// 3
	// delete 3
	BinaryHeap<int> :: downHeap(heap);
	heap.check();
	heap.print();

	int a1[] = { 1, 11, 4, 6, 7, 2, 0, 9, 10, 5, 3 };
	std :: size_t sz = sizeof(a1) / sizeof(a1[0]);
	unique_ptr<int[]> arr(new int[sz]);
	for (std :: size_t i = 0; i < sz; ++i)
		arr[i] = a1[i];

	BinaryHeap<int> :: buildHeap(arr.get(), static_cast<int>(sz), heap);
	heap.check();
	heap.print();
	heap.release();

	int a2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	sz = sizeof(a2) / sizeof(a2[0]);
	arr.reset(new int[sz]);
	for (std :: size_t i = 0; i < sz; ++i)
		arr[i] = a2[i];

	BinaryHeap<int> :: buildHeap(arr.get(), static_cast<int>(sz), heap);
	heap.check();
	heap.print();
	heap.release();
}

int main(int argc, char ** argv)
{
	ticket_246(argc, argv);

	return 0;
}

