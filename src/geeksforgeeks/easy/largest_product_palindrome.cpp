/*
   Given a value n, find out the largest palindrome number which is product of two n digit numbers.

   Examples:
   Input  : n = 2
   Output : 9009
   9009 is the largest number which is product of two 2-digit numbers. 9009 = 91*99.

   Input : n = 1
   Output : 9

   Input:
   The first line of input contains an integer T denoting the no of test cases.
   Then T test cases follow. Each test case contains an integer n.

   Output:
   For each test case in a new line print the required output.

   Constraints:
   1<=T<=6
   1<=n<=6

   Example:
      Input:
      2
      2
      1
      Output:
      9009
      9
 */

#include <iostream>

using namespace std;

bool is_palindrome(uint64_t value)
{
	uint64_t revert_value = 0, mutable_value = value;

	while (mutable_value > 0) {
		uint8_t residue_10 = mutable_value % 10;
		revert_value = revert_value * 10 + residue_10;
		mutable_value /= 10;
	}

	return value == revert_value;
}

// speed O(exp*exp)
// memory O(N) - linear
uint64_t largest_product_palindrome(uint32_t nr_digits)
{
	uint64_t largest_palindrome = 0;

	int lower = 0, upper = 0;
	for (int i = 0; i < nr_digits; ++i) {
		lower = lower * 10 + 1;
		upper = upper * 10 + 9;
	}

	for (int i = upper; i >= lower; --i) {
		for (int j = i; j >= lower; --j) {
			uint64_t product = (uint64_t)i * j;

			// no need to check whether it palindrome or not, no need to continue, stop sub loop here
			if (product < largest_palindrome)
				break;

			if (is_palindrome(product))
				largest_palindrome = product;
		}
	}

	return largest_palindrome;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int nr_digits;
		cin >> nr_digits;

		cout << largest_product_palindrome(nr_digits) << endl;
	}

	return 0;
}



