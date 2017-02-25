/*
   Given a base and a number in that base, increment the number by one and print the resulting number in that base only.

   Input:
   First line contains an integer T, denoting the number of test cases.
   Then T test cases follow. Each test case consists of two lines.
   First line contains an integer B, denoting the base.
   Second line contains a four-digit number N.

   Note: {A,B,C,D,E,F} has been used for numbers greater than 9 in any base.

   Output: Print the incremented value of the number.

   Note: You have to ignore the preceding zeroes in input that are used to make it four-digit. Please see example for more details.

   Constraints:
   1 <= T <= 70
   2 <= B <= 16
   0000 <= N <= Max value in that base (e.g. 1111 for base 2, FFFF for base 16, etc.)

   Example:
      Input:
      3
      2
      0010
      13
      2139
      16
      FFFF

      Output:
      11
      213A
      10000
 */

#include <assert.h>

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

char to_string_tbl[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

// 48 ('0'), ..., 57 ('9'),<invalid>, 65 ('A'), ..., 70 ('F')
char from_string_tbl[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15 };

// speed O(N)
// memory O(1)
void increment_v1(int base, string &s)
{
	assert(!s.empty());

	size_t value = 0;

	// convert to dec
	for (int i = s.length() - 1, ratio = 1; i >= 0; --i, ratio *= base)
		value += from_string_tbl[s[i] - 48] * ratio;

	++value;
	s.clear();

	// convert to string
	while (value >= base) {
		s += to_string_tbl[value % base];
		value /= base;
	}

	if (value || s.empty())
		s += to_string_tbl[value];

	reverse(s.begin(), s.end());
}

// speed O(N)
// memory O(1)
void increment_v2(int base, string &s)
{
	int carry = 1;

	int i = s.length() - 1;
	for (; i >= 0 && carry; --i) {
		int value = from_string_tbl[s[i] - 48] + carry;
		s[i] = to_string_tbl[value % base];
		carry = value / base;
	}

	if (i < 0) {
		if (carry)
			s.insert(0, 1, to_string_tbl[carry]);
	} else {
		for (int j = i; j >= 0; --j) {
			if (from_string_tbl[s[j] - 48])
				i = j - 1;
		}

		if (i >= 0)
			s.erase(0, i + 1);
	}
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int base;
		cin >> base;

		string v1, v2;
		cin >> v1;
		v2 = v1;
		increment_v1(base, v1);
		increment_v2(base, v2);

		cout << v2 << endl;
		assert(v1 == v2);
	}

	return 0;
}



