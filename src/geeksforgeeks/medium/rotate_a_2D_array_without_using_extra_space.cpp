/*
   You are given an n x n 2D matrix representing an image.
   Rotate the image by 90 degrees (clockwise).
   You need to do this in place.
   Note that if you end up using an additional array, you will only receive partial score.

   Example:
   If the array is
   1 2 3 4 5 6 7 8 9
   Then the rotated array becomes:
   7 4 1 8 5 2 9 6 3

   Input:
   The first line contains an integer 'T' denoting the total number of test cases.
   In each test cases, the first line contains an integer 'N' denoting the size of the 2D square matrix.
   And in the second line, the elements of the matrix A[][], each separated by a space in row major form.

   Output:
   For each test case, print the elements of the rotated array row wise, each element separated by a space.
   Print the output of each test case in a new line.

   Constraints:
   1 ≤ T ≤ 70
   1 ≤ N ≤ 10
   1 ≤ A [ i ][ j ] ≤ 100

   Example:
   Input:
   2
   3
   1 2 3 4 5 6 7 8 9
   2
   56 96 91 54

   Output:
   7 4 1 8 5 2 9 6 3
   91 56 54 96
 */

#include <iostream>
#include <memory>

using namespace std;

// speed O(N*N) - linear
// memory O(1)
void rotate_a_2D_array_without_using_extra_space(unique_ptr<int*[]> &matrix, int size)
{
	// swap elements in each line
	for (int row = 0; row < size; ++row) {
		for (int left = 0, right = size - 1; left < size / 2; ++left, --right) {
			swap(matrix[row][left], matrix[row][right]);
		}
	}

	// swap elements in all diagonals
	// down and main
	for (int row = size - 2, col = 1; row >= 0; --row, ++col)
	{
		for (int row_left = row, row_right = size - 1, col_left = 0, col_right = col;
		     row_left < row_right;
		     ++row_left, --row_right, ++col_left, --col_right)
		{
			swap(matrix[row_left][col_left], matrix[row_right][col_right]);
		}
	}

	// right
	for (int col = 1, row = size - 2; col < size - 1; ++col, --row)
	{
		for (int row_left = 0, row_right = row, col_left = col, col_right = size - 1;
		     row_left < row_right;
		     ++row_left, --row_right, ++col_left, --col_right)
		{
			swap(matrix[row_left][col_left], matrix[row_right][col_right]);
		}
	}
}

// another solution 2
// http://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
// the idea is move group of elements in contour

// another solution 3
// http://www.geeksforgeeks.org/rotate-matrix-90-degree-without-using-extra-space-set-2/
// is similar to my

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int size;
		cin >> size;

		unique_ptr<int*[]> matrix(new int*[size]);
		for (int i = 0; i < size; ++i)
			matrix[i] = new int[size];

		for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			cin >> matrix[i][j];

		rotate_a_2D_array_without_using_extra_space(matrix, size);

		for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			cout << matrix[i][j] << " ";
		cout << endl;
	}

	return 0;
}


