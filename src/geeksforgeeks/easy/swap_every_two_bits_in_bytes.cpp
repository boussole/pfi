/*
Swap all the pair of bits in a byte.
Before swapping: 11-10-11-01
After swapping: 11-01-11-10
Input:
The first line of the input contains an integer T denoting the number of test cases. Each test case contains an unsigned integer x.

Output:
For each test case, the output is the integer after swapping the bits.

Constraints:
1<=T<=100
1<=x<=255

Example:
Input:
2
4
20
Output:
8
40
 */

#include <iostream>

using namespace std;

unsigned int swap_every_two_bits_in_bytes(uint8_t val)
{
	return ((val & 0b10101010) >> 1) | ((val & 0b01010101) << 1);
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		unsigned int value;
		cin >> value;
		cout << swap_every_two_bits_in_bytes(value) << endl;
	}

	return 0;
}

