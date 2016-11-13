/**
 * \file main.cpp
 *
 * \author boussole
 */

#include "matrix.h"

using namespace boost :: numeric :: ublas;
using namespace conq_matrix;
using namespace std;

void __test_forEachSubMatrixEdgeElement()
{
	/* 1 x 1 */
	std :: cout << "[1 x 1]\n";
	matrix<int> m1(1, 1);
	fillOutStub(m1);
	print(m1);
	int s = 0;
	forEachSubMatrixEdgeElement(m1, 0, boost :: bind<void>([](int & sum, int element)->void { sum += element; }, ref(s), _1));
	cout << "sum = " << s << endl;

	/* 2 x 2 */
	std :: cout << "[2 x 2]\n";
	matrix<int> m22(2, 2);
	fillOutStub(m22);
	print(m22);
	s = 0;
	forEachSubMatrixEdgeElement(m22, 0, boost :: bind<void>([](int & sum, int element)->void { sum += element; }, ref(s), _1));
	cout << "sum = " << s << endl;

	/* 3 x 3 */
	std :: cout << "[3 x 3]\n";
	matrix<int> m33(3, 3);
	fillOutStub(m33);
	print(m33);
	s = 0;
	forEachSubMatrixEdgeElement(m33, 0, boost :: bind<void>([](int & sum, int element)->void { sum += element; }, ref(s), _1));
	cout << "sum = " << s << endl;
	s = 0;
	forEachSubMatrixEdgeElement(m33, 1, boost :: bind<void>([](int & sum, int element)->void { sum += element; }, ref(s), _1));
	cout << "sum = " << s << endl;

	/* 4 x 4 */
	std :: cout << "[4 x 4]\n";
	matrix<int> m44(4, 4);
	fillOutStub(m44);
	print(m44);
	s = 0;
	forEachSubMatrixEdgeElement(m44, 0, boost :: bind<void>([](int & sum, int element)->void { sum += element; }, ref(s), _1));
	cout << "sum = " << s << endl;
	s = 0;
	forEachSubMatrixEdgeElement(m44, 1, boost :: bind<void>([](int & sum, int element)->void { sum += element; }, ref(s), _1));
	cout << "sum = " << s << endl;

	/* 5 x 5 */
	std :: cout << "[5 x 5]\n";
	matrix<int> m55(5, 5);
	fillOutStub(m55);
	print(m55);
	s = 0;
	forEachSubMatrixEdgeElement(m55, 0, boost :: bind<void>([](int & sum, int element)->void { sum += element; }, ref(s), _1));
	cout << "sum = " << s << endl;
	s = 0;
	forEachSubMatrixEdgeElement(m55, 1, boost :: bind<void>([](int & sum, int element)->void { sum += element; }, ref(s), _1));
	cout << "sum = " << s << endl;
	s = 0;
	forEachSubMatrixEdgeElement(m55, 2, boost :: bind<void>([](int & sum, int element)->void { sum += element; }, ref(s), _1));
	cout << "sum = " << s << endl;
}

void __test_forEachElementInSubMatrix()
{
	std :: cout << "[5 x 5]\n";
	matrix<int> m5(5, 5);
	fillOutStub(m5);
	print(m5);

	cout << "test 1\n";
	forEachElementInSubMatrix(m5, 0, 1, 0, 1, [](int element) { cout << "element = " << element << endl; });

	cout << "test 2\n";
	forEachElementInSubMatrix(m5, 2, 2, 2, 3, [](int element) { cout << "element = " << element << endl; });

	cout << "test 3\n";
	forEachElementInSubMatrix(m5, 0, 4, 1, 3, [](int element) { cout << "element = " << element << endl; });
}

TICKET_FN(237)
{
	cout << "#" << ticket << endl;

	std :: cout << "[1 x 1]\n";
	matrix<int> m1(1, 1);
	fillOutRand(m1, 100);
	print(m1);
	SubMatrix sm;
	int largest_sum = findSubMatrixWithLargestSum(m1, sm);
	if (sm.isValid()) {
		cout << "largest sum = " << largest_sum << endl;
		sm.print(m1);
	}

	std :: cout << "-------------------------------------\n[2 x 2]\n";
	matrix<int> m2(2, 2);
	fillOutRand(m2, 100);
	print(m2);
	largest_sum = findSubMatrixWithLargestSum(m2, sm);
	if (sm.isValid()) {
		cout << "largest sum = " << largest_sum << endl;
		sm.print(m2);
	}

	/* 3 x 3 */
	std :: cout << "-------------------------------------\n[3 x 3]\n";
	matrix<int> m3(3, 3);
	fillOutRand(m3, 100);
	print(m3);
	largest_sum = findSubMatrixWithLargestSum(m3, sm);
	if (sm.isValid()) {
		cout << "largest sum = " << largest_sum << endl;
		sm.print(m3);
	}

	/* 4 x 4 */
	std :: cout << "-------------------------------------\n[4 x 4]\n";
	matrix<int> m4(4, 4);
	fillOutRand(m4, 100);
	print(m4);
	largest_sum = findSubMatrixWithLargestSum(m4, sm);
	if (sm.isValid()) {
		cout << "largest sum = " << largest_sum << endl;
		sm.print(m4);
	}

	/* 5 x 5 */
	std :: cout << "-------------------------------------\n[5 x 5]\n";
	matrix<int> m5(5, 5);
	fillOutRand(m5, 100);
	print(m5);
	largest_sum = findSubMatrixWithLargestSum(m5, sm);
	if (sm.isValid()) {
		cout << "largest sum = " << largest_sum << endl;
		sm.print(m5);
	}

//	__test_forEachSubMatrixEdgeElement();
//	__test_forEachElementInSubMatrix();
}

TICKET_FN(40)
{
	cout << "#" << ticket << endl;

	matrix<int> m1[] = {
		matrix<int>(1, 1),
		matrix<int>(2, 2),
		matrix<int>(3, 3),
		matrix<int>(4, 4),
		matrix<int>(5, 5),
		matrix<int>(6, 6)
	};

	matrix<int> m2[] = {
		matrix<int>(1, 1),
		matrix<int>(2, 2),
		matrix<int>(3, 3),
		matrix<int>(4, 4),
		matrix<int>(5, 5),
		matrix<int>(6, 6)
	};

	matrix<int> m3[] = {
		matrix<int>(1, 1),
		matrix<int>(2, 2),
		matrix<int>(3, 3),
		matrix<int>(4, 4),
		matrix<int>(5, 5),
		matrix<int>(6, 6)
	};

	for (size_t i = 0; i < boost::size(m1); i++) {
		cout << "test №" << i << " [" << m1[i].size1() << ", " << m1[i].size2() << "]\n";
		fillOutStub(m1[i]);
		fillOutStub(m2[i]);
		fillOutStub(m3[i]);
		cout << "src\n";
		print(m1[i]);
		rotate(m1[i], RotationAngle :: _90);
		rotate_f(m2[i], RotationAngle :: _90);
		rotate_90(m3[i]);
		cout << "dst\n";
		print(m1[i]);
		BOOST_ASSERT((m1[i] == m2[i]) && (m2[i] == m3[i]));
	}
}

TICKET_FN(238)
{
	cout << "#" << ticket << endl;

	int rows = 0, cols = 0;

	cout << "enter rows: ";
	cin >> rows;

	if (rows <= 0) {
		cout << "invalid rows value\n";
		return;
	}

	cout << "enter cols: ";
	cin >> cols;

	if (cols <= 0) {
		cout << "invalid cols value\n";
		return;
	}

	matrix<int> m(rows, cols);

	fillOutRand(m, 100);

	cout << "matrix [" << rows << ", " << cols << "]" << endl;

	print(m);

	sortRowAndCol(m);

	cout << "sorted matrix [" << rows << ", " << cols << "]" << endl;

	print(m);

	int value = 0;
	cout << "enter value for search: ";
	cin >> value;

	point_xy pos;
	cout << "Slow algo\n";
	if (findValueInHVSortMatrix(m, value, pos))
		cout << "value = " << value << " found in i = " << pos.x() << ", j = " << pos.y() << endl;
	else
		cout << "value = " << value << " not found\n";

	cout << "Fast algo\n";
	if (book :: findValueInHVSortMatrix(m, value, pos))
		cout << "value = " << value << " found in i = " << pos.x() << ", j = " << pos.y() << endl;
	else
		cout << "value = " << value << " not found\n";

	cout << "Binary search\n";
	if (book :: findValueInHVSortMatrixBin :: doIt(m, value, pos))
		cout << "value = " << value << " found in i = " << pos.x() << ", j = " << pos.y() << endl;
	else
		cout << "value = " << value << " not found\n";
}

TICKET_FN(63)
{
	cout << "#" << ticket << ": find celebrety problem\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <people num> " << "<1 (with) | 0 (without) celebrety>\n";
		return;
	}

	int people = atoi(argv[1]);
	if (people <= 0) {
		cout << "invalid people num\n";
		return;
	}

	int with_celebrety = atoi(argv[2]);
	matrix<int> m(people, people);
	srand(time(NULL) + getpid());

	int celebrety = -1;

	if (with_celebrety == 1) {
		celebrety = rand() % people;
		cout << "celebrety is №" << celebrety << endl;
		for (int i = 0; i < people; ++i) {
			for (int j = 0; j < people; ++j) {
				if (i == j)
					m(i, j) = 1;
				else {
					if (i == celebrety)
						m(i, j) = 0;
					else if (j == celebrety)
						m(i, j) = 1;
					else
						m(i, j) = rand() % 2;
				}
			}
		}

	} else if (with_celebrety == 0) {
		for (int i = 0; i < people; ++i) {
			for (int j = 0; j < people; ++j) {
				m(i, j) = (i == j) ? 1 : rand() % 2;
			}
		}
		// exclude potencial celebrety
		for (int i = 0; i < people; ++i) {
			bool false_celebrety = true;
			for (int j = 0; j < people; ++j) {
				if (i != j) {
					if (m(i, j) == 1) {
						false_celebrety = false;
						break;
					}
				}
			}
			if (false_celebrety) {
				for (int j = 0; j < people; ++j) {
					if (i != j) {
						if (m(j, i) == 0) {
							false_celebrety = false;
							break;
						}
					}
				}
				if (false_celebrety) {
					int r = 0;
					for (r = 0; r == i; r = rand() % people);
					m(i, r) = 1;
				}
			}
		}
		cout << "no celebrety\n";
	} else {
		cout << "invalid option with | without celebrety\n";
		return;
	}

	print(m);

	int c = findCelebrety(m, people);
	if (c < 0)
		cout << "celebrety hasn't been found\n";
	else
		cout << "celebrety = " << c << endl;
}

TICKET_FN(239)
{
	cout << "#" << ticket << " min(k) in sort matrix\n";

	if (argc < 4) {
		cout << "usage: " << *argv << " <N> <M> <min(k)>\n";
		return;
	}

	int n = atoi(argv[1]), m = atoi(argv[2]), min_k = atoi(argv[3]);
	if (n <= 0 || m <= 0 || min_k <= 0) {
		cout << "n, m, min(k) must be positive\n";
		return;
	}

	if (n * m < min_k) {
		cout << "min_k should be less than " << n * m << endl;
		return;
	}

	matrix<int> matrix(n, m);

	fillOutRand(matrix, 30);

	sortRowAndCol(matrix);

	cout << "sorted ( m [" << n << ", " << m << "] )\n";

	print(matrix);

	cout << min_k << "-th minimal = " << findKthSmallestInHVSortMatrix(matrix, static_cast<std :: size_t>(min_k)) << endl;
}

int main(int argc, char ** argv)
{
	/* uncomment one of them */

//	ticket_239(argc, argv);

//	ticket_63(argc, argv);

//	ticket_238(argc, argv);

//	ticket_237(argc, argv);

//	ticket_40(argc, argv);

	return 0;
}
