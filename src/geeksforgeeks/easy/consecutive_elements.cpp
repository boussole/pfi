/*

   For a given string delete the elements which are appearing more than once consecutively. All letters are of lowercase.

   Input:
   The first line contains an integer 'T' denoting the total number of test cases. In each test cases,  a string will be inserted.

   Output:
   In each seperate line the modified string should be output.


   Constraints:
   1<=T<=31
   1<=length(string)<=100

   Example:
   Input:
   1
   aababbccd

   Output:
   ababcd

   **For More Examples Use Expected Output**
 */

#include <iostream>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 31;

static const size_t MinStringLen = 1;
static const size_t MaxStringLen = 100;

// speed O(N)
// memory O(1)
void delete_consecutive_elements(string &s)
{
	size_t src = 0, dst = 0;

	while (src < s.length()) {
		if (s[dst] != s[src])
			s[++dst] = s[src++];
		else
			++src;
	}

	s.resize(dst + 1);
}

int main()
{
	int nr_tests = 0;
	cin >> nr_tests;

	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints error: 1 <= T <= 31\n";
		return 1;
	}

	while (nr_tests--) {
		string s;
		cin >> s;
		if (s.length() < MinStringLen || s.length() > MaxStringLen) {
			cerr << "constraints error: 1<=len<=100\n";
	                return 1;
		}

		delete_consecutive_elements(s);

		cout << s << endl;
	}

	return 0;
}
