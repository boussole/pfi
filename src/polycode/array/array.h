/**
 * \file    array.h
 * \brief   Array utils and problems
 * \details
 * \author  boussole
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include <common/common.h>
#include <common/algorithm.h>
#include <sort/sort.h>

/***********************************************************
 * \namespace conq_array
 * \brief Group operations with arrays
 **********************************************************/
namespace conq_array {

/***********************************************************
 * \brief Filling of array
 * \details Create array and fill it random sign values, in range [-max/2 .. max/2+1]
 * \param [in, out] arr Array which will be filled
 * \param [in] size Array size
 * \param [in] max Range of random values
 **********************************************************/
static inline
void fillRandom(boost :: scoped_array<int> & arr, std :: size_t size, uint8_t max = 100)
{
	srand(time(NULL));

	arr.reset(new int[size]);

	for (std :: size_t i = 0; i < size; i++) {
		arr[i] = (rand() - (RAND_MAX / 2)) % max;
	}
}

/***********************************************************
 * \brief Filling of array by INT input values
 * \param [in, out] arr Array which will be filled
 * \param [in] size Array size
 * \param [in] val Cmd line values
 **********************************************************/
static inline
void fillCmd(boost :: scoped_array<int> & arr, int size, char ** val)
{
	BOOST_ASSERT(size > 0);
	arr.reset(new int[size]);
	for (int i = 0; i < size; i++) {
		arr[i] = atoi(val[i]);
	}
}

/***********************************************************
 * \brief  Filling of array from string where values are splitted by space
 * \return true in case of correct string | false in other case
 ***********************************************************/
static inline
bool fillFromString(int * arr, int size, char * str)
{
	std :: cout << "parse array [" << size << "] = " << str << std :: endl;

	int idx = 0;
	char * token = strtok(str, " \t");

	while (token) {
		if (idx == size) return false;
		arr[idx++] = atoi(token);
		token = strtok(NULL, " \t");
	}

	return (idx == size);
}

/***********************************************************
 * \brief Filling of array by T input values
 * \param [in, out] arr Array which will be filled
 * \param [in] size Array size
 * \param [in] val Cmd line values
 * \tparam T Type of array element
 **********************************************************/
template <typename T>
void fillCmd(boost :: scoped_array<T> & arr, int size, char ** val)
{
	BOOST_ASSERT(size > 0);
	arr.reset(new char[size]);
	for (int i = 0; i < size; i++) {
		arr[i] = *val[i];
	}
}

/***********************************************************
 * \brief Triplet expression
 * \param [in] a First arg
 * \param [in] b Second arg
 * \param [in] c Expected result
 * \return Result of comparing expression with a and b with c
 **********************************************************/
bool SumOfQuad(int a, int b, int c);

/***********************************************************
 * \brief Common full version for find triplets
 **********************************************************/
template <typename T, typename Function>
void findTriplet(const boost :: scoped_array<T> & arr, int size, Function fn)
{
	int counter = 0;

	for (int a = 0; a < size; a++)
		for (int b = 0; b < size; b++)
			for (int c = 0; c < size; c++) {
				if ((a != b) && (b != c) && (a != c) && fn(arr[a], arr[b], arr[c])) {
					std :: cout << "Triplet: a = " << arr[a] << " b = " << arr[b] << " c = " << arr[c] <<  "; index: " << a << " " << b << " " << c << std :: endl;
					counter++;
				}
		}

	std :: cout << __func__ << " result: " << counter << " matches\n";
}

namespace naive {

/***********************************************************
 * \brief SumOfQuad specific search O(N^3)
 **********************************************************/
void findTriplet_SumOfQuad(boost :: scoped_array<int> & arr, int size);

}

/***********************************************************
 * \brief SumOfQuad specific search O(N^2)
 **********************************************************/
void findTriplet_SumOfQuad(boost :: scoped_array<int> & arr, int size);

/***********************************************************
 * \brief Print array
 * \details Print prefix string and all elements of array
 * \tparam T Type of array element
 * \param [in] arr Array to be printed
 * \param [in] sz Size of array
 * \param [in] pref Prefix before array output
 **********************************************************/
template <typename T>
void print(T * arr, int sz, const std :: string & pref = std :: string(), const char * sep = " ")
{
	std :: cout << pref;

	for (int i = 0; i < sz; i++) {
		std :: cout << sep << arr[i];
	}

	std :: cout << std :: endl;
}

/***********************************************************
 * \brief Show sub array of values who is in a range (#62)
 * \details There is an array and list of ranges.\n
 * Function searches sub array of values inside range and print it
 * \tparam T Type of array element
 * \param [in, out] arr Array for searching. Array will be sorted.
 * \param [in] sz Size of array
 * \param [in] range List of ranges for searching sub arrays
 **********************************************************/
template <typename T>
void showSubArrayInRange(T * arr, int sz, const std :: list<std :: pair<int, int> > & range)
{
/** \cond DOXYGEN_SOURCE */
	print(arr, sz, "input:");
	std :: sort(arr, arr + sz);
	print(arr, sz, "prepared:");

	std :: list<std :: pair<int, int> > :: const_iterator it = range.begin();

	while (it != range.end()) {
		if (it->first >= it->second) {
			std :: cout << "\ninvalid range: ( " << it->first << ", " << it->second << " ) ignoring\n" << std :: endl;
			it++;
			continue;
		}

		std :: cout << "\nrange ( " << it->first << ", " << it->second << " )" << std :: endl;

		int a = 0;
		for (a = 0; a < sz; a++) { /** find low limit */
			if (arr[a] > it->first)
				break;
		}

		if (a == sz) {
			std :: cout << "sub array doesn't exist, low border did't find\n";
			it++;
			continue;
		}

		int b = sz;
		for (; b > a; b--) { /** find high limit */
			if (arr[b - 1] < it->second)
				break;
		}

		if (a == b) {
			std :: cout << "sub array doesn't exist, high border didn't find\n";
			it++;
			continue;
		}

		std :: cout << "sub array (size = " << b - a << ") ";
		for (; a < b; a++) {
			std :: cout << arr[a] << " ";
		}
		std :: cout << std :: endl;

		it++;
	}
/** \endcond */
}

/***********************************************************
 * \brief Largest partial sum (#42)
 * \details Find maximal sum of array who could be taken by removing some elements
 * \tparam T Type of array
 * \param [in] arr Array
 * \param [in] size Size of array
 * \return largest sum
 **********************************************************/
template <typename T>
T findLargestPartialSum(T * arr, int size)
{
	assert(size > 0);

	T sum = arr[0];

	for (int i = 1; i < size; i++)
	{
		if (sum >= 0) {
			if (arr[i] > 0) {
				sum += arr[i];
			}
		}
		else if (arr[i] > sum) {
			sum = arr[i];
		}
	}

	return sum;
}

/***********************************************************
 * \brief Check two arrays for equal as result of shift action
 **********************************************************/
template <typename T>
bool isEqualAfterShift(T * src, T * dst, int size)
{
	// for each position in src array
	for (int src_pos = 0; src_pos < size; src_pos++) {
		// search start position in dst array
		for (int dst_pos = 0; dst_pos < size; dst_pos++) {
			// if we have identical entry, we will check tails
			if (src[src_pos] == dst[dst_pos]) {
				int si = (src_pos + 1) % size, di = (dst_pos + 1) % size;
				while (src[si] == dst[di]) {
					if ((si == src_pos)) {
						return true;
					}
					si = (si + 1) % size;
					di = (di + 1) % size;
				}
			}
		}
	}

	return false;
}

enum class ArrayShiftDirection {
	Right = 0,
	Left
};

/***********************************************************
 * \brief Find shift of sort array
 * \details Shift is detected by expression of sorting.
 * It uses additional compare operation to pretend user error in 'cmp' argument,
 * for shift search we should use compare for less + equal or greater_equal.
 **********************************************************/
template <typename T, typename Compare = std :: less<T> >
int shiftSizeOfSortArray(boost :: scoped_array<T> & arr, int arrSz, ArrayShiftDirection direction, Compare cmp)
{
	int offset = 1;
	for (; offset < arrSz; offset++) {
		if (!cmp(arr[offset - 1], arr[offset]) && (arr[offset - 1] != arr[offset])) {
			return (direction == ArrayShiftDirection :: Right) ? offset : arrSz - offset;
		}
	}
	return 0;
}

/***********************************************************
 * \class ArrayShift
 * \brief Static class for circle shift of array
 **********************************************************/
class ArrayShift {
public:
	/***********************************************************
	 * \brief Callback is used for calculate position after left shift
	 * \tparam T Type of array element
	 * \note we also can use right shift with 'shiftSz == arrSz - shiftSz'
	 **********************************************************/
	template <typename T>
	static void left(T * arr, int arrSz, int shiftSz);

	/***********************************************************
	 * \brief Callback is used for calculate position after right shift
	 * \tparam T Type of array element
	 * \note we also cat use left shift with 'shiftSz == arrSz - shiftSz'
	 **********************************************************/
	template <typename T>
	static void right(T * arr, int arrSz, int shiftSz);

protected:
	/***********************************************************
	 * \brief common algorithm of pass an array, it depends on direction of shift
	 **********************************************************/
	template <typename T>
	static void common(T * arr, int arrSz, int shiftSz, boost :: function<int(int, int, int)>);
};

/***********************************************************
 * \brief common algorithm of pass an array, it depends on direction of shift
 **********************************************************/
template <typename T>
void ArrayShift :: common(T * arr, int arrSz, int shiftSz, boost :: function<int(int, int, int)> dstFn)
{
	int step_total = arrSz - 1;
	shiftSz = shiftSz % arrSz; /** round to prevent circle work */
	int src = 0;
	int dst = dstFn(shiftSz, arrSz, src);

	while (step_total > 0) {
		std :: swap(arr[dst], arr[src]);

		/** check correct dst insert */
		dst = dstFn(shiftSz, arrSz, dst);

		/** if we have already done that correctly */
		if (dst == src) {
			src++;
			dst = dstFn(shiftSz, arrSz, src);
			step_total--;
		}

		step_total--;
	}
}

/***********************************************************
 * \brief Callback is used for calculate position after left shift
 * \tparam T Type of array element
 * \note we also can use right shift with 'shiftSz == arrSz - shiftSz'
 **********************************************************/
template <typename T>
void ArrayShift :: left(T * arr, int arrSz, int shiftSz)
{
	common(arr, arrSz, shiftSz, [](int shiftSz, int arrSz, int src) {
		return ((arrSz + src - shiftSz) % arrSz);
	});
}

/***********************************************************
 * \brief Callback is used for calculate position after right shift
 * \tparam T Type of array element
 * \note we also cat use left shift with 'shiftSz == arrSz - shiftSz'
 **********************************************************/
template <typename T>
void ArrayShift :: right(T * arr, int arrSz, int shiftSz)
{
	common(arr, arrSz, shiftSz, [](int shiftSz, int arrSz, int src) {
		return ((src + shiftSz) % arrSz);
	});
}

/***********************************************************
 * \brief Find common parts of two arrays without repeat
 * \tparam T Type of array element
 * \return Size of common array or -1 in case of error
 ***********************************************************/
template <typename T>
int findCommonPartOfTwoArrays(T * arr1, int size1,
		T * arr2, int size2,
		boost :: scoped_array<T> & common)
{
	std :: sort(arr1, arr1 + size1);
	std :: sort(arr2, arr2 + size2);

	int common_sz = 0;

	common.reset(new T[size1 < size2 ? size1 : size2]);
	if (!common.get()) {
		return -1;
	}

	int i1 = 0, i2 = 0;

	while ((i1 < size1) && (i2 < size2)) {
		if (arr1[i1] == arr2[i2]) {
			if ((common_sz == 0) || (common[common_sz - 1] != arr1[i1])) {
				common[common_sz++] = arr1[i1];
			}
			i1++; i2++;
		}
		else
			(arr1[i1] < arr2[i2]) ? i1++ : i2++;
	}

	return common_sz;
}

/***********************************************************
 * \brief       Diff of two arrays
 * \param [in]  arr1  - Left array
 * \param [in]  size1 - Size of left array
 * \param [in]  arr2  - Right array
 * \param [in]  size2 - Size of right array
 * \param [out] del   - Callback is called for each element which is missing in right array
 * \param [out] add   - Callback is called for each element which is added in right array
 **********************************************************/
template <typename T, typename Function>
void diff(T * arr1, std :: size_t size1, T * arr2, std :: size_t size2, Function del, Function add)
{
	boost :: numeric :: ublas :: matrix<int> m;
	conq_algo :: buildLongestCommonSubsequence(m, arr1, size1, arr2, size2);

	/** debug only - LCS */
	std :: function<void(int)> common = [](int v) { std :: cout << v; };

	conq_algo :: diffLongestCommonSubsequence(m, arr1, arr2, del, add, common);
}

/***********************************************************
 * \brief       Merge two sorted arrays
 * \param [in]  in1 Array 1
 * \param [in]  size1 Array1 size
 * \param [in]  in2 Array 2
 * \param [in]  size2 Array2 size
 * \param [out] out Merged array
 * \return      Size of merged array
 **********************************************************/
template <typename T, typename Compare = std :: greater_equal<T> >
int mergeSortedArrays(const std :: unique_ptr<T[]> & in1, int size1,
                       const std :: unique_ptr<T[]> & in2, int size2,
                       std :: unique_ptr<T[]> & out, Compare cmp = Compare())
{
	BOOST_ASSERT(size1 >= 0 && size2 >= 0);

	int size = size1 + size2;
	out.reset(new T [size]);
	BOOST_ASSERT(out.get());

	int it1 = 0, it2 = 0, it_out = 0;
	while (it1 < size1 && it2 < size2)
		out[it_out++] = cmp(in1[it1], in2[it2]) ? in2[it2++] : in1[it1++];

	while (it1 < size1)
		out[it_out++] = in1[it1++];

	while (it2 < size2)
		out[it_out++] = in2[it2++];

	return size;
}

/***********************************************************
 * \brief Find minimal element of index K
 ***********************************************************/
template <typename T>
int findMinimalValueIndexOfK(T * arr, int size, int minimalIndex, T & minValOfIndexK)
{
	if (minimalIndex < 0 || minimalIndex >= size)
		return -1;

	if (size == 1) {
		minValOfIndexK = arr[0];
		return 0;
	}

	std :: function<T(int, int)> priv = [&](int lo, int hi) {
		if (lo == hi)
			return arr[lo];

		std::mt19937 generator(time(nullptr));
		std :: uniform_int_distribution<int> dist(lo, hi - 1);

		int pivot = dist(generator);
		if (pivot != hi)
			std :: swap(arr[pivot], arr[hi]);

		int wall = lo;
		for (int i = lo; i < hi; ++i) {
			if (arr[i] < arr[hi]) {
				if (i != wall)
					std :: swap(arr[i], arr[wall]);
				++wall;
			}
		}

		if (wall != hi)
			std :: swap(arr[wall], arr[hi]);

		if (wall == minimalIndex)
			return arr[minimalIndex];

		if (wall < minimalIndex)
			return priv(wall + 1, hi);
		else
			return priv(lo, wall - 1);
	};

	minValOfIndexK = priv(0, size - 1);

	return 0;
}

/***********************************************************
 * \brief           Random  select element in stream
 * \param [in]      arr     Stream of values, can be changed
 * \param [in]      stream  Size of stream
 * \param [out]     selArr  Selected array, should be allocated
 * \param [in]      selSize Size of random values which should be chosen
 * \return          Number of chosen elements or -1 in case of error
 * \warning         Bad entropy
 ***********************************************************/
template <typename T>
int selectRandomElementsInStream(T * stream, int size, T * selected, int selectedSize)
{
	if (size <= 0 || selectedSize <= 0)
		return -1;

	if (size < selectedSize) {
		for (int i = 0; i < size; ++i)
			selected[i] = stream[i];
		return size;
	}

	int i = 0;
	while (i < selectedSize) {
		selected[i] = stream[i];
		++i;
	}

	std::mt19937 generator(time(nullptr));
	for (; i < size; ++i) {
		std :: uniform_int_distribution<int> dist(0, i);
		int r = dist(generator);
//		std :: cout << "i = " << i << " r = " << r << std :: endl;

		if (r < selectedSize)
			selected[r] = stream[i];
	}

	return selectedSize;
}

/***********************************************************
 * \brief           Permutate input sequence
 * \param [in, out] arr Array for permution
 * \param [in]      sz  Array sz
 * \note            Bad entropy
 ***********************************************************/
template <typename T>
void permutateRandom(T * arr, int sz)
{
	std::mt19937 generator(time(nullptr));
	for (int max = sz - 1; max > 0; --max) {
		std :: uniform_int_distribution<int> dist(0, max);
		int r = dist(generator);
		if (max != r)
			std :: swap(arr[max], arr[r]);
	}
}

/***********************************************************
 * \brief       Permutate input sequence and init output
 * \param [in]  input Input array for permutation
 * \param [out] output Output array
 * \param [in]  sz Input, Output size
 * \warning     Output sequence must have enough size
 ***********************************************************/
template <typename T>
void permutateRandom(T * input, T * output, int sz)
{
	std::mt19937 generator(time(nullptr));
	for (int i = 0; i < sz; ++i) {
		std :: uniform_int_distribution<int> dist(0, i);
		int r = dist(generator);
		if (i != r) //< it means not-init position
			output[i] = output[r];
		output[r] = input[i];
	}
}

/************************************************************
 * \brief Random select of number in array
 * \param [in, out] arr Input array is changed during selection
 * \param [in]      size Size of input array
 * \param [out]     selected Array of selected numbers, should be allocated before call
 * \param [in]      selectedSize Number of items which should be seleceted
 * \return          Actual number of selected items
 ************************************************************/
template <typename T>
int selectRandomElementsInArray(T * arr, int size, T * selected, int selectedSize)
{
	permutateRandom(arr, size);

	int i = 0;
	for (; (i < size) && (i < selectedSize); ++i)
		selected[i] = arr[i];

	return i;
}

namespace greedy {

/***********************************************************
 * \brief  Create change from coints and return minimal number of coints
 * \return Minimal quantity of coins
 ***********************************************************/
int makeMinChange(int * coin, int coinSz, int changeSum, int * changeCoin);

} /** namespace greedy */

namespace dp {

/*************************************************************
 * \brief  Create change from coints and return minimal number of coints
 * \return Minimal quantity of coins
 *************************************************************/
int makeMinChange(int * coin, int coinSz, int changeSum, int * changeCoin);

/*************************************************************
 * \brief  Find continuous subsequence with maximal sum
 * \return Sum of subsequence
 *************************************************************/
int findContinuousSubsequenceWithMaxSum(int * seq, int seqSz, int & start, int & finish);

/*************************************************************
 * \brief  Longest zig-zag subsequence
 * \return Length of the longest subsequnce
 *************************************************************/
int longestZigZag(int * sequence, int size);

} /** namespace dp */

/*************************************************************
 * \brief   Sum of array without comparators
 *************************************************************/
template <typename T>
T sumOfArrayWithoutComparators(T * arr, int len)
{
	std :: function<T(T*,int)> cb[] = {
	{
		[&](T * arr, int i)->T {
			return arr[i] + cb[(i + 1) / len](arr, i + 1);
		}
	},
	{
		[&](T * arr, int index)->T {
			return 0;
		}
	}
	};

	return cb[0](arr, 0);
}

/************************************************************
 * \brief Maximal growing subsequence
 ************************************************************/
template <typename T>
int maxGrowingSubsequence(T * in, int size, T * out)
{
	if (size <= 0)
		return 0;

	/**
	 * pair :: first = len
	 * pair :: second = prev index
	 */
	std :: unique_ptr< std :: pair<int, int>[] > tbl(new std :: pair<int, int> [size]);

	std :: pair<int, int> max(1, 0);

	tbl[0].first = 1;
	tbl[0].second = -1;
	for (int i = 1; i < size; ++i) {
		tbl[i].first = 1;
		tbl[i].second = i;
		for (int j = 0; j < i; ++j) {
			if (in[j] < in[i]) {
				int new_len = tbl[j].first + 1;
				if (tbl[i].first < new_len) {
					tbl[i].first = new_len;
					tbl[i].second = j;
					if (max.first < tbl[i].first) {
						max.first = tbl[i].first;
						max.second = i;
					}
				}
			}
		}
	}

	// restore
	int len = max.first;
	while (max.first) {
		out[--max.first] = in[max.second];
		max.second = tbl[max.second].second;
	}

	return len;
}

/************************************************************
 * \brief Find the element repeated more than n/2 times
 ************************************************************/
template <typename T>
T * findElementRepeatedMoreThanHalf(T * in, int size)
{
	int candidate_num = 0;
	T * candidate = nullptr;

	for (int i = 0; i < size; ++i) {
		if (candidate_num == 0) {
			candidate = &in[i];
			++candidate_num;
		}
		else if (*candidate == in[i]) {
			++candidate_num;
		}
		else {
			--candidate_num;
		}
	}

	return candidate_num == 0 ? nullptr : candidate;
}

/************************************************************
 * \brief Replace numbers in array for merge maximal number
 ************************************************************/
void buildMaximalMergeNumber(int * arr, int size);

/************************************************************
 * \brief High median number
 ************************************************************/
static inline int median(int quantity)
{
	assert(quantity >= 0);

	if (quantity == 0)
		return -1;

	return quantity / 2;
}

/************************************************************
 * \brief Low median number
 ************************************************************/
static inline int lowMedian(int quantity)
{
	assert(quantity >= 0);

	if (quantity == 0)
		return -1;

	if ((quantity % 2) == 0)
		--quantity;

	return quantity / 2;
}

/************************************************************
 * \brief Find median with memory limit
 * \todo  Modify real memLimit including local vars
 ************************************************************/
template <typename T>
T & findMedianMemLimit(T * arr, int size, int memLimit = 13)
{
	assert(memLimit > 0);
	assert(size > 0);
	std :: unique_ptr<T []> mem(new T[memLimit]);

	int start = 0, finish = size - 1;
	int begin = 0, end = 0;
	int m = median(size);

	while (start != finish) {
		int sep = conq_sort :: QuickSort :: RandomSelectStrategy :: select(start, finish);
		// replace random separator with last element, using memory, there are no limit now, mem is free
		T pivot = arr[sep];
		std :: swap(arr[sep], arr[finish]);
		int w = start;
		T wall = arr[w];
		for (int i = start; i < finish; ++i, ++begin) {
			if (begin == end) {
				// load from hdd arr[offset, min(finish - i, memLimit)];
				end = std :: min(finish - i, memLimit);
				std :: memcpy(mem.get(), &arr[i], end * sizeof(T));
				begin = 0;
			}

			if (mem[begin] < pivot) {
				if (w != i) {
					arr[w] = mem[begin];   // save to disc
					arr[i] = wall;         // save to disc
				}
				wall = arr[++w];           // load new wall to mem
			}
		}
		// replace random separator with sep element using mem, there are no limit now, mem is free
		if (w != finish)
			std :: swap(arr[w], arr[finish]);

		// if we are the median
		if (w == m)
			break;

		if (w < m)
			start = w + 1;
		else
			finish = w - 1;
	}

	return arr[m];
}

/************************************************************
 * \brief Find subsequence closest to zero
 ************************************************************/
std :: pair<int, int> findSubsequenceClosestZero(int * arr, int size);

/************************************************************
 * \brief Maximum Product Subarray
 ************************************************************/
int maximumProductSubsequence(int * arr, int size, std :: list<int> &subseq);

} /** namespace conq_array */

/*
 * show K maximal elements from stream
 */
class FindKMaxElements
{
public:
	FindKMaxElements() {}
	~FindKMaxElements() {}
	bool doTask(int argc, char ** argv);

private:
	void doTask(char ** stream, int streamSz, int k);
};

/*
 * \brief Find minimal element of index K
 * \warning Not optimal decision
 */
class FindMinElementOfIndexK
{
public:
	FindMinElementOfIndexK() {}
	~FindMinElementOfIndexK() {}
	bool doTask(int * arr, int arrSz, int kMin);

private:
	/**
	 * \brief Find min[k] element using sorting
	 */
	void doTaskSorting(int * arr, int arrSz, int kMin);

	/**
	 * \brief Find min[k] element using search without changing array
	 * \note  Slot and bad idea
	 */
	void doTaskStable(int * arr, int arrSz, int kMin);
	//-
	bool checkIdx(const int * array, int sz, int idx, boost::function<bool(int, int)> &);
	bool checkAround(const int * array, int pos, int idx, int value, int & less, int & greater, int & equal, boost::function<bool(int, int)> &);
};

#endif /* ARRAY_H_ */
