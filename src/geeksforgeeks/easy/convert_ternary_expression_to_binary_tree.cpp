/*
Given a string that contains ternary expressions.
The expressions may be nested, task is convert the given ternary expression to a binary Tree and return the root.

Input:
First line of input contains of test case T. The only line of test case consists of String s.

Output:
Preorder traversal of Tree formed

Constraints:
1<=T<=100
1<=|String|<=100

Example:
Input:
2
a?b:c
a?b?c:d:e
Output:
a b c
a b c d e
 */

#include <iostream>
#include <string>
#include <list>

using namespace std;

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Complete the function below
Node is as follows
struct Node{
	char data;
	Node *left,*right;
};


Input :  string expression =   a?b:c
Output :        a
              /  \
             b    c

Input : expression =  a?b?c:d:e
Output :     a
           /  \
          b    e
        /  \
       c    d

*/

struct Node{
	char data;
	Node *left,*right;
};

void clearTree(Node *n)
{
	if (!n)
		return;

	clearTree(n->left);
	clearTree(n->right);
	delete n;
}

Node *createNode(char data)
{
	Node *new_node = new Node;
	new_node->data = data;
	new_node->left = new_node->right = nullptr;
	return new_node;
}

void printBFS(Node *n)
{
	Node *stub = createNode('|');
	list<Node*> l;
	l.push_back(n);
	while (!l.empty()) {
		list<Node*> new_l;
		while (!l.empty()) {
			Node *it = l.front();
			l.pop_front();
			cout << it->data << " ";
			if (it != stub) {
				size_t before_sz = new_l.size();
				if (it->left)
					new_l.push_back(it->left);
				if (it->right)
					new_l.push_back(it->right);
				if(new_l.size() > before_sz)
					new_l.push_back(stub);
			}
		}
		cout << endl;
		l = move(new_l);
	}
	delete stub;
}

Node *convertExpressionHelper(string &expr, size_t &i)
{
	if (i >= expr.length())
		return nullptr;

	Node *node = createNode(expr[i++]);
	if (i < expr.length() && expr[i] == '?') {
		node->left = convertExpressionHelper(expr, ++i);
		node->right = convertExpressionHelper(expr, ++i);
	}

	return node;
}

Node *convertExpression(string str, int i)
{
	size_t start_pos = static_cast<size_t>(i);
	return convertExpressionHelper(str, start_pos);
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;
		Node *root = convertExpression(s, 0);
		printBFS(root);
		clearTree(root);
	}

	return 0;
}
