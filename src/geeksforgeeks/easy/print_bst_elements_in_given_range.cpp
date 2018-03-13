/*
Given a Binary Search Tree (BST) and a range, print all the numbers in the BST that lie in the given range. You are required to complete the function printNearNodes. You should not read any input from stdin/console. There are multiple test cases. For each test case, this method will be called individually.

Input (only to be used for Expected Output):
The first line of the input contains an integer 'T' denoting the nummber of test cases. Then 'T' test cases follow. Each test case consists of three lines. Description of  test cases is as follows:
The First line of each test case contains an integer 'N' which denotes the no of nodes in the BST.   .
The Second line of each test case contains 'N' space separated values of the nodes in the BST.
The Third line of each test case contains two space separated integers 'l' and 'h' denoting the range, where l < h .


Output:
You are required to complete the function printNearNodes which takes three arguments. The first being the root of the tree, and then two integers l and h, denoting the range. The function shold print all the nodes which lie in the given range in the BST .

Constraints:
1 <= T <= 50
1 <= N <= 50
1 <= l < h < 1000


Example:
Input
1
6
10 5 50 1 40 100
5 45

Output
5 10 40
 */

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/* The structure of a BST Node is as follows:
struct Node
{
    int data;
    Node * right, * left;
}; */
void printNearNodes(Node *root, int l, int h)
{
	if (!root)
		return;

	if (l < root->data)
		printNearNodes(root->left, l, h);

	if (root->data >= l && root->data <= h)
		cout << root->data << " ";

	if (h > root->data)
		printNearNodes(root->right, l, h);
}
