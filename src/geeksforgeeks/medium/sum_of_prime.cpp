/*
   Given a number ( greater than 2 ).
   Print two prime numbers whose sum will be equal to given number, else print -1 if no such number exists.

   NOTE: A solution will always exist if the number is even. Read Goldbach’s conjecture.

   If [a, b] is one solution with a <= b,
   and [c,d] is another solution with c <= d, and a < c then print [a, b] only and not all possible solutions.

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an integer N.

   Output:
   Print the two prime numbers in a single line with space in between.

   Constraints:
   1 ≤ T ≤ 50
   1 ≤ N ≤ 1000000

   Example:
      Input
      2
      8
      3

      Output
      3 5
      -1
 */

#include <iostream>
#include <vector>

using namespace std;

// speed O(N) => exp (input data logN)
// memory O(N)
bool sum_of_prime(int sum, int &comp1, int &comp2)
{
	vector<int> primes(sum + 1, 1);

	primes[0] = 0;
	primes[1] = 0;
	int it = 2;
	while (it < primes.size()) {
		if (!primes[it]) {
			++it;
			continue;
		}

		for (int i = 2; i * it <= sum; ++i)
			primes[it * i] = 0;

		++it;
	}

	if (primes[sum])
		return false;
	
	int c1, c2;
	for (c1 = 2; c1 < sum; ++c1) {
		if (primes[c1] && primes[sum - c1]) {
			comp1 = c1;
			comp2 = sum - c1;
			return true;
		}
	}

	return false;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int sum;
		cin >> sum;
		int comp1, comp2;
		if (sum_of_prime(sum, comp1, comp2))
			cout << comp1 << " " << comp2 << endl;
		else
			cout << -1 << endl;
	}

	return 0;
}
