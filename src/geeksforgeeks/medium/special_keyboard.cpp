/*
   Imagine you have a special keyboard with the following keys:
   Key 1:  Prints 'A' on screen
   Key 2: (Ctrl-A): Select screen
   Key 3: (Ctrl-C): Copy selection to buffer
   Key 4: (Ctrl-V): Print buffer on screen appending it after what has already been printed.

   If you can only press the keyboard for N times (with the above four keys),
   write a program to produce maximum numbers of A's.
   That is to say, the input parameter is N (No. of keys that you can press), the output is M (No. of As that you can produce).

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   The first line of each test case is N,N is the number of key.

   Output:
   Print maximum number of A's.  Print -1, if N is greater than 75.

   Constraints:
   1 ≤ T ≤ 50
   1 ≤ N ≤ 75

   Example:
   Input:
   2
   3
   7

   Output:
   3
   9

   Explanation:
   Input:  N = 3
   Output: 3
   We can at most get 3 A's on screen by pressing following key sequence.
   A, A, A

   Input:  N = 7
   Output: 9
   We can at most get 9 A's on screen by pressing following key sequence.
   A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V
 */

#include <assert.h>

#include <iostream>
#include <list>

using namespace std;

// speed O(N) - poly
// memory O(1) - linear
//1 - 3 : 1 2 3          ([1'] = 3)
//
//1 - 4 : 1 2 3 4        ([1'] = 4, [1] = 2)
//
//    5 : 2 3 4 5        ([1'] = 5, [1] = 3, [2] = 4)
//
//    6 : 3 4 5 6        (<[1'] = 6, [1] = 3, [2] = 6,> [3] = 6)
//
//    7 : 4 5 6 9        ([3] = 9, [4] = 8)
//
//    8 : 5 6 9 12       (<[3] = 12,> [4] = 12, [5] = 10)
//
//    9 : 6 9 12 16      ([4] = 16, [5] = 15, [6] = 12)
//
//   10 : 9 12 16 20     (<[4] = 20,> [5] = 20, [6] = 18, [9] = 18)
//
//   11 : 12 16 20  27   (<[5] = 25, [6] = 24,> [9] = 27, [12] = 24)
//
//   12 : 16 20 27  36   (<[9] = 36,> [12] = 36, [16] = 32)
//
//   13 : 20 27  36 48   (<[12] = 48,> [16] = 48, [20] = 40)
//
//   14 : 27  36 48 64   ([16] = 64, [20] = 60, [27] = 54)
//
//   15 : 36 48 64  81   (<[16] = 80, [20] = 80,> [27] = 81)
//
//   16 : 48 64  81 108  ([27] = 108, [48] = 96)
//
//   17 : 64  81 108 144 (<[27] = 135,> [48] = 144, [64] = 128)
//
//   18 : 81 108 144     ([48] = 192, [64] = 192)
size_t special_keyboard(size_t value)
{
	assert(value > 0);

	--value; // to start index from '0'

	size_t nr_a[4] = { 1, 2, 3, 4 };

	if (value < 4)
		return nr_a[value];

	/* pair = { value in a clipboard; produced number of 'A' } */
	list<pair<size_t, size_t> > clipboard;
	clipboard.push_back(make_pair(1, 3)); /* basis */

	int oldest = 0, newest = 3, retval = newest; /* it's a position of rotate buffer */
	for (size_t v = 0; v < value - 2; ++v, oldest = (oldest + 1) % 4, newest = (newest + 1) % 4) {
		retval = newest;
		clipboard.push_back(make_pair(nr_a[oldest], nr_a[oldest]));

		auto max_it = clipboard.begin();
		for (auto it = clipboard.begin(); it != clipboard.end(); ++it) {
			it->second += it->first;
			if (it->second >= max_it->second)
				max_it = it;
		}

		if (max_it != clipboard.begin())
			clipboard.erase(clipboard.begin(), max_it);

		nr_a[newest] = max_it->second;
	}

	return nr_a[retval];
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		size_t value;
		cin >> value;

		cout << special_keyboard(value) << endl;
	}
}

