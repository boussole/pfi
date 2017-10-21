/**
 * \file main.cpp
 *
 * \author boussole
 */

#include <common/common.h>
#include "array.h"
#include <matrix/matrix.h>

using namespace conq_array;
using namespace conq_algo;
using namespace conq_matrix;
using namespace std;

/***********************************************************
 * \brief Check input params and determ type of array filing
 * \return Size of array OR -1
 **********************************************************/
static inline
int checkArgs(int argc, char ** argv)
{
	int size = -1;

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size> [ array[0] ... array[size - 1] ]\n";
	} else if ((size = atoi(argv[1])) <= 0) {
		cout << "invalid array size\n";
	} else if ((argc > 2) && ((argc - 2) < size)) {
		cout << "not enough elements of array entered, awaits = " << size << ", entered " << (argc - 2) << endl;
		size = -1;
	}

	return size;
}

/***********************************************************
 * \brief Find triplet of elements by expression
 **********************************************************/
TICKET_FN(44)
{
	cout << "#" << ticket << endl;

	int sz = checkArgs(argc, argv);

	if (sz <= 0) {
		return;
	}

	boost :: scoped_array<int> arr;

	if (argc == 2)
		fillRandom(arr, sz, 100);
	else
		fillCmd(arr, sz, argv + 2);

	print(arr.get(), sz, "input:");

	findTriplet(arr, sz, SumOfQuad);

	naive :: findTriplet_SumOfQuad(arr, sz);
}

/**********************************************************
 * \brief Find sub array by range
 **********************************************************/
TICKET_FN(62)
{
	cout << '#' << ticket << endl;

	assert(argc > 1);

	int sz = checkArgs(2, argv);

	if (sz <= 0)
		return;

	cout << "array size = " << sz << endl;

	boost :: scoped_array<int> arr;

	int input_range = argc - 2;

	if (strncmp(argv[2], "custom", sizeof("custom")) == 0) {
		arr.reset(new int[sz]);
		for (int i = 0; i < sz; i++) {
			arr[i] = atoi(argv[i + 3]);
		}
		input_range -= (sz + 1);
	}
	else {
		fillRandom(arr, sz, 100);
	}

	list<pair<int, int> > range;

	while (input_range >= 2) {
		pair<int, int> p;

		// analize a
		const char * lex = argv[argc - input_range];
		if (strncmp(lex, "a=", sizeof("a=") - 1)) {
			cout << "invalid a: \"" << lex << "\"\n";
			break;
		}

		p.first = atoi(lex + sizeof("a=") - 1);

		// analize b
		lex = argv[argc - input_range + 1];
		if (strncmp(lex, "b=", sizeof("b=") - 1)) {
			cout << "invalid b: \"" << lex << "\"\n";
			break;
		}

		p.second = atoi(lex + sizeof("b=") - 1);

		range.push_back(p);

		input_range -= 2;
	}

	if (input_range != 0) {
		cout << "Warning!!! something strange at the end of input: " << argv[argc - 1] << endl;
	}

	showSubArrayInRange(arr.get(), sz, range);
}

/***********************************************************
 * \brief Largest partial sum
 **********************************************************/
TICKET_FN(42)
{
	cout << '#' << ticket << endl;

	assert(argc > 1);

	int sz = checkArgs(argc, argv);

	if (sz <= 0)
		return;

	cout << "array size = " << sz << endl;

	boost :: scoped_array<int> arr;

	if (argc == 2) {
		fillRandom(arr, sz, 100);
	} else {
		arr.reset(new int[sz]);
		for (int i = 0; i < sz; i++) {
			arr[i] = atoi(argv[i + 2]);
		}
	}

	print(arr.get(), sz, "input");

	cout << "largest partial sum = " << findLargestPartialSum(arr.get(), sz) << endl;
}

/***********************************************************
 * \brief Array circle shift tests
 * \warning Tests were not tested after refactoring
 **********************************************************/
TICKET_FN(52)
{
	cout << "# " << ticket << endl;

	if (argc < 3) {
		cout << argv[0] << " src[0] src[1] ... src[n] dst[0] dst[1] ... dst[n]\n";
		return;
	}

	int size = argc - 1;

	if (size % 2) {
		cout << "arrays should have equal length\n";
		return;
	}

	argv++;
	argc--;
	size /= 2;

	boost :: scoped_array<int> src(new int[size]);
	for (int i = 0; i < size; i++) {
		src[i] = atoi(argv[i]);
	}

	boost :: scoped_array<int> dst(new int[size]);
	for (int i = size, j = 0; i < argc; i++, j++) {
		dst[j] = atoi(argv[i]);
	}

	print(src.get(), size, "src");

	print(dst.get(), size, "dst");

	cout << "result: " << (isEqualAfterShift(src.get(), dst.get(), size) ?
	               "equal" : "not equal") << endl;
}

/***********************************************************
 * \brief Detect shift size of sort array
 **********************************************************/
TICKET_FN(54)
{
	cout << "#" << ticket << endl;

	const char usage_msg[] = /** app name */ " -n <array size> -s <shift size> -[ l | r ]";

	if (argc < 6) {
		cout << "usage: " << *argv << usage_msg << endl;
		return;
	}

	int arr_sz = atoi(argv[2]);
	if (strcmp(argv[1], "-n") != 0) {
		cout << "usage: " << *argv << usage_msg << endl;
		return;
	} else if (arr_sz <= 0) {
		cout << "invalid array size = " << arr_sz << endl;
		return;
	}

	int shift = atoi(argv[4]);
	if (strcmp(argv[3], "-s") != 0) {
		cout << "usage: " << *argv << usage_msg << endl;
		return;
	} else if (shift <= 0) {
		cout << "invalid shift = " << shift << endl;
		return;
	}

	if ((strcmp(argv[5], "-l") != 0) && (strcmp(argv[5], "-r") != 0)) {
		cout << "invalid direction = " << argv[5] << endl;
		return;
	}

	ArrayShiftDirection direction = (strcmp(argv[5], "-l") == 0) ? ArrayShiftDirection :: Left : ArrayShiftDirection :: Right;

	boost :: scoped_array<int> arr(new int[arr_sz]);

	fillRandom(arr, arr_sz);

	print(arr.get(), arr_sz, "src", "\t");

	sort(arr.get(), arr.get() + arr_sz, less<int>());

	print(arr.get(), arr_sz, "sort", "\t");

	(direction == ArrayShiftDirection :: Left) ?
			ArrayShift :: left(arr.get(), arr_sz, shift) :
			ArrayShift :: right(arr.get(), arr_sz, shift);

	print(arr.get(), arr_sz, "shift", "\t");

	cout << "shiftSizeOfSortArray() == " << shiftSizeOfSortArray(arr, arr_sz, direction, less<int>()) << endl;

	shift %= arr_sz;

	BOOST_ASSERT(shift == shiftSizeOfSortArray(arr, arr_sz, direction, less<int>()));
}

/***********************************************************
 * \brief Array shift in both sides
 **********************************************************/
TICKET_FN(53)
{
	if (argc < 3) {
		cout << "usage: " << *argv << " k=[val] [ array[0] ... array[n] ]" << endl;
		return;
	}

	if (strncmp(argv[1], "k=", 2) != 0) {
		cout << "usage: " << *argv << " k=[val] [ array[0] ... array[n] ]" << endl;
		return;
	}

	int k = atoi(argv[1] + 2);
	if (k < 0) {
		cout << "invalid K = " << k << endl;
		return;
	}

	boost :: scoped_array<char> arr_left;

	fillCmd(arr_left, argc - 2, argv + 2);

	print(arr_left.get(), argc - 2);

	ArrayShift :: right(arr_left.get(), argc - 2, k);

	cout << " >> " << k << endl;

	print(arr_left.get(), argc - 2);

	cout << "-------------------------" << endl;

	boost :: scoped_array<char> arr_right;

	fillCmd(arr_right, argc - 2, argv + 2);

	print(arr_right.get(), argc - 2);

	ArrayShift :: left(arr_right.get(), argc - 2, k);

	cout << " << " << k << endl;

	print(arr_right.get(), argc - 2);
}

/***********************************************************
 * \brief   Find common part in two array without repeats
 * \details Usage: <array1 size> "<array1>" <array2 size> "<array2>"
 **********************************************************/
TICKET_FN(66)
{
	cout << "#" << ticket << endl;

	if (argc < 5) {
		cout << "usage: " << *argv << " <array1 size> \"<array1>\" <array2 size> \"<array2>\"\n";
		return;
	}

	int sz1 = atoi(argv[1]), sz2 = atoi(argv[3]);
	if ((sz1 < 0) || (sz2 < 0)) {
		cout << "array size should be positive or zero\n";
		return;
	}

	boost :: scoped_array<int> arr1, arr2;
	if (sz1 > 0) {
		arr1.reset(new int[sz1]);
	}

	if (sz2 > 0) {
		arr2.reset(new int[sz2]);
	}

	if (!fillFromString(arr1.get(), sz1, argv[2]) || !fillFromString(arr2.get(), sz2, argv[4])) {
		cout << "size of array is incorrect\n";
		return;
	}

	boost :: scoped_array<int> common;
	
	int common_sz = findCommonPartOfTwoArrays(arr1.get(), sz1, arr2.get(), sz2, common);
	
	switch (common_sz) {
		case(0) : cout << "no common elements\n"; break;
		case(-1): cout << "memory error\n"; break;
		default: {
			cout << "common array size = " << common_sz << endl;
			print(common.get(), common_sz, "common array: ");
		}
	};

}

/***********************************************************
 * \brief   Diff for array
 * \details Usage: <array1 size> "<array1>" <array2 size> "<array2>"
 **********************************************************/
TICKET_FN(36)
{
	cout << "#" << ticket << endl;

	if (argc < 5) {
		cout << "usage: " << *argv << " <array1 size> \"<array1>\" <array2 size> \"<array2>\"\n";
		return;
	}

	int sz1 = atoi(argv[1]), sz2 = atoi(argv[3]);
	if ((sz1 < 0) || (sz2 < 0)) {
		cout << "array size should be positive or zero\n";
		return;
	}

	boost :: scoped_array<int> arr1, arr2;
	if (sz1 > 0) {
		arr1.reset(new int[sz1]);
	}

	if (sz2 > 0) {
		arr2.reset(new int[sz2]);
	}

	if (!fillFromString(arr1.get(), sz1, argv[2]) || !fillFromString(arr2.get(), sz2, argv[4])) {
		cout << "size of array is incorrect\n";
		return;
	}

	std :: function<void(int)> del = [](int v) { cout << " [-]" << v << " "; };
	std :: function<void(int)> add = [](int v) { cout << " [+]" << v << " "; };

	cout << "Diff of array\n";

	diff(arr1.get(), sz1, arr2.get(), sz2, del, add);

	std :: cout << endl;
}

/***********************************************************
 * \brief Merge two sorted arrays
 ***********************************************************/
TICKET_FN(94)
{
	cout << "#" << ticket << ": merge sorted arrays\n";

	if (argc < 4) {
		cout << "usage: " << *argv << " size1 \"array1\" size2 \"array2\"\n";
		return;
	}

	int size1 = atoi(argv[1]), size2 = atoi(argv[3]);
	if (size1 < 0 || size2 < 0) {
		cout << "size of arrays must be >=0 (size1 = " << size1 << ", size2 = " << size2 << ")\n";
		return;
	}

	unique_ptr<int[]> arr1(new int[size1]), arr2(new int[size2]);

	if (!fillFromString(arr1.get(), size1, argv[2]) || !fillFromString(arr2.get(), size2, argv[4])) {
		cout << "invalid size of array\n";
		return;
	}

	unique_ptr<int[]> merged;

	std :: sort(arr1.get(), arr1.get() + size1, std :: less<int>());

	std :: sort(arr2.get(), arr2.get() + size2, std :: less<int>());

	int size = mergeSortedArrays(arr1, size1, arr2, size2, merged);

	print(merged.get(), size, "merged array: ");
}

TICKET_FN(65)
{
	cout << "#" << ticket << ": find min[k] element\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size> <min[k]>\n";
		return;
	}

	int size = atoi(argv[1]), min_k = atoi(argv[2]);
	if ((size <= 0) || (min_k < 0)) {
		cout << "invalid input params\n";
		return;
	}

	boost :: scoped_array<int> arr(new int[size]);

	fillRandom(arr, static_cast<size_t>(size), 30);

	print(arr.get(), size, "src: ");

//	char str[] = "0, -2, 4, -9, -3, 6, 1, -1, -19, 1";

//	if (!fillFromString(arr.get(), 10, str)) {
//		cout << "invalid size of array\n";
//		return;
//	}

	FindMinElementOfIndexK algo;
	algo.doTask(arr.get(), size, min_k + 1);

	int min_k_val = -1;

	if (findMinimalValueIndexOfK(arr.get(), size, min_k, min_k_val) == -1)
		cout << "invalid input param \"minimalIndex\"\n";
	else
		cout << "min[" << min_k << "] = " << min_k_val << endl;
}

TICKET_FN(281)
{
	cout << "#" << ticket << ": random select from stream\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <stream size> <selected size>\n";
		return;
	}

	int stream_sz = atoi(argv[1]), selected_sz = atoi(argv[2]);
	if (stream_sz <= 0 || selected_sz <= 0) {
		cout << "invalid input params\n";
		return;
	}

	boost :: scoped_array<int> stream(new int[stream_sz]);
	fillRandom(stream, stream_sz, 50);
	print(stream.get(), stream_sz, "stream: ");

	boost :: scoped_array<int> selected(new int[selected_sz]);
	selected_sz = selectRandomElementsInStream(stream.get(), stream_sz, selected.get(), selected_sz);
	print(selected.get(), selected_sz, "selected: ");
}

TICKET_FN(117)
{
	cout << "#" << ticket << ": random permutation\n";

	int src[] = { 0, 1, 2, 3, 4, 5, 6 };

	int len = sizeof(src) / sizeof(src[0]);

	print(src, len, "src: ");

	int dst[len];

	std :: memcpy(dst, src, sizeof(src));

	permutateRandom(dst, len);

	print(dst, len, "dst: ");

	permutateRandom(src, dst, len);

	print(dst, len, "dst: ");
}

TICKET_FN(118)
{
	cout << "#" << ticket << ": random select from array\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <array size> <selected size>\n";
		return;
	}

	int sz = atoi(argv[1]), s_sz = atoi(argv[2]);
	if ((sz <= 0) || (s_sz <= 0))  {
		cout << "invalid input pararms\n";
		return;
	}

	boost :: scoped_array<int> arr(new int[sz]), selected(new int[s_sz]);

	fillRandom(arr, sz, 50);

	print(arr.get(), sz, "src: ");

	int actual = selectRandomElementsInArray(arr.get(), sz, selected.get(), s_sz);

	print(selected.get(), actual, "selected:");
}

TICKET_FN(116)
{
	cout << "#" << ticket << ": generate [1..7] values using generator with [1..5]\n";

	std::mt19937 generator(time(nullptr));
	std :: uniform_int_distribution<int> dist(1, 5); /**< input expression */

	int val = 0;
	do {
		val = (dist(generator) - 1) * 5 + (dist(generator) - 1);
		cout << "val = " << val << endl;
	} while(val > 20);

	val = val / 3 + 1;

	cout << "final: " << val << endl;
}

TICKET_FN(121)
{
	cout << "#" << ticket << ": minimal coins number in change\n";

	if (argc < 4) {
		cout << *argv << ": <coins quantity> <coins> <change>\n";
		return;
	}

	int quantity = atoi(argv[1]);
	if (quantity <= 0) {
		cout << "invalid coins quantity: " << quantity << endl;
		return;
	}

	boost :: scoped_array<int> coin(new int[quantity]);
	fillFromString(coin.get(), quantity, argv[2]);

	int change = atoi(argv[3]);
	if (change < 0) {
		cout << "invalid change: " << change << endl;
		return;
	}

	bool invalid_coin = false;
	cout << "coins:";
	for (int i = 0; i < quantity; ++i) {
		if (coin[i] <= 0) {
			invalid_coin = true;
			cout << " " << coin[i] << "(invalid)";
		} else
			cout << " " << coin[i];
	}
	cout << endl;

	if (invalid_coin)
		return;

	boost :: scoped_array<int> change_coin(new int[quantity]);

//	int res = greedy :: makeMinChange(coin.get(), quantity, change, change_coin.get());

	int res = dp :: makeMinChange(coin.get(), quantity, change, change_coin.get());

	cout << "minimal change (" << change << ") size = " << res << endl;

	if (res > 0) {
		cout << "change:";
		for (int i = 0; i < quantity; ++i) {
			while (change_coin[i]-- > 0) {
				cout << " " << coin[i];
			}
		}
		cout << endl;
	}
}

TICKET_FN(58)
{
	cout << "#" << ticket << ": continuous subsequence with max sum\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <sequence size> [\"a[0] a[1] .. a[n]\"]\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid size: " << size << endl;
		return;
	}

	boost :: scoped_array<int> arr;

	if (argc == 3) {
		arr.reset(new int[size]);
		if (!fillFromString(arr.get(), size, argv[2])) {
			cout << "incomplete array\n";
			return;
		}
	}
	else
		fillRandom(arr, size, 25);

	int start = -1, finish = -1;

	cout << "input sequence:";
	for (int i = 0; i < size; ++i)
		cout << " " << arr[i];
	cout << endl;

	int max = dp :: findContinuousSubsequenceWithMaxSum(arr.get(), size, start, finish);
	cout << "subsequence:";
	for (int i = start; i <= finish; ++i)
		cout << " " << arr[i];
	cout << "\nmaximal sum [" << start << ", " << finish << "] = " << max << endl;
}

TICKET_FN(288)
{
	cout << "#" << ticket << ": sum of array without comparators\n";

//	int a0[] = {};
	int a1[] = { 1 };
	int a2[] = { 1, 2 };
	int a3[] = { 1, 2, 3 };
	int a4[] = { 1, 2, 3, 4 };
	int a5[] = { 1, 2, 3, 4, 5 };
	int a6[] = { 1, 2, 3, 4, 5, 6 };

//	cout << "sum(a0) = " << sumOfArrayWithoutComparators(a0, 0) << endl;
	cout << "sum(a1) = " << sumOfArrayWithoutComparators(a1, 1) << endl;
	cout << "sum(a2) = " << sumOfArrayWithoutComparators(a2, 2) << endl;
	cout << "sum(a3) = " << sumOfArrayWithoutComparators(a3, 3) << endl;
	cout << "sum(a4) = " << sumOfArrayWithoutComparators(a4, 4) << endl;
	cout << "sum(a5) = " << sumOfArrayWithoutComparators(a5, 5) << endl;
	cout << "sum(a6) = " << sumOfArrayWithoutComparators(a6, 6) << endl;
}

TICKET_FN(114)
{
	cout << "#" << ticket << ": Pythagorean triple O(N^2)\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size>  [array0 array1 .. arrayN]\n";
		return;
	}

	int sz = atoi(argv[1]);
	if (sz < 3) {
		cout << "invalid array size\n";
		return;
	}

	boost :: scoped_array<int> arr;

	if (argc == 2)
		fillRandom(arr, sz, 100);
	else
		fillCmd(arr, sz, argv + 2);

	cout << "input array:";
	for_each(arr.get(), arr.get() + sz, [](const int & v) { cout << " " << v; });
	cout << endl;

	findTriplet_SumOfQuad(arr, sz);
}

TICKET_FN(115)
{
	cout << "#" << ticket << ": maximal growing subsequence\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " [size] \"[array[0] ... array[n]\"\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid size\n";
		return;
	}

	boost :: scoped_array<int> arr(new int[size]), seq(new int[size]);
	if (!fillFromString(arr.get(), size, argv[2])) {
		cout << "invalid array\n";
		return;
	}

	int max = maxGrowingSubsequence(arr.get(), size, seq.get());

	cout << "maximal growing subsequence:";
	for (int i = 0; i < max; ++i) {
		cout << " " << seq[i];
	}
	cout << endl;
}


/************************************************************
 * \brief Find the element repeated more than n/2 times
 ************************************************************/
TICKET_FN(109)
{
	cout << "#" << ticket << ": find the element repeated more than n/2 times\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <array size> \"array\"\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid array size\n";
		return;
	}

	unique_ptr<int[]> ptr(new int[size]);

	if (!fillFromString(ptr.get(), size, argv[2])) {
		cout << "invalid array\n";
		return;
	}

	int * candidate = findElementRepeatedMoreThanHalf(ptr.get(), size);
	if (candidate) {
		cout << "candidate = " << *candidate << endl;
	}
	else {
		cout << "not found\n";
	}
}

TICKET_FN(233)
{
	cout << "#" << ticket << ": make maximal pseudo number by merge array elements\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size> \"<array1 array2 ... arrayN>\"\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid array size\n";
		return;
	}

	unique_ptr<int[]> array(new int[size]);

	if (!fillFromString(array.get(), size, argv[2])) {
		cout << "invalid input array\n";
		return;
	}

	buildMaximalMergeNumber(array.get(), size);

	print(array.get(), size, "result:");

	cout << "maximal merge value = ";
	for (int i = 0; i < size; ++i) {
		cout << array[i];
	}
	cout << endl;
}

TICKET_FN(57)
{
	cout << "#" << ticket << ": find median with memory limit\n";

//	cout << "test median position functions\n";
//	for (int i = 0; i < 25; ++i)
//		cout << "median (" << i << "): high = " << median(i) << " low = " << lowMedian(i) << endl;
//	cout << endl;

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size>\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid array size\n";
		return;
	}

	boost :: scoped_array<int> arr(new int[size]);

	fillRandom(arr, static_cast<std :: size_t>(size), 50);

	print(arr.get(), size, "input: ");

	int m = findMedianMemLimit(arr.get(), size);

	int m2 = 0;

	findMinimalValueIndexOfK(arr.get(), size, median(size), m2);

	cout << "median (" << median(size) << ") " << m << " == " << m2 << endl;
}

/**
 * #311: ZigZag problem
 */
TICKET_FN(311)
{
	if (argc < 3) {
		cout << "usage: " << *argv << " <array size> <array>\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid size (0..INT_MAX]\n";
		return;
	}

	std :: unique_ptr<int[]> arr(new int[size]);
	if (!fillFromString(arr.get(), size, argv[2])) {
		cout << "invalid input array\n";
		return;
	}

	cout << "longest zig-zag subsequence has length = " << dp :: longestZigZag(arr.get(), size) << endl;
}

TICKET_FN(60)
{
	cout << "#" << ticket << ": sequence with sum closest to zero\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <array size> <array>\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid size = " << size << endl;
		return;
	}

	unique_ptr<int[]> arr(new int[size]);

	if (!fillFromString(arr.get(), size, argv[2])) {
		cout << "reading array fail\n";
		return;
	}

	pair<int, int> res = findSubsequenceClosestZero(arr.get(), size);

	//std :: cout << "start = " << res.first << " end = " << res.second << std :: endl;
	cout << "seq (" << res.first << ", " << res.second << "):";
	for (int i = res.first; i < res.second; ++i)
		cout << " " << arr[i];
	cout << endl;
}

TICKET_FN(59)
{
	cout << "#" << ticket << ": maximum product subarray\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <array size> <array>\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid size = " << size << endl;
		return;
	}

	unique_ptr<int[]> arr(new int[size]);

	if (!fillFromString(arr.get(), size, argv[2])) {
		cout << "reading array fail\n";
		return;
	}

	std :: list<int> subseq;

	cout << "maximum product: " << maximumProductSubsequence(arr.get(), size, subseq) << std :: endl;
	cout << "subseq:";
	for (auto &i : subseq)
		cout << " " << i;
	cout << endl;
}

int main(int argc, char ** argv)
{
	/* uncomment one of them */

//	ticket_59(argc, argv);

//	ticket_60(argc, argv);

// ticket_311(argc, argv);

//	ticket_57(argc, argv);

//	ticket_233(argc, argv);

//	ticket_109(argc, argv);

//	ticket_115(argc, argv);

//	ticket_114(argc, argv);

//	ticket_288(argc, argv);

//	ticket_58(argc, argv);

//	ticket_121(argc, argv);

//	ticket_116(argc, argv);

//	ticket_118(argc, argv);

//	ticket_117(argc, argv);

//	ticket_281(argc, argv);

//	ticket_65(argc, argv);

//	ticket_94(argc, argv);

//	ticket_36(argc, argv);

//	ticket_66(argc, argv);

//	ticket_54(argc, argv);

//	ticket_53(argc, argv);

//	ticket_52(argc, argv);

//	ticket_42(argc, argv);

//	ticket_62(argc, argv);

//	ticket_44(argc, argv);

//	FindMinElementOfIndexK algo;

///	algo.doTask(argc, argv);

	return 0;
}

