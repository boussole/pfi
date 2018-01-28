/*
   Given a string, print all permutations of a given string.
   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Each test case contains a single string in capital letter.

   Output:
   Print all permutations of a given string with single space and
   all permutations should be in lexicographically increasing order.

   Constraints:
   1 ≤ T ≤ 10
   1 ≤ size of string ≤ 5

   Example:
   Input:
   2
   ABC
   ABSG

   Output:
   ABC ACB BAC BCA CAB CBA
   ABGS ABSG AGBS AGSB ASBG ASGB BAGS BASG BGAS BGSA BSAG BSGA GABS GASB GBAS GBSA GSAB GSBA SABG SAGB SBAG SBGA SGAB SGBA
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool make_next_permutation(string &s)
{
	if (s.empty())
		return false;

	for (size_t last = s.length() - 1; last > 0; --last) {
		size_t left_swap = last - 1;
		if (s[left_swap] < s[last]) {
			size_t right_swap = last++;
			/* NOTE: Use binary search here to find
			 * an element which is less than [left_swap - 1] but greater than [left_swap] */
			while (last < s.length()) {
				if (s[last] > s[left_swap] && s[right_swap] > s[left_swap]) {
					right_swap = last;
				}

				++last;
			}
			swap(s[left_swap], s[right_swap]);
			/* NOTE: don't sort here, it's sorted, just revert!!!! */
			sort(s.begin() + left_swap + 1, s.end());
			return true;
		}
	}

	return false;
}

/**
 * method 2: using recursion
 * https://www.geeksforgeeks.org/permutations-of-a-given-string-using-stl/
 */

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;

		sort(s.begin(), s.end());
		cout << s << " ";
		while (make_next_permutation(s)) {
			cout << s << " ";
		}
		cout << endl;
	}

	return 0;
}

