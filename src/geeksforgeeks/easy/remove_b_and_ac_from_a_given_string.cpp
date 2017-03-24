/*
   Given a string, eliminate all “b” and “ac” in the string, replace them in-place and iterate over the string once.

   Input:
   The first line of input contains an integer T denoting the number of test cases. The description of T test cases follows.
   Each test case contains a string of length N.

   Output:
   Print the resultant substring after removing 'b' and 'ac' from string.

   Constraints:
   1 ≤ T ≤ 200
   1 ≤ N ≤ 200

   Example:
   Input:
   2
   acbac
   aababc

   Output:
   <blank>
   aaac
 */

#include <iostream>
#include <string>

using namespace std;

// speed O(N)
// memory O(1)
void remove_b_and_ac_from_a_given_string(string &s)
{
	size_t new_len = 0, pos = 0;
	while (pos < s.length()) {
		if (s[pos] == 'b') {
			++pos;
		} else if (s[pos] == 'a' /*&& pos + 1 < s.length()*/ && s[pos + 1] == 'c') {
			pos += 2;
		} else
			s[new_len++] = s[pos++];
	}

	s.resize(new_len);
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;
		remove_b_and_ac_from_a_given_string(s);
		cout << s << endl;
	}

	return 0;
}
