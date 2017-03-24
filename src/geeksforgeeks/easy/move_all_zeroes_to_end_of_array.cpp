/*
   Given an array of random numbers, Push all the zero’s of a given array to the end of the array.
   For example, if the given arrays is {1, 9, 8, 4, 0, 0, 2, 7, 0, 6, 0},
   it should be changed to {1, 9, 8, 4, 2, 7, 6, 0, 0, 0, 0}.

   Input:
   The first line contains an integer 'T' denoting the total number of test cases.
   In each test cases, First line is number of elements in array 'N' and second its values.

   Output:
   Print the array after shifting all 0's at the end.​

   Note: An extra space is expected at the end after output of every test case

   Constraints:
   1 <= T <=100
   1 <= N <=1000
   0 <= a[i] <=100

   Example:
   Input:
   1
   5
   3 5 0 0 4

   Output:
   3 5 4 0 0
 */

#include <iostream>
#include <memory>

using namespace std;

// speed O(N)
// memory O(1)
void move_all_zeroes_to_end_of_array(unique_ptr<int[]> &arr, int arr_sz)
{
	int left, right;

	// little preprocessing
	// 1. save first zero to left
	for (left = 0; left < arr_sz && arr[left]; ++left);
	if (left == arr_sz)
		return;

	// 2. save first non zero after first zero
	for (right = left + 1; left < arr_sz && !arr[right]; ++right);
	if (right == arr_sz)
		return;

	for (; left < arr_sz; ++left) {
		if (arr[left] == 0) {
			swap(arr[left], arr[right++]);
			// look for the next not zero
			for (; right < arr_sz && !arr[right]; ++right);
			if (right == arr_sz)
				return;
		}
	}
}

// there is a more elegant decision with the same complexity http://www.geeksforgeeks.org/move-zeroes-end-array/
/*
void pushZerosToEnd(int arr[], int n)
{
    int count = 0;  // Count of non-zero elements

    // Traverse the array. If element encountered is non-
    // zero, then replace the element at index 'count'
    // with this element
    for (int i = 0; i < n; i++)
        if (arr[i] != 0)
            arr[count++] = arr[i]; // here count is
                                   // incremented

    // Now all non-zero elements have been shifted to
    // front and  'count' is set as index of first 0.
    // Make all elements 0 from count to end.
    while (count < n)
        arr[count++] = 0;
}
 */

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;
		unique_ptr<int[]> arr(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i)
			cin >> arr[i];

		move_all_zeroes_to_end_of_array(arr, arr_sz);

		for (int i = 0; i < arr_sz; ++i)
			cout << arr[i] << " ";
		cout << endl;
	}

	return 0;
}
