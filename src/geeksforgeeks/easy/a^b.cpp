/*
   For two given positive numbers a and b. Find a^b.
   Output your number modulus 10^9+7.

   Input:
   The first line contains an integer 'T' denoting the total number of test cases.
   In each test cases, there are two numbers a and b.

   Output:
   Find a^b.

   Constraints:
   1 <= T <= 31
   1 <= a <= 100
   1 <= b <= 1000000

   Example:
   Input:
      2
      1 1
      2 5

   Output:
   1
   32

   **For More Examples Use Expected Output**
 */

#include <iostream>

using namespace std;

template <int base, int p>
struct power {
	enum : uint64_t { value = base * power<base, p - 1> :: value };
};

template <int base>
struct power <base, 0> {
	enum : uint64_t { value = 1 };
};

static const uint64_t modul = power<10, 9> :: value + 7;

// speed O(exp^exp)
// memory O(N)
uint64_t a_in_b(uint64_t a, uint64_t b)
{
	uint64_t result = 1, product = 1;

	for (int i = 0; i < b; ++i) {
		product *= a;

		if (product >= modul) {
			result *= (product % modul);
			product = 1;
		}

		while (result > modul)
			result %= modul;
	}

	// residue
	if (product > 1)
		result *= product % modul;
	while (result > modul)
        	result %= modul;

	return result;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int a, b;
		cin >> a >> b;

		cout << a_in_b(a, b) << endl;
	}
	
	return 0;
}



