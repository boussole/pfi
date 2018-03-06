/*
Given a Binary Tree, your task is to print its level order traversal where each level is separated by $ 

For the below tree the output will be 1 $ 2 3 $ 4 5 6 7 $ 8 $

          1
       /     \
     2        3
   /    \     /   \
  4     5   6    7
    \
     8

            

Input:
The task is to complete the method which takes one argument, root of Binary Tree. The struct Node has a data part which stores the data, pointer to left child and pointer to right child.
There are multiple test cases. For each test case, this method will be called individually.

Output:
The function should print the level order traversal of the tree as specified in the problem statement .

Constraints:
1 <=T<= 20
1 <= Number of edges<= 1000
1 <= Data of a node<= 100

Example:
Input:
2
2
1 2 R 1 3 L
4
10 20 L 10 30 R 20 40 L 20 60 R

Output:
1 $ 3 2  $
10 $ 20 30 $ 40 60 $
 

There are two test casess.  First case represents a tree with 3 nodes and 2 edges where root is 1, left child of 1 is 3 and right child of 1 is 2.   Second test case represents a tree with 4 edges and 5 nodes.
*/

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/* A binary tree Node
struct Node
{
    int data;
    Node* left, * right;
}; */
//You are required to complete this method
void levelOrder(Node* node)
{
    if (!node) {
        cout << "$\n";
        return;
    }
    
    queue<Node*> q;
    q.push(node);
    while (!q.empty()) {
        queue<Node*> aux;
        while (!q.empty()) {
            Node *n = q.front();
            cout << n->data << " ";
            if (n->left)
                aux.push(n->left);
            if (n->right)
                aux.push(n->right);
            q.pop();
        }
        
        cout << "$ ";
        q = move(aux);
    }
}

