/*
   Given 2 sorted arrays A and B of size N each. Print sum of middle elements of the array obtained after merging the given arrays.

   Input:
   The first line contains 'T' denoting the number of testcases. Then follows description of testcases.
   Each case begins with a single positive integer N denoting the size of array.
   The second line contains the N space separated positive integers denoting the elements of array A.
   The third line contains N space separated positive integers denoting the elements of array B.

   Output:
   For each testcase, print the sum of middle elements of two sorted arrays.
   The number of the elements in the merged array are even so there will be 2 numbers in the center n/2 and n/2 +1.
   You have to print their sum.


   Constraints:
   1<=T<=50
   1<=N<=1000
   1<=A[i]<=100000
   1<=B[i]<=100000

   Example:
      Input :
      1
      5
      1 2 4 6 10
      4 5 6 9 12

      Output :
      11
 */

#include <iostream>
#include <memory>

using namespace std;

// speed O(N)
// memory O(1)
int sum_of_middle_elements_of_two_sorted_arrays(const unique_ptr<int[]> &arr_1, const unique_ptr<int[]> &arr_2, int arr_sz)
{
	if (arr_sz == 1)
		return arr_1[0] + arr_2[0];

	int low = arr_sz - 1, high = arr_sz;
	int result[2];
	int result_pos = 0, i = 0, i_1 = 0, i_2 = 0;

	while (i <= high) {
		if (i_1 < arr_sz && i_2 < arr_sz)
			result[result_pos] = (arr_1[i_1] < arr_2[i_2]) ? arr_1[i_1++] : arr_2[i_2++];
		else
			result[result_pos] = (i_1 < arr_sz) ? arr_1[i_1++] : arr_2[i_2++];

		if (i++ == low)
			++result_pos;
	}

	return result[0] + result[1];
}


int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		unique_ptr<int[]> arr_1(new int[arr_sz]), arr_2(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i)
			cin >> arr_1[i];
		for (int i = 0; i < arr_sz; ++i)
			cin >> arr_2[i];

		cout << sum_of_middle_elements_of_two_sorted_arrays(arr_1, arr_2, arr_sz) << endl;
	}

	return 0;
}
