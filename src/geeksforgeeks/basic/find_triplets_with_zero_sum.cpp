/*
Given an array A[] of n elements. The task is to complete the function which returns true if triplets exists in array A[] whose sum is zero else returns false.

Input:
The first line of input contains an integer T, denoting the no of test cases. Then T test cases follow. The first line of each test case contains an integer N, denoting the number of elements in array. The second line of each test case contains N space separated values of the array A[].


Output:
For each test case in a new line output will be 1 if triplet exists else 0.

Constrains:
1<=T<=100
1<=N<=1000
-1000<=A[]<=1000


Example(To be used only for expected output) :
Input:
2
5
0 -1 2 -3 1
3
1 2 3
Output:
1
0
 */

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/

#include <algorithm>
#include <iostream>
#include <memory>

using namespace std;

/*You are required to complete the function below*/
bool findTriplets(int arr[], int n)
{
	sort(arr, arr + n);
	for (int i = 0; i < n; ++i) {
		int j = i + 1, k = n - 1;
		while (j < k) {
			int sum = arr[i] + arr[j] + arr[k];
			if (sum == 0)
				return true;

			if (sum > 0)
				--k;
			else
				++j;
		}
	}

	return false;
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

		cout << findTriplets(arr.get(), arr_sz) << endl;
	}

	return 0;
}


