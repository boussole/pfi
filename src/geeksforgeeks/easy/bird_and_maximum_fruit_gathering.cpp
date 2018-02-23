/*
There are N trees in a circle. Each tree has a fruit value associated with it.
A bird has to sit on a tree for 0.5 sec to gather all the fruits present on the tree and then the bird can move to a neighboring tree. It takes the bird 0.5 seconds to move from one tree to another. Once all the fruits are picked from a particular tree, she can’t pick any more fruits from that tree. The maximum number of fruits she can gather is infinite.
We are given N and M (the total number of seconds the bird has), and the fruit values of the trees. We have to maximize the total fruit value that the bird can gather. The bird can start from any tree.

Input:
The first line contains a positive integer T denoting the number of test cases. Each of the test case consists of 2 lines. The first line of each test case contains two integers N and M. Next line contains space separated sequence of N integers denoting the fruit value of each tree.

Output:
For each test case, print in a new line, the maximum number of fruits the bird can gather. As the results can be large, print your answer modulo 10^9+7

Constraints:
1 <= T <= 10^3
1 <= N, M <= 10^5

Example:
Input:
2
7 3
2 1 3 5 0 1 4
6 2
1 6 2 5 3 4

Output:
9
8

Explanation:
Assume 0-based indexing.
For the 1st case:
She can start from tree 1 and move to tree2 and then to tree 3. Hence, total number of gathered fruits = 1 + 3 + 5 = 9.
For the 2nd case:
She can start from tree 1 and move to tree 2. In this case she will gather 6 + 2 = 8 fruits.
She can also start from tree 3 and move to tree 4. In this case, too, she will gather 5 + 3 = 8 fruits.
 */

#include <vector>
#include <iostream>

using namespace std;

const unsigned long modulo_ans = 1000000000+7;

unsigned long max_fruit_gathering(const vector<int> &arr, size_t k)
{
	size_t nr_trees = min(k, arr.size());
	// case k >= arr.size();
	unsigned long ans = arr[0];
	for (size_t i = 1; i < nr_trees; ++i) {
		ans += arr[i];
		if (ans > modulo_ans)
			ans %= modulo_ans;
	}

	if (nr_trees >= arr.size())
		return ans;

	unsigned long max_ans = ans;
	int left_pos = 0, right_pos = nr_trees;
	do {
		ans -= arr[left_pos];
		ans += arr[right_pos];
		if (ans > modulo_ans)
			ans %= modulo_ans;

		max_ans = max(ans, max_ans);

		left_pos = (left_pos + 1) % arr.size();
		right_pos = (right_pos + 1) % arr.size();
	} while (left_pos != 0);

	return max_ans;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		size_t k;
		cin >> arr_sz >> k;

		vector<int> arr(arr_sz);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		cout << max_fruit_gathering(arr, k) << endl;
	}

return 0;
}

