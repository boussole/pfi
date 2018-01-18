/*
   Given two integers N and M. The task is to find the longest contiguous
   subset in binary representation of both the numbers and print its decimal value.

   Note: If there are two or more longest common substrings with the same length,
   the print the maximum value of all the common substrings.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Then T test cases follow. Each test case contains two integer N and M as input.

   Output:
   For each test case, print the decimal value of longest common substring In new line.

   Constraints:
   1<=T<=1000
   1<=N,M<=1018

   Example:
      Input:
      2
      10 11
      8 16

      Output:
      5
      8
 */

#include <iostream>
#include <memory>
#include <string>

using namespace std;

void int_to_bin_string(unsigned long val, string &s)
{
	char buf[64];
	int i = sizeof(buf);

	do {
		buf[--i] = (val & 1) ? '1' : '0';
		val >>= 1;
	} while (val != 0);

	s.assign(&buf[i], sizeof(buf) - i);
}

unsigned long bin_string_to_int(const string &s)
{
	unsigned long val = 0;
	for (size_t i = 0; i < s.length(); ++i) {
		val = (val << 1);
		if (s[i] == '1')
			val |= 1;
	}

	return val;
}

unsigned long longest_common_substring_value_of_two_numbers(unsigned long val_1, unsigned long val_2)
{
	string s1, s2;
	int_to_bin_string(val_1, s1);
	int_to_bin_string(val_2, s2);

	size_t lcs_len = 0;
	unsigned long val = 0;
	unique_ptr<unique_ptr<size_t[]>[]> lcs(new unique_ptr<size_t[]>[s1.length()]);

	// fill line 0
	lcs[0].reset(new size_t[s2.length()]());
	for (size_t i = 0; i < s2.length(); ++i) {
		if (s1[0] == s2[i]) {
			lcs[0][i] = 1;
			lcs_len = 1;
			val = 1;
		}
	}

	for (size_t i = 1; i < s1.length(); ++i) {
		lcs[i].reset(new size_t[s2.length()]());
		for (size_t j = 0; j < s2.length(); ++j) {
			if (s1[i] == s2[j]) {
				size_t new_len;

				if (j == 0) {
					new_len = 1;
					lcs[i][j] = new_len;
				} else {
					new_len = lcs[i - 1][j - 1] + 1;
					lcs[i][j] = new_len;
				}

				if (new_len >= lcs_len) {
					unsigned long candidate = bin_string_to_int(s1.substr(i + 1 - new_len, new_len));
					if (new_len > lcs_len || candidate > val) {
						val = candidate;
						lcs_len = new_len;
					}
				}
			}
		}
	}

	return val;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		unsigned long val_1, val_2;
		cin >> val_1 >> val_2;
		cout << longest_common_substring_value_of_two_numbers(val_1, val_2) << endl;
	}

	return 0;
}
