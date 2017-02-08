/*
   For an integer n find number of trailing zeroes in n! .

   Input:
   The first line contains an integer 'T' denoting the total number of test cases. In each test cases, it contains an integer 'N'.

   Output:
   In each seperate line output the answer to the problem.

   Constraints:
   1<=T<=100
   1<=N<=1000


   Example:
   Input:
   1
   9
   Output:
   1

   **For More Examples Use Expected Output**
 */

#include <iostream>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 100;

static const int MinValue = 1;
static const int MaxValue = 1000;

/*
	0  =                         1 = 0
	1  =                         1 = 0
	2  =                         2 = 0
	3  =                         6 = 0
	4  =                        24 = 0
	5  =                       120 = 1
	6  =                       720 = 1
	7  =                      5040 = 1
	8  =                    40 320 = 1
	9  =                   362 880 = 1
	10 =                 3 628 800 = 2
	11 =                39 916 800 = 2
	12 =               479 001 600 = 2
	13 =             6 227 020 800 = 2
	14 =            87 178 291 200 = 2
	15 =         1 307 674 368 000 = 3
	16 =        20 922 789 888 000 = 3
	17 =       355 687 428 096 000 = 3
	18 =     6 402 373 705 728 000 = 3
	19 =   121 645 100 408 832 000 = 3
	20 = 2 432 902 008 176 640 000 = 4
	//--------------------------------
	speed O(poli)
	memory O(N)
 */
int trailing_zeroes_in_factorial(int value)
{
	int zeroes = 0;
	int div_result = value;

	while ((div_result /= 5))
		zeroes += div_result;

	return zeroes;
}

int main()
{
	int nr_tests = 0;
	cin >> nr_tests;

	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints: 1 ≤ T ≤ 100\n";
		return 1;
	}

	while (nr_tests--) {
		int value;
		cin >> value;
		if (value < MinValue || value > MaxValue) {
			cerr << "constraints: 1<=N<=1000\n";
			return 1;
		}

		cout << trailing_zeroes_in_factorial(value) << endl;
	}

	return 0;
}
