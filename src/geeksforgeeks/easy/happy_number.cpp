/*
   Given a no N your task is to find whether its a happy no or not.
   A number is called happy if it leads to 1 after a sequence of steps where in each step number is replaced
   by sum of squares of its digit that is if we start with Happy Number and keep replacing it with digits square sum,
   we reach 1.

   For eg:
   Input: n = 19
   Output: 1
   19 is Happy Number,
   1^2 + 9^2 = 82
   8^2 + 2^2 = 68
   6^2 + 8^2 = 100
   1^2 + 0^2 + 0^2 = 1
   As we reached to 1, 19 is a Happy Number.

   Input: n = 20
   Output: 0

   Input:
   The first line of input contains an integer T denoting the no of test cases.
   Then T test cases follow . The first line of each test case contains an integer N.

   Output:
   For each test case in a new line print 1 if the no is a happy else print 0.

   Constraints:
   1<=T<=100
   1<=N<=1000

   Example:
   Input
   2
   19
   20
   Output
   1
   0
 */

#include <iostream>

using namespace std;

uint64_t sum_of_squares_of_digits(uint64_t value)
{
	uint64_t sum = 0;

	while (value) {
		uint8_t digit = value % 10;
		sum += digit * digit;
		value /= 10;
	}

	return sum;
}

// memory O(1) - linear
bool is_happy_number(uint64_t value)
{
	uint64_t slow = value, fast = value;
	do {
		slow = sum_of_squares_of_digits(slow);
		if (slow == 1)
			return true;

		fast = sum_of_squares_of_digits(sum_of_squares_of_digits(fast));
		if (fast == 1)
			return true;

	} while (slow != fast);

	return false;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		uint64_t value;
		cin >> value;
		cout << (is_happy_number(value) ? "1" : "0") << endl;
	}

	return 0;
}
