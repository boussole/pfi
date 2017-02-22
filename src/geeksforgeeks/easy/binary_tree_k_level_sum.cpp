/*
   Given a binary tree and a number K, the task is to find sum of tree nodes at level k.
   The Binary Tree s given in string form: (node-value(left-subtree)(right-subtree)).

   Input:
   The first line of input contains an integer T denoting the no of test cases.
   Then T test cases follow.
   Each test case contains an integer K denoting level of Binary Tree for which we need sum.
   Next line is string which represents Binary Tree.

   Output:
   Print the Sum of all the elements at k level in each line.

   Constraints:
   1<=T<=100
   1<=K<=20

   Example:
      Input:
      1
      2
      (0(5(6()())(4()(9()())))(7(1()())(3()())))
      Output:
      14

   Explaination:
   The Tree from the above String will formed as:
                            0
                          /   \
                         5     7
                        / \   / \
                       6   4 1   3
                            \
                             9
 */

#include <assert.h>

#include <iostream>
#include <string>

using namespace std;

// speed O(N)
// memory O(1)
size_t binary_tree_k_level_sum(const string &description, int level)
{
	int l = -1;
	size_t i = 0;
	size_t sum = 0;
	while (i < description.length()) {
		if (description[i] == '(') {
			char value[64]; size_t value_sz = 0;
			++i;
			++l;

			while (isdigit(description[i]))
				value[value_sz++] = description[i++];
			value[value_sz] = 0;

			if (l == level)
				sum += atoi(value);
		} else {
			assert(l >= 0);
			++i;
			--l;
		}
	}

	return sum;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int level;
		cin >> level;
		string description;
		cin >> description;

		cout << binary_tree_k_level_sum(description, level) << endl;
	}

	return 0;
}


