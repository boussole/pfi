/*
Given a string, the task is to remove all  duplicate characters from the string and print the resultant string.  The order of remaining characters in the output should be same as in the original string.

Input:
The first line of input contains an integer T denoting the number of test cases. The description of T test cases follows.
Each test case contains a string of length N.

Output:
Print the resultant substring after removing duplicate characters from string.

Constraints:
1 ≤ T ≤ 100
1 ≤ N ≤ 100

Example:
Input:
2
geeksforgeeks
HappyNewYear

Output:
geksfor
HapyNewYr
 */

#include <iostream>
#include <string>

using namespace std;

void remove_all_duplicates_from_a_given_string(string &s)
{
	bool sym_hash[255] = {0};
	size_t dst = 0;
	for (size_t src = 0; src < s.length(); ++src) {
		uint8_t pos = s[src] - 'a';
		if (!sym_hash[pos]) {
			sym_hash[pos] = true;
			s[dst++] = s[src];
		}
	}

	s.resize(dst);
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;
		remove_all_duplicates_from_a_given_string(s);
		cout << s << endl;
	}

	return 0;
}
