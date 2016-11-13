/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */

#ifndef SORT_H_
#define SORT_H_

#include <heap/heap.h>
#include <list/single_linked_list.h>
#include <string>

namespace conq_sort {

/******************************************
 * \brief Sort testing
 ******************************************/
 template <typename T, typename Compare = std :: less<T> >
 void testSort(T * data, int dataSize, const Compare & cmp = Compare())
 {
 	for (int i = 0; i < dataSize - 1; i++) {
 		if (cmp(data[i + 1], data[i]))
 			std :: cout << "[" << i << "] = " << data[i] << ", ["
			            << i + 1 << "] = " << data[i + 1] << std :: endl;
		BOOST_ASSERT(!cmp(data[i + 1], data[i]));
 	}
 }


/*******************************************
 * \brief Insert sort algorithm
 *******************************************/
template <typename T, typename Compare = std :: less<T> >
void insertSort(T * data, int dataSize, Compare cmp = std :: less<T>())
{
	for (int i = 1; i < dataSize; i++) {
		for (int current = i; current > 0; current--) {
			if (cmp(data[current], data[current - 1]))
				std :: swap(data[current], data[current - 1]);
			else
				break;
		}
	}
}


/********************************************
 * \brief Bucket sort algorithm
 ********************************************/
template <int BucketNum, int Size, typename T>
void bucketSort(T * data)
{
	typedef typename conq_list :: SingleLinkedList<T> :: template Unit<T> Bucket;
	Bucket bucket_pool[Size];
	Bucket * bucket[BucketNum] = {nullptr};
	int iterator[BucketNum] = {0}, pool_it = 0;

	BOOST_ASSERT(BucketNum > 0);
	BOOST_ASSERT(Size > 0);

	int min = data[0], max = data[0];
	for (int i = 1; i < Size; i++) {
		if (data[i] < min)
			min = data[i];
		else if (data[i] > max)
			max = data[i];
	}

	const int bucket_sz = (((max - min) / BucketNum) + 1);

	for (int i = 0; i < Size; i++) {
		int b = (data[i] - min) / bucket_sz;
		// sorted insert
		Bucket * add = &bucket_pool[pool_it++];
		add->value = data[i];
		if (iterator[b] > 0) {
			Bucket * cur = bucket[b];
			if (cur->value > add->value) {
				add->next = cur;
				bucket[b] = add;
			}
			else {
				for (; cur->next && cur->next->value < add->value; cur = cur->next);
				add->next = cur->next;
				cur->next = add;
			}
		} else
			bucket[b] = add;

		++iterator[b];
	}

	for (int i = 0, out = 0; i < BucketNum; i++) {
		while (bucket[i]) {
			data[out++] = bucket[i]->value;
			bucket[i] = bucket[i]->next;
		}
	}
}

/********************************************
 * \brief Counting sort algorithm (grow up only)
 ********************************************/
class CountingSort {
public:
	/****************************************
	 * \brief Unstable variant
	 * \todo  Modify for negative
	 ****************************************/
	template <int NUM, typename T>
	static void unstableSort(T * data, int dataSize)
	{
		T arr[NUM] = {0};

		for (int i = 0; i < dataSize; i++) {
			BOOST_ASSERT(data[i] >= 0);
			BOOST_ASSERT(data[i] < NUM);
			++arr[data[i]];
		}

		for (int out = 0, in = 0; out < dataSize; out++) {
			while (arr[in] == 0) ++in;
			data[out] = in;
			--arr[in];
		}
	}

	/****************************************
	 * \brief Stable variant (grow up)
	 * \todo  Modify for negative
	 ****************************************/
	template <int NUM, typename T>
	static void stableSort(T * data, int dataSize)
	{
		std :: unique_ptr<T[]> tmp(new T[dataSize]);

		BOOST_ASSERT(tmp.get());

		T arr[NUM] = {0};

		for (int i = 0; i < dataSize; i++) {
			BOOST_ASSERT(data[i] >= 0);
			BOOST_ASSERT(data[i] < NUM);
			++arr[data[i]];
		}

		// first place for each element
		for (int i = 1; i < NUM; i++)
			arr[i] = arr[i] + arr[i - 1];

		for (int i = dataSize - 1; i >= 0; --i)
			tmp[--arr[data[i]]] = data[i];

		for (int i = 0; i < dataSize; i++)
			data[i] = tmp[i];
	}

	/****************************************
	 * \brief Stable sort for random values (grow up)
	 ****************************************/
	template <typename T>
	static void sort(T * data, int dataSize)
	{
		if (dataSize < 2)
			return;

		// search min && max
		T min = data[0], max = data[0];
		for (int i = 0; i < dataSize; i++) {
			if (data[i] < min)
				min = data[i];
			if (data[i] > max)
				max = data[i];
		}

		// all elements are equal
		if (min == max)
			return;

		int num = max - min + 1;

//		std :: cout << __PRETTY_FUNCTION__ << ": min = " << min
//		            << ", max = " << max << ", num = " << num << std :: endl;

		std :: unique_ptr<int[]> arr(new int[num]());

		for (int i = 0; i < dataSize; i++)
			++arr[data[i] - min];

		for (int i = 1; i < num; i++)
			arr[i] = arr[i] + arr[i - 1];

		std :: unique_ptr<int[]> tmp(new int[dataSize]);
		for (int i = dataSize - 1; i >= 0; --i) {
			tmp[--arr[data[i] - min]] = data[i];
		}

		for (int i = 0; i < dataSize; i++)
			data[i] = tmp[i];
	}

private:
	CountingSort() {}
	~CountingSort() {}
};

/********************************************
 * \brief Quick sort algorithm
 ********************************************/
class QuickSort {
public:
	/*****************************************
	 * \brief Last select strategy
	 *****************************************/
	class LastSelectStrategy
	{
		LastSelectStrategy() {}
		~LastSelectStrategy() {}
	public:
		static int select(int lo, int hi)
		{
			BOOST_ASSERT(lo < hi);
			return hi - 1;
		}
	};

	/****************************************
	 * \brief Center select strategy
	 ****************************************/
	class CenterSelectStrategy
	{
		CenterSelectStrategy() {}
		~CenterSelectStrategy() {}
	public:
		static int select(int lo, int hi)
		{
			BOOST_ASSERT(lo < hi);
			return lo + ((hi - lo) / 2);
		}
	};

	/****************************************
	 * \brief Random select strategy
	 ****************************************/
	class RandomSelectStrategy
	{
		RandomSelectStrategy() {}
		~RandomSelectStrategy() {}
	public:
		static int select(int lo, int hi)
		{
			BOOST_ASSERT(lo < hi);
			srand(time(NULL) + lo + hi);
			return lo + (rand() % (hi - lo));
		}
	};

	/*****************************************
	* \brief Kormen variant
	*****************************************/
	template <class SelectStrategy, typename T, typename Compare = std :: less<T> >
	static void rSort_v1(T * data, int dataSize, const Compare & cmp = std :: less<T>())
	{
		std :: function<void(T*,int,int)> fn = [&](T * data, int lo, int hi) {
			if (lo >= hi)
				return;

			int select = SelectStrategy :: select(lo, hi), wall = lo, pivot = hi - 1;
			if (select != pivot)
				std :: swap(data[select], data[pivot]);

			for (int i = lo; i < pivot; i++) {
				if (cmp(data[i], data[pivot])) {
					if (i != wall)
						std :: swap(data[wall], data[i]);
					++wall;
				}
			}
			if (pivot != wall)
				std :: swap(data[wall], data[pivot]);

			fn(data, lo, wall);
			fn(data, wall + 1, hi);
		};

		fn(data, 0, dataSize);
	}

	/*****************************************
	* \brief Traditional variant
	*****************************************/
	template <class SelectStrategy, typename T, typename Compare = std :: less<T> >
	static void rSort_v2(T * data, int dataSize, const Compare & cmp = std :: less<T>())
	{
		std :: function<void(T*, int, int)> fn = [&](T * arr, int lo, int hi) {
			T pivot = arr[SelectStrategy :: select(lo, hi)];
			int l = lo, r = hi;

			do {
				while (cmp(arr[l], pivot)) { ++l; }
				while (cmp(pivot, arr[r])) { --r; }

				if (l <= r) {
					if (l != r)
						std :: swap(arr[l], arr[r]);
					++l;
					--r;
				}
			} while (l <= r);

			if (r > lo) fn(arr, lo, r);
			if (l < hi) fn(arr, l, hi);
		};

		fn(data, 0, dataSize - 1);
	}

	/*****************************************
	* \brief   Iteration traditional variant
	* \details Save future call params in storage and
	*          sort bigger piece.
	* \warning Not ready yet.
	*****************************************/
	template <class SelectStrategy, typename T, typename Compare = std :: less<T> >
	static void iSort(T * data, int dataSize, const Compare & cmp = std :: less<T>())
	{
//#warning "Not ready yet"
		(void)data;
		(void)dataSize;
		(void)cmp;
	}

private:
	QuickSort() {}
	~QuickSort() {}
};


/*******************************************
 * \brief   Radix sort for digits
 * \details Used counting sort and radix size 1 byte.
 *          Used storage only for 1 pass
 ******************************************/
template <typename T>
void radixSort(T * data, int dataSize)
{
	uint8_t counting[0x100] = {0};

	std :: unique_ptr<T[]> arr(new T[dataSize]);

	T * in = data, * out = arr.get();

	uint32_t rank = 0xFF;
	int offset = 0;
	auto unsign_fn = [&]() {
		for (int j = 0; j < dataSize; j++)
			++counting[((in[j] & rank) >> offset)];
		// wise optimization
		if (counting[0] == dataSize) {
			// all rank is equal and don't need to sort
			std :: fill_n(counting, 0x100, 0);
			return;
		}
		for (int j = 1; j < 0x100; j++)
			counting[j] += counting[j - 1];
		for (int j = dataSize - 1; j >= 0; --j)
			out[--counting[((in[j] & rank) >> offset)]] = in[j];
	};

	for (int i = 0;
	     i < static_cast<int>(sizeof(T)) - 1;
	     i++, rank <<= 8, offset += 8)
	{
		unsign_fn();
		std :: swap(in, out);
		std :: fill_n(counting, 0x100, 0);
	}
	// last pass for sign
	if (std :: numeric_limits<T>::is_signed) {
		for (int j = 0; j < dataSize; j++)
			++counting[((in[j] & rank) >> offset)];

		for (int neg = 254; neg > 127; --neg)
			counting[neg] += counting[neg + 1];

		counting[0] += counting[128];

		for (int pos = 1; pos < 128; pos++)
			counting[pos] += counting[pos - 1];

		for (int j = dataSize - 1; j >= 0; --j)
			out[--counting[((in[j] & rank) >> offset)]] = in[j];
	} else
		unsign_fn();

	std :: swap(in, out);

	if (data != in)
		std :: copy(in, in + dataSize, data);
}

namespace recursion {

/*******************************************
 * \brief Merge sort algorithm
 ******************************************/
template <typename T, typename Compare = std :: less<T> >
void mergeSort(T * data, int dataSize, Compare cmp = std :: less<T>())
{
	if (dataSize < 2)
		return;

	if (dataSize == 2) {
		if (!cmp(data[0], data[1]))
			std :: swap(data[0], data[1]);
		return;
	}

	int middle = dataSize / 2;

	mergeSort(data, middle, cmp);

	mergeSort(&data[middle], dataSize - middle, cmp);

	int left_idx = 0, right_idx = middle, idx = 0;

	boost :: scoped_array<T> arr(new T[dataSize]);

	BOOST_ASSERT(arr.get());

	while ((left_idx < middle) && (right_idx < dataSize)) {
		(cmp(data[left_idx], data[right_idx])) ?
			arr[idx++] = data[left_idx++] :
			arr[idx++] = data[right_idx++];
	}

	while (left_idx < middle)
		arr[idx++] = data[left_idx++];

	while (right_idx < dataSize)
		arr[idx++] = data[right_idx++];

	std :: memcpy(data, arr.get(), sizeof(T) * dataSize);
}

} /** namespace recursion */

namespace iteration {

/*******************************************
 * \brief   Merge sort algorithm
 * \details One addition buffer and without recursion
 *******************************************/
template <typename T, typename Compare = std :: less<T> >
void mergeSort(T * data, int dataSize, Compare cmp = std :: less<T>())
{
	if (dataSize < 2) return;

	if (dataSize == 2) {
		if (!cmp(data[0], data[1]))
			std :: swap(data[0], data[1]);
		return;
	}

	// 1. split -> sort neighbors
	for (int i = 0, j = 0, i_max = dataSize / 2; i < i_max; i++, j += 2)
		if (!cmp(data[j], data[j + 1]))
			std :: swap(data[j], data[j + 1]);

	// 2. merge
	std :: unique_ptr<T[]> tmp(new T[dataSize]);

	T * input = data, * output = tmp.get();

	int chunk_sz = 2;

	while (chunk_sz < dataSize) {
		int l = 0, l_max = chunk_sz, pos = 0;

		auto merge = [&](int & l, int l_max, int r, int r_max) {
				while (l < l_max && r < r_max)
					cmp(input[l], input[r]) ? output[pos++] = input[l++] : output[pos++] = input[r++];
				while (l < l_max) output[pos++] = input[l++];
				while (r < r_max) output[pos++] = input[r++];
		};

		for (int block = 0, block_max = dataSize / (chunk_sz * 2); block < block_max; block++) {
			int r_max = l_max + chunk_sz;
			merge(l, l_max, l_max, r_max);
			l += chunk_sz;
			l_max = l + chunk_sz;
		}

		if (l < dataSize) {
			int l_max = l + chunk_sz;
			(dataSize < l_max) ? merge(l, dataSize, 0, 0) : merge(l, l_max, l_max, dataSize);
		}

		std :: swap(input, output);
		chunk_sz *= 2;
	}

	if (input != data)
		std :: memcpy(data, input, dataSize * sizeof(T));
}

/*******************************************
 * \brief   Natural merge sort algorithm
 * \details One addition buffer and without recursion +
 *          better time in the best case than in usual
 *          implementation
 *******************************************/
template <typename T, typename Compare = std :: less_equal<T> >
void mergeNaturalSort(T * data, int dataSize, Compare cmp = std :: less_equal<T>())
{
	std :: unique_ptr<T[]> tmp(new T[dataSize]);

	T * input = data, * output = tmp.get();

	bool merge = true;

	while (merge) {
		merge = false;
		int l = 0, pos = 0;
		for (int r = l + 1; r < dataSize; r++) {
			if (!cmp(input[r - 1], input[r])) {
				int l_max = r, r_max = r + 1;
				// search r_max
				while ((r_max < dataSize) && (cmp(input[r_max - 1], input[r_max])))
					r_max++;
				// merge
				while ((l < l_max) && (r < r_max)) {
					cmp(input[l], input[r])	 ?
						output[pos++] = input[l++] :
						output[pos++] = input[r++];
				}
				while (l < l_max)
					output[pos++] = input[l++];
				while (r < r_max)
					output[pos++] = input[r++];

				merge = true;
				l = r_max;
			}
		}

		// residue
		if (merge) {
			while (l < dataSize)
				output[pos++] = input[l++];
			std :: swap(input, output);
		}
	}

	if (input != data)
		std :: memcpy(data, input, dataSize * sizeof(T));
}

} /** namespace iteration */

/*******************************************
 * \brief Heap sort
 *******************************************/
template <typename T, typename Compare = std :: less<T> >
void heapSort(T * data, int dataSize, Compare cmp = Compare())
{
	conq_heap :: BinaryHeap<T> heap(data, static_cast<std :: size_t>(dataSize), cmp);
	heap.check(cmp);

	while (--dataSize > 0) {
		T last = data[0];
		conq_heap :: BinaryHeap<T> :: downHeap(heap, cmp);
		heap.check(cmp);
		data[dataSize] = last;
	}

	heap.release();
}

namespace book {

/*******************************************
 * \brief   Insert sort algorithm
 * \details Optimize swap operation (unlike of conq_sort :: insertSort)
 *******************************************/
template <typename T, typename Compare = std :: less<T> >
void insertSort(T * data, int dataSize, Compare cmp = std :: less<T>())
{
	for (int i = 1; i < dataSize; i++) {
		int current = i;
		T tmp = data[i];

		while (current > 0) {
			if (cmp(tmp, data[current - 1]))
				data[current] = data[current - 1];
			else
				break;

			current--;
		}

		data[current] = tmp;
	}
}

} /* namespace book */

/********************************************
 * \brief   Big data sorting
 * \details Sort integer values in a file
 ********************************************/
template <typename T>
void sortBigData(const std :: basic_string<T> & in, std :: size_t memLimit, std :: basic_string<T> & out)
{
	time_t t = time(NULL);
	pid_t p = getpid();

	std :: string file_postfix = std :: string("tmp_") + std :: string(__func__) + "_" + std :: to_string(t) + "_" + std :: to_string(p);

	assert(memLimit >= 2); // not interesting, its impossible

	int chunk_sz = memLimit / 2; /** for chunk sorting needs more data */

	std :: ifstream input(in);
	if (!input.is_open()) {
		std :: cout << "fail opening file " << in << std :: endl;
		return;
	}

	boost :: scoped_array<int> m1(new int[chunk_sz]);

	int size = 0, i1 = 0, chunk_num = 0;
	while (input >> m1[i1]) {
		++size;
		if (++i1 == chunk_sz) {
			QuickSort :: rSort_v1<QuickSort :: RandomSelectStrategy>(m1.get(), i1);
			out = file_postfix + "_" + std :: to_string(chunk_num++);
			std :: ofstream o(out);
			for (int i = 0; i < i1; ++i) {
				o << m1[i] << std :: endl;
			}
			i1 = 0;
		}
	}
	if (i1) {
		QuickSort :: rSort_v1<QuickSort :: RandomSelectStrategy>(m1.get(), i1);
		out = file_postfix + "_" + std :: to_string(chunk_num++);
		std :: ofstream o(out);
		for (int i = 0; i < i1; ++i) {
			o << m1[i] << std :: endl;
		}
	}

	std :: cout << "size = " << size << " memlimit = " << memLimit << " chunk_sz = " << chunk_sz
	            << " chunk_num = " << chunk_num << std :: endl;

	int counter = 0;
	boost :: scoped_array<int> m2(new int[chunk_sz]);
	while (chunk_num > 1) {
		out = file_postfix + "_" + std :: to_string(counter + chunk_num);
		std :: ofstream o(out);
		std :: ifstream in1(file_postfix + "_" + std :: to_string(counter++));
		std :: ifstream in2(file_postfix + "_" + std :: to_string(counter++));
		assert(o.is_open() && in1.is_open() && in2.is_open());

		int i2 = 0, l1 = 0, l2 = 0;
		i1 = 0;
		while (true) {
			if (i1 == l1) {
				i1 = l1 = 0;
				while ((l1 < chunk_sz) && (in1 >> m1[l1])) { ++l1; }
				if (!l1) {
					while (i2 != l2) { o << m2[i2++] << std :: endl; }
					while (in2 >> m2[0]) { o << m2[0] << std :: endl; }
					break;
				}
			}
			else if (i2 == l2) {
				i2 = l2 = 0;
				while ((l2 < chunk_sz) && (in2 >> m2[l2])) { l2++; }
				if (!l2) {
					while (i1 != l1) { o << m1[i1++] << std :: endl; }
					while (in1 >> m1[0]) { o << m1[0] << std :: endl; }
					break;
				}
			}
			else {
				while (i1 != l1 && i2 != l2) {
					if (m1[i1] <= m2[i2])
						o << m1[i1++] << std :: endl;
					else
						o << m2[i2++] << std :: endl;
				}
			}
		}
		--chunk_num;
	}
}

} /* namespace conq_sort */


#endif /* SORT_H_ */
