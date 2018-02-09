/*
Given a linked list, write a function to reverse every k nodes
(where k is an input to the function).

If a linked list is given as 1->2->3->4->5->6->7->8->NULL and k = 3 then output will be 3->2->1->6->5->4->8->7->NULL.

Input:
In this problem, method takes two argument: the head of the linked list and int k.
You should not read any input from stdin/console.
The struct Node has a data part which stores the data and a next pointer which points to the next element of the linked list.
There are multiple test cases. For each test case, this method will be called individually.

Output:
Reverse the linked list in the group of given size and return the reference of starting node(head) of the reversed Linked list .

Note: If you use "Test" or "Expected Output Button" use below example format

Example:
Input:
1
8
1 2 2 4 5 6 7 8
4

Output:
4 2 2 1 8 7 6 5
** For More Input/Output Examples Use 'Expected Output' option **
*/

#include <iostream>

using namespace std;

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*
  Reverse a linked list
  The input list will have at least one element
  Return the node which points to the head of the new LinkedList
  Node is defined as
  struct node
  {
     int data;
     struct Node *next;
  }
*/

struct node {
	node(int d) : data(d), next(nullptr) {}
	int data;
	struct node *next;
};

void reverse(node *head)
{
	node *next, *prev = nullptr;
	while (head) {
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}
}

node *reverse(node *head, int k)
{
	// Complete this method
	if (!head)
		return nullptr;

	node *h = head, *t = head;
	for (int i = 1; i < k && t->next; ++i) {
		t = t->next;
	}

	node *new_head = t;
	node *nn = t->next;
	t->next = nullptr;
	reverse(h);
	h->next = nn;

	node *old_t = h;
	while (nn) {
		h = t = nn;
		for (int i = 1; i < k && t->next; ++i) {
			t = t->next;
		}

		nn = t->next;
		t->next = nullptr;
		reverse(h);
		old_t->next = t;
		h->next = nn;
		old_t = h;
	}

	return new_head;
}

void print_ll(node *head)
{
	while (head) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

void clear(node *head)
{
	while (head) {
		node *d = head;
		head = head->next;
		delete d;
	}
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		size_t size;
		cin >> size;

		int val;
		cin >> val;
		node *head = new node(val);
		node *it = head;
		for (size_t i = 1; i < size; ++i) {
			cin >> val;
			it->next = new node(val);
			it = it->next;
		}

		int k;
		cin >> k;
		head = reverse(head, k);
		print_ll(head);
		clear(head);
	}

	return 0;
}

