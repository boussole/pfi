/*
   Given a sorted array. Write a program that creates a Balanced Binary Search Tree using array elements.
   If there are n elements in array, then floor(n/2)'th element should be chosen as root and same should be followed recursively.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   The first line of each test case is N,N is the size of array.
   The second line of each test case contains N input A[].

   Output:
   Print the preorder traversal of constructed BST.

   Constraints:
   1 ≤ T ≤ 100
   1 ≤ N ≤ 1000
   1 ≤ A[] ≤ 10000

   Example:
      Input:
      1
      7
      7 6 5 4 3 2 1

      Output:
      4 6 7 5 2 3 1
 */

#include <functional>
#include <iostream>
#include <memory>

using namespace std;

template <typename T>
struct node {
	node(const T &data, unique_ptr<node<T> > *parent) :
		_data(data),
		_parent(parent)
	{}

	T _data;

	unique_ptr<node<T> > *_parent;

	unique_ptr<node<T> > _left, _right;
};

template <typename T>
class binary_tree {
public:
	binary_tree(const unique_ptr<int[]> &arr, int arr_sz)
	{
		make(arr, 0, arr_sz - 1, _root, nullptr);
	}

	void preorder_print()
	{
		preorder_dfs(_root);

		cout << endl;
	}

protected:
	void make(const unique_ptr<int[]> &arr, int begin, int end, unique_ptr<node<T> > &n, unique_ptr<node<T> > *parent)
	{
		if (begin > end)
			return;

		int middle = (begin + end) / 2;

		n.reset(new node<T>(arr[middle], parent));

		// fill left subtree
		make(arr, begin, middle - 1, n->_left, &n);

		// fill right subtree
		make(arr, middle + 1, end, n->_right, &n);
	}

	// speed O(N)
	// memory O(1)
	void preorder_dfs(const unique_ptr<node<T> > &node)
	{
		if (!node.get())
			return;

		cout << node->_data << " ";

		preorder_dfs(node->_left);

		preorder_dfs(node->_right);
	}

private:
	unique_ptr<node<T> > _root;
};

// speed O(N)
// memory O(1)
// \note without building tree
void array_to_bst(const unique_ptr<int[]> &arr, int begin, int end)
{
	if (begin > end)
		return;

	int middle = (begin + end) / 2;

	// put to the tree
	cout << arr[middle] << " ";

	// right subtree, all elements are bigger than arr[middle]
	array_to_bst(arr, begin, middle - 1);

	// left subtree, all elements are less than arr[middle]
	array_to_bst(arr, middle + 1, end);
}

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

		// without building binary tree
		// array_to_bst(arr, 0, arr_sz - 1);
		// cout << endl;

		binary_tree<int> bt(arr, arr_sz);

		bt.preorder_print();
	}

	return 0;
}


