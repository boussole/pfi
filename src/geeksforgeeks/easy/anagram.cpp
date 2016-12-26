/*
   Given two strings, check whether two given strings are anagram of each other or not.
   An anagram of a string is another string that contains same characters, only the order
   of characters can be different. For example, “act” and “tac” are anagram of each other.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Each test case consist of two strings in 'lowercase' only, in a separate line.

   Output:
   Print "YES" without quotes if the two strings are anagram else print "NO".

   Constraints:
   1 ≤ T ≤ 30
   1 ≤ |s| ≤ 100

   Example:
      Input:
      2
      geeksforgeeks
      forgeeksgeeks
      allergy
      allergic

      Output:
      YES
      NO
      **For More Examples Use Expected Output**

   http://www.practice.geeksforgeeks.org/problem-page.php?pid=88
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

static const int MinNrTest = 1;
static const int MaxNrTest = 30;

static const size_t MinStringLen = 1;
static const size_t MaxStringLen = 100;

/* speed = O(N * LogN)
   memory = O(1) (heapsort) */
bool is_anagram_v1(string &s1, string &s2)
{
	if (s1.length() != s2.length())
		return false;

	// speed O(N * LogN), memory O(1)
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());

	// speed = O(N), memory = O(1)
	for (size_t i = 0; i < s1.length(); ++i) {
		if (s1[i] != s2[i])
			return false;
	}

	return true;
}

/* speed avg = O(N)
   memory = O(N) */
bool is_anagram_v2(string &s1, string &s2)
{
	if (s1.length() != s2.length())
		return false;

	unordered_map<char, int> h_tbl;

	/* O(N) */
	for (size_t i = 0; i < s1.length(); ++i) {
		// speed avg O(1), memory O(N)
		++h_tbl[s1[i]];
		--h_tbl[s2[i]];
	}

	/* O(N) */
	for (auto& x: h_tbl) {
		if (x.second)
			return false;
	}

	return true;
}

int main()
{
	int nr_tests;

	cin >> nr_tests;
	if (nr_tests < MinNrTest || nr_tests > MaxNrTest) {
		cerr << "constraints error: 1 ≤ T ≤ 30\n";
		return 1;
	}

	string s1, s2;
	while (nr_tests--) {
		cin >> s1;
		if (s1.length() < MinStringLen || s1.length() > MaxStringLen) {
			cerr << "constraints error: 1 ≤ len(s) ≤ 100\n";
			return 1;
		}

		cin >> s2;
		if (s2.length() < MinStringLen || s2.length() > MaxStringLen) {
			cerr << "constraints error: 1 ≤ len(s) ≤ 100\n";
			return 1;
		}

		cout << ((is_anagram_v2(s1, s2)) ? "YES" : "NO") << endl;
	}

	return 0;
}

