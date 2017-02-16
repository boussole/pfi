/*
   Given a string S consisting of uppercase alphabatic characters.
   Return the  number of different substrings of size 2 that appear in S as contiguous substrings.

   NOTES: strange task definition about "as contiguous substrings", really needs only unique string of len == 2

   Input:
   The first line contains 'T' denoting the number of testcases.
   Then follows description of testcases. The next T lines contains the string S.

   Output:
   Output the number of different substrings of size 2 in S.

   Constraints:
   1<=T<=50
   1<=|S|<=100

   Example:
   Input:
      2
      ABCAB
      XYZ

   Output :
      3
      2

   Explanation:
   For "ABCAB", the three distinct substrings of size 2 are "AB", "BC" and "CA".
   For "XYZ", the two distinct substrings of size 2 are "XY" and "YZ".
 */

#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

// hash { "substring" }
using hash_tbl = unordered_set<string>;

// speed O(N)
// memory O(N)
long distinct_substrings_of_len_2(string &s)
{
	if (s.length() < 2)
		return 0;

	long len = 0;
	hash_tbl tbl;

	for (size_t i = 0; i < s.length() - 1; ++i) {
		// save substring
		string sub(s.substr(i, 2));

		// find it in the hash O(1) (avg)
		hash_tbl :: iterator got = tbl.find(sub);

		// not found, insert it O(1) (avg)
		if (got == tbl.end()) {
			tbl.insert(sub);
			++len;
		}
	}

	return len;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;

		cout << distinct_substrings_of_len_2(s) << endl;
	}

	return 0;
}


