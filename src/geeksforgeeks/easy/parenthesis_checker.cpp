/*
   Given an expression string exp, examine whether the pairs and the orders of “{“,”}”,”(“,”)”,”[“,”]” are correct in exp.
   For example, the program should print 'balanced' for exp = “[()]{}{[()()]()}” and 'not balanced' for exp = “[(])”

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Each test case consist of a string of expression, in a separate line.

   Output:
   Print 'balanced' without quotes if pair of parenthesis are balanced else print 'not balanced' in a separate line.

   Constraints:
   1 ≤ T ≤ 30
   1 ≤ |s| ≤ 100

   Example:
      Input:
      3
      {([])}
      ()
      ()[]

      Output:
      balanced
      balanced
      balanced
      **For More Examples Use Expected Output**

      http://www.practice.geeksforgeeks.org/problem-page.php?pid=147
 */

#include <iostream>
#include <stack>

using namespace std;

#ifndef ARRAY_SIZE
#	define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

static const int MinNrTests = 1;
static const int MaxNrTests = 30;

static const size_t MinStringLen = 1;
static const size_t MaxStringLen = 100;

// unfortunately an ascii gap between pair of parethessis is not identical for all pairs :(
// '(' - 40, ')' - 41 => (gap = 1)
// '[' - 91, ']' - 93 => (gap = 2)
// '{' - 123, '}' - 125 => (gap = 2)
// so save index of array
static char open[] =  { '(', '{', '[' };
static char close[] = { ')', '}', ']' };

// O(1)
bool is_open_parethessis(char sym, int &id)
{
	for (id = 0; id < ARRAY_SIZE(open); ++id) {
		if (open[id] == sym)
			return true;
	}

	return false;
}

// O(1)
bool is_close_parethessis(char sym, int &id)
{
	for (id = 0; id < ARRAY_SIZE(close); ++id) {
		if (close[id] == sym)
			return true;
	}

	return false;
}

// speed O(N)
// memory O(N)
bool parenthesis_checker(string &s)
{
	stack<int> open_parenthesis; // stack of parenthesis `id`

	for (size_t i = 0; i < s.length(); ++i) {
		int id = 0;

		if (is_open_parethessis(s[i], id)) {
			open_parenthesis.push(id);
		} else if (is_close_parethessis(s[i], id)) {
			if (open_parenthesis.empty())
				return false;

			if (open_parenthesis.top() != id)
				return false;

			open_parenthesis.pop();
		}
	}

	return open_parenthesis.empty();
}

int main()
{
	int nr_tests = 0;
	cin >> nr_tests;

	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints error: 1 <= T <= 30\n";
		return 1;
	}

	while (nr_tests--) {
		string s;
		cin >> s;
		if (s.length() < MinStringLen || s.length() > MaxStringLen) {
			cerr << "constraints error: 1 <= T <= 30\n";
			return 1;
		}

		cout << (parenthesis_checker(s) ? "balanced" : "not balanced") << endl;
	}

	return 0;
}
