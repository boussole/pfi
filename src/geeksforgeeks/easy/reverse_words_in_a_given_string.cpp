/*
   Given a String of length N reverse the words in it. Words are separated by dots.

   Input:
   The first line contains T denoting the number of testcases.
   Then follows description of testcases.
   Each case contains a string containing spaces and characters.

   Output:
   For each test case, output a single line containing the reversed String.

   Constraints:
   1<=T<=20
   1<=Lenght of String<=2000

   Example:
   Input:
   2
   i.like.this.program.very.much
   pqr.mno

   Output:
   much.very.program.this.like.i
   mno.pqr
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/**
 * speed : O(N)
 * memory: O(1)
 */
void reverse_words_in_a_given_string(string &s, char sep = '.')
{
	reverse(s.begin(), s.end());

	size_t curr = s.find(sep);
	int prev = 0;

	auto reverse_word = [&s, &curr, &prev]() {
		for (int c = static_cast<int>(curr) - 1; c > prev; --c, ++prev) {
			swap(s[c], s[prev]);
		}
	};

	while (curr != string::npos) {
		reverse_word();
		prev = curr + 1;
		curr = s.find(sep, prev);
	}

	if (static_cast<size_t>(prev) != s.length()) {
		curr = s.length();
		reverse_word();
	}
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;
		reverse_words_in_a_given_string(s);
		cout << s << endl;
	}

	return 0;
}

