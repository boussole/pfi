/*
   Given a non-negative number represented as an array of digits, add 1 to the number
   ( increment the number represented by the digits ).
   The digits are stored such that the most significant digit is at the head of the list.

   Example:
      If the array has [4, 5, 6] the resultant array should be [4, 5, 7] as 456 + 1 = 457.

   Input:
      The first line of input contains an integer T denoting the number of test cases. The description of T test cases follows.
      The first line of each test case contains a single integer N denoting the size of array.
      The second line contains N space-separated integers A1, A2, ..., AN denoting the elements of the array.

   Output: Print the space separated resultant array in a separate line for each case.

   Constraints:
   1 ≤ T ≤ 30
   1 ≤ N ≤ 1000
   0 ≤ A[i] ≤ 9

   Example:
      Input:
      2
      4
      5 6 7 8
      3
      9 9 9
      Output:
      5 6 7 9
      1 0 0 0
      **For More Examples Use Expected Output**

   http://www.practice.geeksforgeeks.org/problem-page.php?pid=107
 */

#include <iostream>
#include <memory>

static const size_t MinNrTest = 1;
static const size_t MaxNrTest = 30;

static const size_t MinNrDigit = 1;
static const size_t MaxNrDigit = 1000;

static const size_t MinValidDigit = 0;
static const size_t MaxValidDigit = 9;

using namespace std;

/* insert digits in a back order */
bool read_digits(unique_ptr<int[]> &arr, size_t nr_digit)
{
	int pos = static_cast<int>(nr_digit);

	while (--pos >= 0) {
		cin >> arr[pos];
		if (arr[pos] < MinValidDigit || arr[pos] > MaxValidDigit)
			return false;
	}

	return true;
}

/* extract digits in a back order */
void write_digits(unique_ptr<int[]> &arr, size_t nr_digit)
{
	int pos = static_cast<int>(nr_digit);

	while (--pos > 0)
		cout << arr[pos] << " ";

	cout << arr[pos] << endl;
}

void adding_one(unique_ptr<int[]> &arr, size_t &nr_digit)
{
	size_t pos = 0;
	int digit = 1;

	while (digit > 0) {
		uint8_t val = arr[pos] + digit;
		arr[pos++] = val % 10;
		digit = val / 10;
	}

	nr_digit = max(pos, nr_digit);
}

int main()
{
	int nr_tests;

	cin >> nr_tests;
	if (nr_tests < MinNrTest || nr_tests > MaxNrTest) {
		cerr << "constraints error: 1 ≤ T ≤ 30\n";
		return 1;
	}

	while (nr_tests--) {
		size_t nr_digit = 0;
		cin >> nr_digit;

		if (nr_digit < MinNrDigit || nr_digit > MaxNrDigit) {
			cerr << "constraints error: 1 ≤ N ≤ 1000\n";
			return 1;
		}

		// yes, there is a `make_unique`, but geeksforgeeks compiler doesn't support c++14
		unique_ptr<int[]> arr(new int[nr_digit + 1]()); // `+1` for overflow position

		if (!read_digits(arr, nr_digit)) {
			cerr << "constraints error: 0 ≤ A[i] ≤ 9\n";
			return 1;
		}

		adding_one(arr, nr_digit);

		write_digits(arr, nr_digit);
	}

	return 0;
}

