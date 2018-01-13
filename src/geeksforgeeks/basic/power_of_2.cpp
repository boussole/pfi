/*
   Given a positive integer N, check if N is a power of 2.

   Input:
   The first line contains 'T' denoting the number of test cases. Then follows description of test cases.
   Each test case contains a single positive integer N.

   Output:
   Print "YES" if it is a power of 2 else "NO". (Without the double quotes)

   Constraints:
   1<=T<=100
   0<=N<=10^18

   Example:
   Input :
   2
   1
   98

   Output :
   YES
   ​NO

   Explanation:  (2^0 == 1)
 */

#include <iostream>

using namespace std;

/**
 * 0000 0001
 * 0000 0010
 * 0000 0100
 * 0000 1000
 * 0001 0000
 * 0010 0000
 * 0100 0000
 * 1000 0000
 * .....
 * Value which is a power of 2 contains only one `1`
 * 4       = 0000 1000
 * 4 - 1   = 0000 0111 = 3
 * ~3      = 1111 1000
 *
 * 98      = 0110 0010
 * 98 - 1  = 0110 0001 = 97
 * ~97     = 1001 1110
 *
 * 127     = 0111 1111
 * 127 - 1 = 0111 1110
 *
 * speed  O(N)
 * memory O(N)
 */

bool is_power_of_2(size_t value)
{
	if (value == 0)
		return false;
	return (value & ~(value - 1)) == value;
}

/**
 * another solution, but with the same approach
 * return x && (!(x&(x-1)));
 */

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		size_t value;
		cin >> value;

		cout << (is_power_of_2(value) ? "YES" : "NO") << endl;
	}

	return 0;
}
