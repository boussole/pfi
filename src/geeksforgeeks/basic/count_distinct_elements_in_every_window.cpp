/*
Given an array A[] of size n and an integer k, your task is to complete the function countDistinct which prints the count of distinct numbers in all windows of size k in the array A[].

Example

Input:  A[] = {1, 2, 1, 3, 4, 2, 3};
            k = 4
Output:
3 4 4 3
Explanation:
First window is {1, 2, 1, 3}, count of distinct numbers is 3
Second window is {2, 1, 3, 4} count of distinct numbers is 4
Third window is {1, 3, 4, 2} count of distinct numbers is 4
Fourth window is {3, 4, 2, 3} count of distinct numbers is 3

Input:
The first line of input contains an integer T denoting the no of test cases. Then T test cases follow. Each test case contains two integers n and k. Then in the next line are N space separated values of the array A[].

Output:
For each test case in a new line print the space separated values denoting counts of distinct numbers in all windows of size k in the array A[].

Constraints:
1<=T<=100
1<=n,k<=100
1<=A[]<=100

Example(To be used only for expected output):
Input:
2
7 4
1 2 1 3 4 2 3
3 2
4 1 1
Output:
3 4 4 3
2 1
 */

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <memory>

using namespace std;

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/

class SmallHash {
public:
	SmallHash() : _nr_distinct(0)
	{ fill(_hash, _hash + 101, 0); }

	~SmallHash()
	{}

	void add(int val)
	{
		if (_hash[val]++ == 0) {
			++_nr_distinct;
		}
	}

	void del(int val)
	{
		if (--_hash[val] == 0) {
			--_nr_distinct;
		}
	}

	int nr_distinct()
	{
		return _nr_distinct;
	}

private:
	int _nr_distinct;
	int _hash[101];
};

/*You are required to complete below method */
void countDistinct(int A[], int k, int n)
{
	SmallHash h_tbl;
	int i = 0;
	for (; i < k; ++i) {
		h_tbl.add(A[i]);
	}

	cout << h_tbl.nr_distinct();
	if (n < k) {
		return;
	}

	for (; i < n; ++i) {
		h_tbl.del(A[i - k]);
		h_tbl.add(A[i]);
		cout << " " << h_tbl.nr_distinct();
	}
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz, k;
		cin >> arr_sz >> k;

		unique_ptr<int[]> arr(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		countDistinct(arr.get(), arr_sz, k);
	}

	return 0;
}

