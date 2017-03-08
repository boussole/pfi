/*
   Given a binary string, count number of substrings that start and end with 1.
   For example, if the input string is “00100101”, then there are three substrings “1001”, “100101” and “101”.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Each test case consist of an integer 'n' denoting the string length and next line is followed by a binary string .

   Output:
   Print the number of substring starting and ending with 1 in a separate line.

   Constraints:
   1 ≤ T ≤ 40
   1 ≤ |s| ≤ 1000

   Example:
      Input:
      1
      4
      1111
      Output:
      6
 */

#include <assert.h>

#include <iostream>
#include <string>

using namespace std;

// speed O(N^2)
// memory O(1)
int nr_substrings_v1(const string &s)
{
	int nr = 0;

	for (size_t i = 0; i < s.length(); ++i) {
		if (s[i] == '1') {
			for (size_t j = i + 1; j < s.length(); ++j)
				if (s[j] == '1')
					++nr;
		}
	}

	return nr;
}

// speed O(N)
// memory O(1)
int nr_substrings_v2(const string &s)
{
	int nr_of_1 = 0, nr = 0;

	for (size_t i = 0; i < s.length(); ++i) {
		if (s[i] == '1')
			++nr_of_1;
	}

	if (nr_of_1 > 1) {
		--nr_of_1;
		nr = ((1 + nr_of_1) * nr_of_1) / 2;
	}

	return nr;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int len;
		string s;
		cin >> len;
		cin >> s;
		assert(len == s.length());

		int ans_1 = nr_substrings_v1(s), ans_2 = nr_substrings_v2(s);
		assert(ans_1 == ans_2);
		cout << ans_1 << endl;
	}

	return 0;
}

