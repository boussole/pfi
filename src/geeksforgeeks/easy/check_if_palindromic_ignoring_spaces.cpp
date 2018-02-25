/*
Given a string, check if it is a palindrome by ignoring spaces. E.g. race car would be a palindrome.

Input:
The first line of input contains an integer T denoting the no of T test cases. The only line in each test case consists of String S.

Output:
For each test case in a new line print YES if String is palindromic else print NO.

Constraints:
1<=T<=100
1<=|Length of String|<=1000

Example:
Input:
2
race car
abcaa

Output:
YES
NO
 */

#include <iostream>
#include <string>

using namespace std;

bool is_palindromic_ignoring_spaces(const string &s)
{
	int left = 0, right = s.length() - 1;
	while (left < right) {
		bool check_symbols = true;

		if (isspace(s[left])) {
			++left;
			check_symbols = false;
		}

		if (isspace(s[right])) {
			--right;
			check_symbols = false;
		}

		if (check_symbols) {
			if (s[left++] != s[right--]) {
				return false;
			}
		}
	}

	return true;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		getline(cin >> ws, s);
		cout << (is_palindromic_ignoring_spaces(s) ? "YES" : "NO") << endl;
	}

	return 0;
}
