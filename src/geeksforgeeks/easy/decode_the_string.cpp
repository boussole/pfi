/*
   An encoded string (s) is given, the task is to decode it.
   The pattern in which the strings were encoded were as follows
   original string: abbbababbbababbbab
   encoded string : "3[a3[b]1[ab]]".

   Input:
   The first line of input contains an integer T denoting the no of test cases. Then T test cases follow. Each test case contains a string s.

   Output:
   For each test case in a new line print the required decoded string.

   Constraints:
   1<=T<=10
   1<=length of the string <=30

   Example:
   Input:
   2
   1[b]
   3[b2[ca]]

   Output:
   b
   bcacabcacabcaca
 */

#include <assert.h>

#include <iostream>
#include <string>
#include <stack>

using namespace std;

// speed O(N)
// memory O(N)
string &decode_the_string(const string &enc, string &dec)
{
	stack<pair<int, string> > stack;
	string digit;

	for (size_t i = 0; i < enc.length(); ++i) {
		string :: size_type sz = 0;

		if (enc[i] == '[') {
			stack.push(make_pair(digit.empty() ? 1 : stoll(digit, &sz, 0), ""));
			digit.clear();
		} else if (isdigit(enc[i])) {
			digit += enc[i];
		} else if (enc[i] == ']') {
			assert(!stack.empty());
			string mid;
			while (stack.top().first--)
				mid += stack.top().second;
			stack.pop();

			if (stack.empty())
				dec += mid;
			else
				stack.top().second += mid;
		} else /* it a string */ {
			assert(!stack.empty());
			stack.top().second += enc[i];
		}
	}

	return dec;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string encoded, decoded;
		cin >> encoded;

		cout << decode_the_string(encoded, decoded) << endl;
	}

	return 0;
}

