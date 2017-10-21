/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include <common/common.h>
#include <array/array.h>
#include <sys/types.h>
#include <unistd.h>
#include "sort.h"

using namespace std;
using namespace conq_array;
using namespace conq_sort;
using namespace boost;

TICKET_FN(228)
{
	cout << "#" << ticket << ": insert sort\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size>\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid array size, should be > 0\n";
		return;
	}

	scoped_array<int> arr(new int[size]);

	BOOST_ASSERT(arr.get());

	fillRandom(arr, static_cast<size_t>(size), 100);

	print(arr.get(), size, "origin: ");

	insertSort(arr.get(), size);

	// book :: insertSort(arr.get(), size);

	print(arr.get(), size, "sorted: ");
}


TICKET_FN(68)
{
	cout << '#' << ticket << ": merge sort\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size>\n";
		return;
	}

	int size = atoi(argv[1]);

	if (size <= 0) {
		cout << "invalid array size, should be > 0\n";
		return;
	}

	scoped_array<int> arr(new int[size]);

	BOOST_ASSERT(arr.get());

	fillRandom(arr, static_cast<size_t>(size), 100);

	print(arr.get(), size, "origin: ");

//	iteration :: mergeSort(arr.get(), size);

//	recursion :: mergeSort(arr.get(), size);

	iteration :: mergeNaturalSort(arr.get(), size);

	testSort(arr.get(), size);

	print(arr.get(), size, "sorted: ");
}

TICKET_FN(225)
{
	cout << '#' << ticket << ": heap sort\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size>\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid array size, should be >0\n";
		return;
	}

	scoped_array<int> arr(new int[size]);

	BOOST_ASSERT(arr.get());

	fillRandom(arr, static_cast<size_t>(size), 100);

	print(arr.get(), size, "origin: ");

	heapSort(arr.get(), size);

	print(arr.get(), size, "sorted: ");

	testSort(arr.get(), size);
}

TICKET_FN(67)
{
	cout << "#" << ticket << ": quick sort\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size>\n";
		return;
	}

	int size = atoi(argv[1]); // size = 6;
	if (size <= 0) {
		cout << "invalid array size, should be >0\n";
		return;
	}

	scoped_array<int> arr(new int[size]);

	BOOST_ASSERT(arr.get());

	fillRandom(arr, static_cast<size_t>(size), 100);

//	char test_1[] = "6 5 4 3 2 1";
//	char test_2[] = "4 7 -1 5 10 0";
//	fillFromString(arr.get(), size, test_1);

	print(arr.get(), size, "origin: ");

//	QuickSort :: rSort_v1<QuickSort :: LastSelectStrategy>(arr.get(), size);
//	QuickSort :: rSort_v1<QuickSort :: CenterSelectStrategy>(arr.get(), size);
//	QuickSort :: rSort_v1<QuickSort :: RandomSelectStrategy>(arr.get(), size);

	QuickSort :: rSort_v2<QuickSort :: CenterSelectStrategy>(arr.get(), size);

	print(arr.get(), size, "sorted: ");

	testSort(arr.get(), size);
}

TICKET_FN(229)
{
	cout << "#" << ticket << ": counting sort\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size>\n";
		return;
	}

	int size =
		atoi(argv[1]);
//		8;
	if (size <= 0) {
		cout << "invalid array size, should be >0\n";
		return;
	}

	scoped_array<int> arr(new int[size]);

	BOOST_ASSERT(arr.get());

	fillRandom(arr, static_cast<size_t>(size), 50);

//	char test_1[] = "2 5 3 0 2 3 0 3";
//	fillFromString(arr.get(), size, test_1);

	print(arr.get(), size, "origin: ");

//	CountingSort :: unstableSort<20>(arr.get(), size);

//	CountingSort :: stableSort<20>(arr.get(), size);

	CountingSort :: sort(arr.get(), size);

	print(arr.get(), size, "sorted: ");

	testSort(arr.get(), size);
}

TICKET_FN(231)
{
	cout << "#" << ticket << ": radix sort\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size>\n";
		return;
	}

	int size = 	atoi(argv[1]);

	if (size <= 0) {
		cout << "invalid array size, should be >0\n";
		return;
	}

	scoped_array<int> arr(new int[size]);

	BOOST_ASSERT(arr.get());

	fillRandom(arr, static_cast<size_t>(size), 50);

//	char test_1[] = "2 5 3 0 2 3 0 3 20";
//	size = 9;
//	fillFromString(arr.get(), size, test_1);
//	char test_2[] = "6 -19 -14 1 -26 -45 19 47 45 -31 -17 -24 -21 25 46 24 -34 37 22 18";
//	size = 20;
//	fillFromString(arr.get(), size, test_2);
//	char test_3[] = "2 1 -2 -1";
//	size = 4;
//	fillFromString(arr.get(), size, test_3);

	print(arr.get(), size, "origin: ");

	radixSort(arr.get(), size);

	print(arr.get(), size, "sorted: ");

	testSort(arr.get(), size);
}

TICKET_FN(230)
{
#define BUCKETS 5
#define ARRAY_SZ 10

	std :: cout << "#" << ticket << ": bucket sort - array size = 10, min\n";

	scoped_array<int> arr(new int[ARRAY_SZ]);

	BOOST_ASSERT(arr.get());

//	char test_1[] = "13 12 42 41 8 30 7 10 15 25";
//	fillFromString(arr.get(), ARRAY_SZ, test_1);

//	char test_2[] = "9 8 7 6 5 4 3 2 1 1";
//	fillFromString(arr.get(), ARRAY_SZ, test_2);

//	char test_3[] = "6 27 26 35 6 23 49 40 2 29";
//	fillFromString(arr.get(), ARRAY_SZ, test_3);

//	char test_4[] = "9 8 7 1 2 3 5 4 6 0";
//	fillFromString(arr.get(), ARRAY_SZ, test_4);

	fillRandom(arr, ARRAY_SZ, 50);

	print(arr.get(), ARRAY_SZ, "origin: ");

	bucketSort<BUCKETS, ARRAY_SZ>(arr.get());

	print(arr.get(), ARRAY_SZ, "sorted: ");

	testSort(arr.get(), ARRAY_SZ);

#undef BUCKETS
#undef ARRAY_SZ
}

TICKET_FN(92)
{
	cout << "#" << ticket << ": sorting of big data\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <array size>\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid array size\n";
		return;
	}


	time_t t = time(NULL);
	pid_t p = getpid();
	string in = string("main_") + to_string(t) + "_" + to_string(p);

	ofstream f(in);
	if (!f.is_open()) {
		cout << "fail to open input file\n";
		return;
	}

	srand(time(NULL));
	for (int i = 0; i < size; ++i) {
		f << (rand() - (RAND_MAX / 2)) % 100 << endl;
	}

	f.close();

	string out;
	sortBigData(in, 10, out);

	cout << "input file = " << in << ", output file = " << out << endl;
}

int main(int argc, char ** argv)
{
	/* uncomment one of them */

//	ticket_92(argc, argv);

//	ticket_230(argc, argv);

//	ticket_231(argc, argv);

//	ticket_229(argc, argv);

//	ticket_67(argc, argv);

//	ticket_225(argc, argv);

//	ticket_68(argc, argv);

//	ticket_228(argc, argv);

	return 0;
}

