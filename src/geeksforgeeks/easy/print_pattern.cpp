/*
   Print a sequence of numbers starting with N, !!!without using loop!!!, in which
   A[i+1] = A[i] - 5,  if  A[i]>0, else A[i+1]=A[i] + 5  repeat it until A[i]=N.

   Input:
   First line contains number of test cases T. Then following T lines contains an integer N.

   Output:
   Single line with pattern .

   Constraints:
   0 < N < 10000 (origin)
   -10000 < N < 10000 (my)

   Example:
      Input:
      2
      16
      10

      Output:
      16 11 6 1 -4 1 6 11 16
      10 5 0 5 10

   Explanation:
   We basically first reduce 5 one by one until we reach a negative or 0. After we reach 0 or negative, we one by one add 5 until we reach N.
   **For More Examples Use Expected Output**

   http://www.practice.geeksforgeeks.org/problem-page.php?pid=141
 */

#include <iostream>
#include <functional>

using namespace std;

static const int MinValidNumber = /* 0 */ -10000;
static const int MaxValidNumber = 10000;

void print_pattern(int number)
{
	function<void(int)> down = [&down](int n) {
		if (n > 0) {
			cout << n << " ";
			down(n - 5);
			cout << " ";
		}

		cout << n;
	};

	function<void(int)> up = [&up](int n) {
		if (n <= 0) {
			cout << n << " ";
			up(n + 5);
			cout << " ";
		}

		cout << n;
	};

	if (number > 0)
		down(number);
	else
		up(number);

	cout << endl;
}

int main()
{
	int nr_tests = 0;
	cin >> nr_tests;

	if (nr_tests <= 0) {
		cerr << "constraints error: T > 0\n";
		return 1;
	}

	while (nr_tests--) {
		int number;
		cin >> number;

		if (number <= MinValidNumber || number >= MaxValidNumber) {
			cerr << "constraints error: -10000 < N < 10000\n";
			return 1;
		}

		print_pattern(number);
	}
}

