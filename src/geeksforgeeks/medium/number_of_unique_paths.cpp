/*
   Given a MxN matrix with initial position at top-left corner,
   find the number of possible unique paths to reach the bottom right corner of the grid from the initial position.

   NOTE: Possible moves can be either down or right at any point in time, i.e.,
   we can move to matrix[i+1][j] or matrix[i][j+1] from matrix[i][j].

   Input:
   The first line contains an integer T, depicting total number of test cases.
   Then following T lines contains an two integers A and B depicting the size of the grid.

   Output:
   Print the number of unique paths to reach bottom-right corner from the top-left corner.

   Constraints:
   1 ≤ T ≤ 30
   1 ≤ M ≤ 15
   1 ≤ N ≤ 15

   Example:
      Input
      2
      2 2
      3 4

      Output
      2
      10
 */

#include <iostream>
#include <memory>

using namespace std;

// speed O(N*M)
// memory O(N)
int nr_of_unique_paths(int n, int m)
{
	int nr_paths = 0;

	// create matrix NxM
	unique_ptr<int*[]> matrix(new int*[n]());
	for (int i = 0; i < n; ++i)
		matrix[i] = new int[m]();

	matrix[0][0] = 0;
	// fill edge row
	for (int i = 1; i < n; ++i)
		matrix[i][0] = 1;

	// fill edge col
	for (int i = 1; i < m; ++i)
		matrix[0][i] = 1;

	// fill middle elements
	for (int i = 1; i < n; ++i)
	for (int j = 1; j < m; ++j)
		matrix[i][j] = matrix[i - 1][j] + matrix[i][j - 1];

	return matrix[n - 1][m - 1];
}

// method 2, based on combinatorics http://qa.geeksforgeeks.org/3676/number-of-unique-paths
// There is a mathematical approach to solving this problem.
// Note that you have to take m + n - 2 steps in total.
// You have to take (m - 1) steps going down and (n-1) steps going right.
// Let 0 denote a down step and 1 denote a right step.
// So we need to find out the number of strings of length m + n - 2 which have exactly m - 1 zeroes and n - 1 ones.
// Essentially we need to choose the positions of ‘1s’, and then ‘0s’ fall into the remaining positions.
// So, the answer becomes Choose(m+n-2, n - 1).
//
//int uniquePaths(int m, int n) {
//	// m+n-2 C n-1 = (m+n-2)! / (n-1)! (m-1)!
//	long long ans = 1;
//	for (int i = n; i < (m + n - 1); i++) {
//		ans *= i;
//		ans /= (i - n + 1);
//	}
//	return (int)ans;
//}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int n, m;
		cin >> n >> m;

		cout << nr_of_unique_paths(n, m) << endl;
	}

	return 0;
}
