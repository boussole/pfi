/*
   Given an array of integers of size N. Assume ‘0’ as invalid number and all other as valid number.
   Write a program that modifies the array in such a way that
   if just next valid number is same as current number, double its value and replace the next number with 0.
   After the modification, rearrange the array such that all 0’s are shifted to the end and the sequence
   of the valid number or new doubled number is maintained as in the original array.

   Examples:
   Input : arr[] = {2, 2, 0, 4, 0, 8}
   Output : 4 4 8 0 0 0

   Input : arr[] = {0, 2, 2, 2, 0, 6, 6, 0, 0, 8}
   Output : 4 2 12 8 0 0 0 0 0 0

   Input:
   The first line of the input contains an integer T, denoting the number of test cases.
   Then T test case follows. First line of each test contains an integer N denoting the size of the array.
   Then next line contains N space separated integers denoting the elements of the array.

   Output:
   For each test case print space separated elements of the new modified array on a new line.

   Constraints:
   1<=T<=103
   1<=N<=105

   Example:
      Input:
      2
      5
      2 2 0 4 4
      5
      0 1 2 2 0
      Output:
      4 8 0 0 0
      1 4 0 0 0
 */

#include <iostream>
#include <vector>

using namespace std;

/*
 * speed  O(N)
 * memory O(1)
 */
void ease_the_array(vector<int> &arr)
{
	for (size_t i = 0; i < arr.size() - 1; ++i) {
		if (arr[i] != 0) {
			if (arr[i] == arr[i + 1]) {
				arr[i] *= 2;
				arr[i + 1] = 0;
			}
		}
	}

	size_t n_zero = 0;
	for (size_t i = 0; i < arr.size(); ++i) {
		if (arr[i] != 0)
			arr[n_zero++] = arr[i];
	}

	fill_n(&arr[n_zero], arr.size() - n_zero, 0);
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		vector<int> arr(arr_sz);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		ease_the_array(arr);

		for (int i = 0; i < arr_sz; ++i) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	return 0;
}

