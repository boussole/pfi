/*
   Given Binary Search Tree.
   The task is to find sum of all elements smaller than and equal to Kth smallest element.

   Input:
   The first line of input contains a single integer T denoting the number of test cases.
   Then T test cases follow. Each test case consists of three lines.
   First line of each test case consist of integer N, denoting the number of elements in a BST.
   Second line of each test case consists of N space separated integers denoting the elements in the BST.
   Third line of each test case consists of an integer K, denoting the Kth smallest elements.

   Output:
   It should be single line output, Print the respective output in the respective line.

   Constraints:
   1<=T<=100
   1<=N<=50
   1<=K<=N

   Example:
   Input:
   1
   7
   20 8 4 12 10 14 22
   3
   Output:
   22
   Explanation:
   The tree for above input will look like this:

         20
        /  \
       8    22
      / \
     4  12
        / \
       10  14

   Sum of 3 smallest elements are: 4 + 8 + 10 = 22
 */

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
class bst {
public:
	bst()
	{}

	~bst()
	{}

	void add(const T &data)
	{
		if (!_root.get()) {
			_root.reset(new node<T>(data, nullptr));
			return;
		}

		unique_ptr<node<T> > *it = &_root;
		while (true) {
			// FIX: this is fix for input data, we don't allow duplicates
			if (data == (*it)->_data)
				break;

			if (data < (*it)->_data) {
				if (!(*it)->_left.get()) {
					(*it)->_left.reset(new node<T>(data, it));
					break;
				} else
					it = &(*it)->_left;
			} else {
				if (!(*it)->_right.get()) {
					(*it)->_right.reset(new node<T>(data, it));
					break;
				} else
					it = &(*it)->_right;
			}
		}
	}

	int sum_of_k_smallest(int k) {
		int sum = 0;

		node<T> *n = nullptr;

		while (k-- && (n = successor(n)))
			sum += n->_data;

		return sum;
	}

protected:
	// speed O(H)
	// memory O(1)
	node<T> * successor(node<T> *n)
	{
		// start search at the roor
		if (!n) {
			n = _root.get();
			while (n->_left.get())
				n = n->_left.get();

			return n;
		}

		// node is a root or a fork
		if (!n->_parent || n->_right.get()) {
			n = n->_right.get();
			if (!n)
				return nullptr;

			while (n->_left.get())
				n = n->_left.get();

			return n;
		}

		// node is the most left node in subtree, successor is parent
		if ((*(n->_parent))->_left.get() == n)
			return (*(n->_parent)).get();

		// node is the most right node in subtree
		while (n->_parent && (*(n->_parent))->_right.get() == n)
			n = (*(n->_parent)).get();

		return (n->_parent) ? (*(n->_parent)).get() : nullptr;
	}

private:
	unique_ptr<node<T> > _root;
};

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int nr_tree_nodes;
		cin >> nr_tree_nodes;

		bst<int> bst;
		for (int i = 0; i < nr_tree_nodes; ++i) {
			int data;
			cin >> data;
			bst.add(data);
		}

		int k;
		cin >> k;
		cout << bst.sum_of_k_smallest(k) << endl;
	}
}



