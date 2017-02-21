/*
   Give a N*N square matrix, return an array of its anti-diagonals. Look at the example for more details.

   For Example:
   If the matrix is
   1 2 3
   4 5 6
   7 8 9

   The output should Return the following :
   [1],
   [2, 4],
   [3, 5, 7],
   [6, 8],
   [9]

   i.e print the elements of array diagonally.

   Note: The input array given is in single line and you have to output the answer in one line only.

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an integer N depicting the size of square matrix and next line followed by the value of array.

   Output:
   Print the elements of matrix diagonally in separate line.

   Constraints:
   1 ≤ T ≤ 30
   1 ≤ N ≤ 20
   0 ≤ A[i][j] ≤ 9

   Example:
      Input:
      2
      2
      1 2 3 4
      3
      1 2 3 4 5 6 7 8 9
      Output:
      1 2 3 4
      1 2 4 3 5 7 6 8 9
 */

#include <iostream>
#include <memory>

using namespace std;

int & matrix_item(unique_ptr<int[]> &matrix, int i, int j, int size)
{
	return matrix[i * size + j];
}

// speed O(N)
// memory O(1)
void print_diagonally(unique_ptr<int[]> &matrix, int size)
{
	int offset = size - 1;

	// horizontal
	int nr_items = 1;
	for (int i = 0; i < size; ++i) {
		for (int nr = 0; nr < nr_items; ++nr) {
			int pos = i + nr * offset, i = pos / size, j = pos % size;
			cout << matrix_item(matrix, i, j, size) << " ";
		}

		++nr_items;
	}

	nr_items -= 2;

	// vertical
	for (int i = size + offset; i < size * size; i += size) {
		for (int nr = 0; nr < nr_items; ++nr) {
			int pos = i + nr * offset, i = pos / size, j = pos % size;
			cout << matrix_item(matrix, i, j, size) << " ";
		}
		--nr_items;
	}

	cout << endl;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int size;
		cin >> size;

		// emulate matrix
		unique_ptr<int[]> matrix(new int[size * size]);
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				cin >> matrix_item(matrix, i, j, size);

		print_diagonally(matrix, size);
	}

	return 0;
}

