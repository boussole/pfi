/*
   Given an array of integers, find the nearest smaller number for every
   element such that the smaller element is on left side.If no small element present on the left print -1.

   Input:
   The first line of input contains T test cases.
   The first line of each test case contains the number of elements in the array.
   The second line of each test case contains the elements of the array.

   Output:
   Print the n elements.

   Constraints:
   1<=T<=100
   1<=N<=100
   0<=A[i]<10000

   Example:
      Input:
      2
      3
      1 6 2
      6
      1 5 0 3 4 5

      Output:
      -1 1 1
      -1 1 -1 0 3 4
 */

#include <iostream>
#include <memory>
#include <stack>

using namespace std;

/**
 * speed O(N)
 * memory O(1)
 */
void smallest_number_on_left(const unique_ptr<int[]> &in, unique_ptr<int[]> &out, size_t size)
{
	stack<int> stack;
	for (size_t i = 0; i < size; ++i) {
		while (!stack.empty() && stack.top() >= in[i]) {
			stack.pop();
		}

		out[i] = stack.empty() ? -1 : stack.top();
		stack.push(in[i]);
	}
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		unique_ptr<int[]> in(new int[arr_sz]), out(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i)
			cin >> in[i];

		smallest_number_on_left(in, out, arr_sz);

		for (int i = 0; i < arr_sz; ++i)
			cout << out[i] << " ";
		cout << endl;
	}

	return 0;
}



