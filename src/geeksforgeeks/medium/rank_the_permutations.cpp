/*
   Given a string, find the rank of the string amongst its permutations sorted lexicographically.
   Return 0 if the characters are repeated in the string.

   For example:
   Input : 'acb'
   Output : 2

   The order permutations with letters 'a', 'c', and 'b' :
   abc
   acb
   bac
   bca
   cab
   cba

   The answer might not fit in an integer, so return your answer % 1000003

   Input:
   The first line of input contains an integer T denoting the number of test cases. Each test case consist of a string in 'lowercase' only in a separate line.

   Output:
   Print the rank of the string amongst its permutations.

   Constraints:
   1 ≤ T ≤ 50
   1 ≤ |s| ≤ 15

   Example:
   Input:
   2
   abc
   acb
   Output:
   1
   2
 */

#include <iostream>
#include <string>

using namespace std;

uint64_t factorial(uint64_t n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

// speed O(N^2)
// memory O(1)
uint64_t rank_the_permutation(const string &s)
{
	uint64_t rank = 1;
	uint64_t mul = s.length() - 1;
	uint64_t fact = factorial(mul);

	for (size_t i = 0; i < s.length() - 1; ++i) {
		for (size_t j = i + 1; j < s.length(); ++j) {
			if (s[i] == s[j])
				return 0;	// task 

			if (s[j] < s[i])
				rank += fact;

			while (rank > 1000003)
				rank %= 1000003;
		}

		fact /= mul--;
	}

	return rank;
}


/*
   there is another solution here http://www.geeksforgeeks.org/lexicographic-rank-of-a-string/
   but I'm not sure that it works in O(N)
 */

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;
		cout << rank_the_permutation(s) << endl;
	}

	return 0;
}
