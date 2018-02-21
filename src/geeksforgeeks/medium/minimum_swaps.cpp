/*
Given an array of N distinct elementsA[ ], find the minimum number of swaps required to sort the array.
Your are required to complete the function which returns an integer denoting the minimum number of swaps, required to sort the array.

Examples:

Input : {4, 3, 2, 1}
Output : 2
Explanation : Swap index 0 with 3 and 1 with 2 to
              form the sorted array {1, 2, 3, 4}.

Input : {1, 5, 4, 3, 2}
Output : 2

Input:
The first line of input contains an integer T denoting the no of test cases . Then T test cases follow . Each test case contains an integer N denoting the no of element of the array A[ ]. In the next line are N space separated values of the array A[ ] .

Output:
For each test case in a new line output will be an integer denoting  minimum umber of swaps that are  required to sort the array.

Constraints:
1<=T<=100
1<=N<=100
1<=A[] <=1000

Example(To be used only for expected output):
Input:
2
4
4 3 2 1
5
1 5 4 3 2
Output:
2
2
 */

#include <algorithm>
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/* You are required to complete this method */
int minSwaps(int A[], int N) {
	vector<pair<int, size_t>> aux(N);
	for (int i = 0; i < N; ++i) {
		aux[i] = make_pair(A[i], i);
	}

	sort(aux.begin(), aux.end(), [](const pair<int, size_t> &l, const pair<int, size_t> &r) {
		return l.first < r.first;
	});

	int ans = 0;
	for (size_t i = 0; i < aux.size(); ++i) {
		size_t cur = i;
		size_t cycle = 0;
		while (aux[cur].second != cur) {
			++cycle;
			size_t next = aux[cur].second;
			aux[cur].second = cur;
			cur = next;
		}

		if (cycle)
			ans += cycle - 1;
	}

	return ans;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		unique_ptr<int[]> arr(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		cout << minSwaps(arr.get(), arr_sz) << endl;
	}

	return 0;
}
