/*
Given a string containing uppercase alphabets and integer digits (from 0 to 9), the task is to print the alphabets in the order followed by the sum of digits.

Input:
The first line of input contains an integer T denoting the number of test cases. Then T test cases follow. Each test case contains a string with uppercase alphabets and integer digits.

Output:
Print alphabets in the order followed by the sum of digits.

Constraints:
1<=T<=10^5
1<=length of string<=10^5

Example:
Input:
2
AC2BEW3
ACCBA10D2EW30

Output:
ABCEW5
AABCCDEW6
 */


#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void rearrange_a_string(string &s)
{
	int hash_tbl['Z' - 'A' + 1] = {0};
	bool with_digits = false;
	unsigned long sum = 0;
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			++hash_tbl[s[i] - 'A'];
		} else {
			with_digits = true;
			sum += s[i] - '0';
		}
	}

	size_t str_i = 0;
	for (size_t i = 0; i < sizeof(hash_tbl) / sizeof(int); ++i) {
		while (hash_tbl[i] > 0) {
			s[str_i++] = i + 'A';
			--hash_tbl[i];
		}
	}

	int digit_at = str_i;
	if (with_digits) {
		if (sum == 0) {
			s[str_i++] = '0';
		} else {
			int base = 1;
			while (sum) {
				s[str_i++] = sum % 10 + '0';
				base *= 10;
				sum /= base;
			}

			reverse(&s[digit_at], &s[str_i]);
		}
	}

	s.resize(str_i);
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;
		rearrange_a_string(s);
		cout << s << endl;
	}

	return 0;
}
