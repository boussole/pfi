/*
   A number is a special number if it’s digits only consist 0, 1, 2, 3, 4 or 5.
   Given a number n and we have to find n-th Special Number.

   Input:
      First line of input contains the number of test cases.
      The only line of the test case contains N.

   Output:
      Print the nth special number.

   Constraints:
   1<=T<=100
   1<=N<=100000

   Example:
      Sample Input:
      2
      6
      10

   Sample Output:
      5
      13
 */
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/**
 * speed  O(logN)
 * memory O(1)
 */
string special_number(unsigned int val)
{
	assert(val > 0);
	string s;
	--val;

	unsigned int div = val / 6, mod = val % 6;
	while (div > 0) {
		val = div;
		s += to_string(mod);
		div = val / 6;
		mod = val % 6;
	}

	if (mod || s.empty())
		s += to_string(mod);

	reverse(s.begin(), s.end());

	return s;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		unsigned int val;
		cin >> val;
		string s = special_number(val);
		cout << s << endl;
	}

	return 0;
}
