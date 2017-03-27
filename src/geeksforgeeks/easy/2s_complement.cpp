/*
   For a given string of binary number find the two’s complement of it.
   Input :
   The first line contains an integer 'T' denoting the total number of test cases.
   The next T lines contains the string S.

   Output:
   In each separate line the two’s complement string should be output.

   Constraints:
   1<=T<=30
   1<=lenght(string)<=10

   Example:
   Input:
   1
   00000101
   Output:
   11111011
 */

#include <assert.h>

#include <iostream>
#include <string>

using namespace std;

// speed  O(N)
// memory O(1)
void two_s_complement(string &s)
{
	assert(!s.empty());

	// positive value, don't change it
//	if (s[0] == '0')
//		return;

	auto inversion = [&](size_t new_len) {
		for (size_t i = 0; i < new_len; ++i)
			s[i] = s[i] == '0' ? '1' : '0';
	};


	size_t last = s.length() - 1;
	do {
		if (s[last] == '1') {
			inversion(last);
			return;
		}
	} while (last-- != 0);

	s.insert(0, 1, '1');
}

int main()
{
	int nr_tests;
	cin >> nr_tests;
	while (nr_tests--) {
		string s;
		cin >> s;
		two_s_complement(s);
		cout << s << endl;
	}

	return 0;
}
