/*
   Given an string in roman no format (s)  your task is to convert it to integer .

   Input:
   The first line of each test case contains the no of test cases T.
   Then T test cases follow.
   Each test case contains a string s denoting the roman no.

   Output:
   For each test case in a new line print the integer representation of roman number s.

   Constraints:
   1<=T<=100
   1<=roman no range<4000

   Example:
      Input
      2
      V
      III

      Output
      5
      3
 */

#include <assert.h>

#include <iostream>
#include <string>

using namespace std;

// based on upper case acsii symbols
// speed O(1)
// memory O(M)
// note: really it is a short array which can be situated in a cache,
//       so it's enough to run and find digit
int roman_hash(char sym)
{
	static int h_tbl[7] = {1000, 10, 5, 1, 100, 500, 50};
	
	return h_tbl[sym % 7 - 3 * (sym / 88)];
}

// speed O(N)
// memory O(1)
uint32_t roman_number_to_integer(const string &s)
{
	uint32_t val = 0;
	size_t i = 0, dig = 0; /* it is impossible roman value */

	while (i < s.length()) {
		if (!dig) {
			dig = roman_hash(s[i]);
			val += dig;
		} else {
			size_t new_dig = roman_hash(s[i]);
			if (new_dig > dig) {
				val = val + new_dig - 2 * dig;
				dig = 0;
			} else {
				val += new_dig;
				dig = new_dig;
			}
		}

		++i;
	}

	return val;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;
		cout << roman_number_to_integer(s) << endl;
	}

	return 0;
}

