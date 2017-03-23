/*
   You are given a binary string S.
   In a single operation, you can choose two indices L and R such that
   1 ≤ L ≤ R ≤ N and complement the characters between L and R i.e SL, SL+1, …, SR.
   By complement, we mean change character 0 to 1 and vice-versa.
   You task is to perform ATMOST one operation such that in final string number of 1s is maximised.
   If there is no need to completement, i.e., string contains all 1s, return -1.
   Else, return the two values denoting L and R.
   If there are multiple solutions, return the lexicographically smallest pair of L and R.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Each test case consist of a length of string N and the next line contains the string S in 'lowercase' only.

   Output:
   Print the value L and R with space between then in a seprate line if it exists else print -1.

   Constraints:
   1 ≤ T ≤ 40
   1 ≤ N ≤ 100
   1 ≤ |s| ≤ 100

   Example:
   Input:
   2
   3
   111
   2
   01
   Output:
   -1
   1 1
 */

#include <iostream>
#include <string>

using namespace std;

// speed O(N)
// memory O(1)
void complement(const string &s, int &l, int &r)
{
	l = r = -1;

	int balance = 0, cand_balance = 0, cand_l = -1;
	for (size_t i = 0; i < s.length(); ++i) {
		if (s[i] == '0') {
			if (!cand_balance++ && cand_l == -1)
				cand_l = i;

			if (cand_balance > balance) {
				balance = cand_balance;
				l = cand_l;
				r = i;
			}
		} else {
			if (cand_balance)
				--cand_balance;
			else
				cand_l = -1;
		}
	}

	// adjustment for task, indexes start from `1`
	if (l != -1) {
		++l;
		++r;
	}
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int len;
		cin >> len;
		string s;
		cin >> s;
		int l, r;
		complement(s, l, r);
		if (l > 0)
			cout << l << " " << r << endl;
		else
			cout << -1 << endl;
	}

	return 0;
}
