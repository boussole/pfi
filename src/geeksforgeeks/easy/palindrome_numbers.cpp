/*
   Check if binary representation of a number is palindrome

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an integer N.

   Output:
   Each seperate line showing output 0(False) or 1 (True).

   Constraints:
   1 ≤ T ≤ 30 (orig)
   1 ≤ N ≤ 10 ^ 18

   Example:
      Input:
      2
      999
      17

      Output:
      0
      1

      **For More Examples Use Expected Output**
 */

#include <iostream>

using namespace std;

template <int base, int power>
struct Power {
	enum : uint64_t { value = base * Power<base, power - 1> :: value };
};

template <int base>
struct Power<base, 0> {
	enum : uint64_t { value = 1 };
};

static const int MinNrTests = 1;
static const int MaxNrTests = 50;

static const uint64_t MinValue = 1;
static const uint64_t MaxValue = Power<10, 18> :: value;

// speed O(N)
// memory O(N)
bool is_palindrome_number(uint64_t value)
{
	uint64_t v = value, invert = 0;

	while (v) {
		invert = (invert << 1) | (v & 1);
		v >>= 1;
	}

	return value == invert;
}

int main()
{
	int nr_tests;

	cin >> nr_tests;
	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints: 1 ≤ T ≤ 30\n";
		return 1;
	}

	while (nr_tests--) {
		uint64_t value;
		cin >> value;
		if (value < MinValue || value > MaxValue) {
			cerr << "constraints: 1 ≤ N ≤ 10 ^ 18\n";
			return 1;
		}

		cerr << value << endl;
		cout << (is_palindrome_number(value) ? "1" : "0") << endl;
	}

	return 0;
}

