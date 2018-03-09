/*
Write a function to print spiral order traversal of a tree. For below tree, function should print 1, 2, 3, 4, 5, 6, 7.

Input:
The task is to complete the method which takes one argument, root of the Tree. The struct node has a data part which stores the data, pointer to left child and pointer to right child.
There are multiple test cases. For each test case, this method will be called individually.

Output:
The function should print level order traversal in spiral form .

Constraints:
1 <=T<= 30
1 <=Number of nodes<= 3000
1 <=Data of a node<= 1000

Example:
Input:
2
2
1 2 R 1 3 L
4
10 20 L 10 30 R 20 40 L 20 60 R

Output:
1 3 2
10 20 30 60 40

There are two test casess.  First case represents a tree with 3 nodes and 2 edges where root is 1, left child of 1 is 3 and right child of 1 is 2.   Second test case represents a tree with 4 edges and 5 nodes.
 */

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/* A binary tree node has data, pointer to left child
   and a pointer to right child
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */
void printSpiral(Node *root)
{

	//Your code here
	std::list<Node*> list;
	list.push_back(root);
	bool from_left_to_right = false;
	while (!list.empty()) {
		std::list<Node*> aux;
		while (!list.empty()) {
			Node *n = list.front();
			list.pop_front();
			cout << n->data << " ";

			if (from_left_to_right) {
				if (n->left)
					aux.push_front(n->left);

				if (n->right)
					aux.push_front(n->right);
			} else {
				if (n->right)
					aux.push_front(n->right);

				if (n->left)
					aux.push_front(n->left);
			}
		}

		from_left_to_right = !from_left_to_right;
		list = move(aux);
	}
}
