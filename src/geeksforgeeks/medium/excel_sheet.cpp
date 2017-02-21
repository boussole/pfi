/*
   Given a positive integer, return its corresponding column title as appear in an Excel sheet.
   For example:
      1 -> A
      2 -> B
      3 -> C
      ...
      26 -> Z
      27 -> AA
      28 -> AB

   NOTE: The alphabets are all in uppercase.

   Input:
   The first line contains an integer T, depicting total number of test cases. Then following T lines contains an integer N.

   Output:
   Print the string corrosponding to the column number.

   Constraints:
   1 ≤ T ≤ 40
   1 ≤ N ≤ 10000000

   Example:
      Input
      1
      51
      Output
      AY
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// speed O(exp)
// speed O(exp)
void excel_sheet(int n, string &s)
{
	static char alphabet_before_A = 'A' - 1;

	while (n > 26) {
		s += alphabet_before_A + n % 26;
		n /= 26;
	}

	s += alphabet_before_A + n;

	reverse(s.begin(), s.end());
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	string s;
	while (nr_tests--) {
		int n;
		cin >> n;

		excel_sheet(n, s);
		cout << s << endl;
		s.clear();
	}

	return 0;
}
