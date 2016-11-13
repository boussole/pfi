/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include "stack_wrapper.h"
#include "stack.h"

using namespace std;
using namespace conq_stack;

TICKET_FN(55)
{
	cout << "#" << ticket << endl;

	if (argc < 2) {
		cout << "usage: " << *argv << " <stack size>\n";
		return;
	}

	int size = atoi(argv[1]);
	if (size <= 0) {
		cout << "invalid stack size: " << size << endl;
		return;
	}

	SimpleStack<int> stack;

	cout << "input stack:";

	int value = 0, counter = 0;

	while (counter++ < size) {
		cout << " " << size - counter; /**< LAST INPUT FIRST OUTPUT */
		stack.push(value++);
	}

	cout << std :: endl;

	stack.revert();

//	stack.revertUsingStackSz();

	cout << "output stack:";

	counter = 0;

	while (counter++ < size) {
		cout << " " << stack.top();
		stack.pop();
	}

	cout << std :: endl;
}

TICKET_FN(111)
{
	std :: cout << "#" << ticket << std :: endl;

	Stack<int, StackThrough2QueuesImpl> q;

	int i = 0;

	// put 0, 1
	for (; i < 2; i++) {
		cout << "put " << i << endl;
		q.push(i);
	}

	// get 1, 0
	while (!q.is_empty()) {
		cout << "get " << q.top() << endl;
		q.pop();
	}

	// put 2, 3, 4
	for (; i < 5; i++) {
		cout << "put " << i << endl;
		q.push(i);
	}

	// get 4
	cout << "get " << q.top() << endl;
	q.pop();

	// put 5, 6 (3, 2)
	for (; i < 7; i++) {
		cout << "put " << i << endl;
		q.push(i);
	}

	// get 6 (5, 3, 2)
	cout << "get " << q.top() << endl;
	q.pop();

	// put 7 (7, 5, 3, 2)
	cout << "put " << i << endl;
	q.push(i);

	// get 7, 5, 3, 2
	while (!q.is_empty()) {
		cout << "get " << q.top() << endl;
		q.pop();
	}

	assert(q.is_empty());
}

int main(int argc, char ** argv)
{
	/* uncomment one of them */

	//ticket_111(argc, argv);

	//ticket_55(argc, argv);

	return 0;
}


