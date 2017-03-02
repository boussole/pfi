/*
   Given a string you need to print the size of the longest possible substring that has exactly k unique characters.
   If there is no possible substring print -1.

   Example
   For the string aabacbebebe and k = 3 the substring will be cbebebe with length 7.

   Input:
   The first line of input contains an integer T denoting the no of test cases then T test cases follow.
   Each test case contains two lines.
   The first line of each test case contains a string s and the next line conatains an integer k.

   Output:
   For each test case in a new line print the required output.

   Constraints:
   1<=T<=100
   1<=k<=10

   Example:
      Input:
      2
      aabacbebebe
      3
      aaaa
      1
      Output:
      7
      4
*/

#include <iostream>
#include <string>

using namespace std;

// speed O(N)
// memory O(1)
int longest_k_unique_characters_substring(const string &s, int k)
{
	int len = 0, max_len = 0, start = 0;

	int map['z' - 'a' + 1] = {0};

	for (size_t i = 0; i < s.length(); ++i) {
		// already exists, no problem to add it to sequence
		if (map[s[i] - 'a']) {
			++map[s[i] - 'a'];
		} else {
			// it is a new element, so we can add it only if it's possible
			while (!k) {
				if (!--map[s[start++] - 'a'])
					++k;
			}

			--k;
			++map[s[i] - 'a'];
		}

		if (!k) {
			len = i - start + 1;
			max_len = max(len, max_len);
		}
	}

	return max_len ? max_len : -1;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;
		int k;
		cin >> k;

		cout << longest_k_unique_characters_substring(s, k) << endl;
	}

	return 0;
}


