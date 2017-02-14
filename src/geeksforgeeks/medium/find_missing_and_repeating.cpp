/*

   Given an unsorted array of size n. Array elements are in range from 1 to n.
   One number 'A' from set {1, 2, …n} is missing and one number 'B' occurs twice in array.
   Find these two numbers.

   Input:
   The first line of input contains an integer T denoting the number of test cases. The description of T test cases follows.
   The first line of each test case contains a single integer N denoting the size of array.
   The second line contains N space-separated integers A1, A2, ..., AN denoting the elements of the array.

   Output:

   Print B, the repeating number followed by A which is missing in a single line.

   Constraints:
   1 ≤ T ≤ 40
   1 ≤ N ≤ 100
   1 ≤ A[i] ≤ N

   Example:
      Input
      2
      2
      2 2
      3
      1 3 3

      Output
      2 1
      3 2

      **For More Examples Use Expected Output**
 */

#include <assert.h>
#include <math.h>

#include <iostream>
#include <memory>

using namespace std;

// speed O(N)
// memory O(N)
void find_missing_and_repeating_v1(const unique_ptr<int[]> &arr, int arr_sz, int &repeating, int &missing)
{
	unique_ptr<int[]> counting_arr(new int[arr_sz]());
	for (int i = 0; i < arr_sz; ++i)
		++counting_arr[arr[i] - 1];

	for (int i = 0; i < arr_sz; ++i) {
		if (!counting_arr[i])
			missing = i + 1;
		else if (counting_arr[i] == 2)
			repeating = i + 1;
	}
}

// speed O(N)
// memory O(1)
//
// equations:
// sum(1..n) = ((1 + n) * n) / 2;
// sum(1..n) = sum(arr) - repeating + missing = sum(arr) - (repeating - missing) (1)
//
// product(1..n) = product(arr) * missing / repeating (overflow to fast)
//
// sum(1^2..n^2) = n(n + 1)(2*n + 1)/6
// sum(1^2..n^2) = sum(arr[0]^2..arr[n - 1]^2) - repeating^2 + missing^2 = sum(arr[0]^2..arr[n - 1]^2) - (repeating^2 - missing^2) (2)
//
// use (1) and (2)
// (1): (repeating - missing) = sum(arr) - sum(1..n)
// (2): (repeating^2 - missing^2) = sum(arr[0]^2..arr[n - 1]^2) - sum(1^2..n^2)
// (2): (repeating - missing) * (repeating + missing) = sum(arr[0]^2..arr[n - 1]^2) - sum(1^2..n^2)
// (2): (repeating + missing) = (sum(arr[0]^2..arr[n - 1]^2) - sum(1^2..n^2)) / (repeating - missing)
// (2): (repeating + missing) = (sum(arr[0]^2..arr[n - 1]^2) - sum(1^2..n^2)) / (expanding...)
// (2): (repeating + missing) = (sum(arr[0]^2..arr[n - 1]^2) - sum(1^2..n^2)) / (sum(arr) - sum(1..n))
//
// so we have
// (repeating + missing) = const1
// (repeating - missing) = const2
// ...
// repeating = const1 - missing
// const1 - missing - missing = const2 => const1 - const2 = 2 * missing => (const1 - const2) / 2 = missing
void find_missing_and_repeating_v2(const unique_ptr<int[]> &arr, int arr_sz, int &repeating, int &missing)
{
	int normal_sum = ((1 + arr_sz) * arr_sz) / 2;
	int normal_sum_squares = arr_sz*(arr_sz + 1)*(2*arr_sz + 1)/6;
	int input_sum = 0;
	int input_sum_squares = 0;

	for (int i = 0; i < arr_sz; ++i) {
		input_sum += arr[i];
		input_sum_squares += arr[i] * arr[i];
	}

	int x_minus_y = (input_sum - normal_sum);
	int x_plus_y = (input_sum_squares - normal_sum_squares) / x_minus_y;

	missing = (x_plus_y - x_minus_y) / 2;
	repeating = x_plus_y - missing;
}

// speed O(N)
// memory O(1)
void find_missing_and_repeating_v3(const unique_ptr<int[]> &arr, int arr_sz, int &repeating, int &missing)
{
	int orig_xor = 0, input_xor = 0;
	// O(N)
	for (int i = 0; i < arr_sz; ++i) {
		orig_xor ^= (i + 1);
		input_xor ^= arr[i];
	}


	int common_bits = orig_xor ^ input_xor;
	int right_most_bit = common_bits & ~(common_bits - 1);

	int first_xor = 0, second_xor = 0;
	// O(N)
	for (int i = 0; i < arr_sz; ++i) {
		int orig_value = i + 1;
		if (orig_value & right_most_bit)
			first_xor ^= orig_value;
		else
			second_xor ^= orig_value;

		if (arr[i] & right_most_bit)
			first_xor ^= arr[i];
		else
			second_xor ^= arr[i];
	}

	// O(N)
	for (int i = 0; i < arr_sz; ++i) {
		if (arr[i] == first_xor) {
			repeating = first_xor;
			missing = second_xor;
			break;
		} else if (arr[i] == second_xor) {
			repeating = second_xor;
			missing = first_xor;
			break;
		}
	}
}

// Method 3 (Use elements as Index and mark the visited places)
// Traverse the array. While traversing, use absolute value of every element as index and make the value at this index as negative to mark it visited.
// If something is already marked negative then this is the repeating element. To find missing, traverse the array again and look for a positive value.

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;
		assert(arr_sz > 0);

		unique_ptr<int[]> arr(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
			assert(arr[i] > 0 && arr[i] <= 100);
		}

		int repeating_1, missing_1;
		int repeating_2, missing_2;
		int repeating_3, missing_3;
		find_missing_and_repeating_v1(arr, arr_sz, repeating_1, missing_1);
		find_missing_and_repeating_v2(arr, arr_sz, repeating_2, missing_2);
		find_missing_and_repeating_v3(arr, arr_sz, repeating_3, missing_3);

		assert(missing_1 == missing_2 && missing_2 == missing_3);
		assert(repeating_1 == repeating_2 && repeating_2 == repeating_3);

		cout << repeating_1 << " " << missing_1 << endl;
	}

	return 0;
}
