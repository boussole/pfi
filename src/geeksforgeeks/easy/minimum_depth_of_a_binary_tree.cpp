/*
Given a binary tree, your task is to complete the function minDepth which takes one argument the root of the binary tree and prints the min depth of  binary tree .

          1
       /    \
     2       3
   /
4

For the tree above the min depth is 2 ie 1 3

Input:

The task is to complete the method which takes one argument, root of Binary Tree. There are multiple test cases. For each test case, this method will be called individually.

Output:
The output will be an integer denoting the min depth of the binary tree.

Constraints:
1 <=T<= 30
1 <= Number of nodes<= 20


Example:
Input:
2
2
1 2 R 1 3 L
4
10 20 L 10 30 R 20 40 L 20 60 R

Output:
2
3


There are two test cases.  First case represents a tree with 3 nodes and 2 edges where root is 1, left child of 1 is 3 and right child of 1 is 2.   Second test case represents a tree with 4 edges and 5 nodes.
 */

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/* The Node structure is
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */
/*You are required to complete this method*/

int minDepth(Node *node, int depth, int &minDepthVal)
{
	if (node == nullptr) {
		return minDepthVal;
	}

	if (depth >= minDepthVal) {
		return minDepthVal;
	}

	if (node->left == nullptr && node->right == nullptr) {
		minDepthVal = depth;
		return depth;
	}

	return min(minDepth(node->left, depth + 1, minDepthVal), minDepth(node->right, depth + 1, minDepthVal));
}

int minDepth(Node *node)
{
	int minDepthVal = INT_MAX;
	return node ? minDepth(node, 1, minDepthVal) : 0;
}

/**
 * Another solution is based on BFS, it's more efficient
 */

// TODO: implement main

