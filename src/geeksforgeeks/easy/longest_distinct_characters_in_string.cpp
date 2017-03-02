/*
   Given a string, find length of the longest substring with all distinct characters.
   For example, for input "abca", the output is 3 as "abc" is the longest substring with all distinct characters.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   The first line of each test case is String str.

   Output:
   Print length of smallest substring with maximum number of distinct characters.
   Note: The output substring should have all distinct characters.

   Constraints:
   1 ≤ T ≤ 100
   1 ≤ size of str ≤ 10000

   Example:
      Input
      2
      abababcdefababcdab
      geeksforgeeks
      Output:
      6
      7
 */

#include <iostream>
#include <string>

using namespace std;

// speed O(N)
// memory O(1)
size_t longest_distinct_characters_in_string(const string &s)
{
	int symbol_map['z' - 'a' + 1] = {0};

	size_t current_len = 0, longest_len = 0, sequence_start = 0;
	for (size_t i = 0; i < s.length(); ++i) {
		if (!symbol_map[s[i] - 'a']) {
			symbol_map[s[i] - 'a'] = 1;
			++current_len;
		} else {
			longest_len = max(current_len, longest_len);
			while (sequence_start < i) {
				if (s[sequence_start] == s[i]) {
					++sequence_start;
					break;
				} else {
					symbol_map[s[sequence_start++] - 'a'] = 0;
					--current_len;
				}
			}
		}
	}

	return max(current_len, longest_len);
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;
		cout << longest_distinct_characters_in_string(s) << endl;
	}

	return 0;
}

