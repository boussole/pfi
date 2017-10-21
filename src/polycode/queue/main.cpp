#include <common/common.h>
#include "queue.h"
#include "priority_queue.h"

using namespace conq_queue;
using namespace conq_stack;
using namespace std;

TICKET_FN(9)
{
	std :: cout << "#" << ticket << std :: endl;

	Queue<int, QueueThrough2StacksImpl> q;

	int val = 0;

	// 0 -> q
	q.enqueue(val);
	cout << "Put " << val++ << endl;

	// q -> 0
	cout << "Get " << q.top() << " min = " << q.min() << endl;
	q.dequeue();

	// 1,2 -> q
	do {
		q.enqueue(val);
		cout << "Put " << val++ << endl;
	} while (val < 3);

	// q -> 1
	cout << "Get " << q.top() << " min = " << q.min() << endl;
	q.dequeue();

	// 3,4,5 -> q
	do {
		q.enqueue(val);
		cout << "Put " << val++ << endl;
	} while (val < 6);

	// q ->
	while (!q.is_empty()) {
		cout << "Get " << q.top() << " min = " << q.min() << endl;
		q.dequeue();
	}

	cout << "Put = " << "10" << endl;

	q.enqueue(10);

	cout << "min = " << q.min() << endl;

	cout << "Get = " << q.top() << endl;

	cout << "min = " << q.min() << endl;

	cout << "Put = " << "9" << endl;

	q.enqueue(9);

	cout << "min = " << q.min() << endl;

	cout << "Put = " << "11" << endl;

	q.enqueue(11);

	cout << "min = " << q.min() << endl;

	q.dequeue();

	cout << "top = " << q.top() << " min = " << q.min() << endl;

	q.dequeue();

	cout << "min = " << q.min() << endl;
}

TICKET_FN(33)
{
	cout << "#" << ticket << endl;

	Queue<int, QueueThroughStackImpl> q;

	int counter = 0;

	cout << "put = " << counter << endl;
	q.enqueue(counter++);

	cout << "--->top = " << q.top() << endl;

	while (counter < 4) {
		cout << "put = " << counter << endl;
		q.enqueue(counter++);
	}

	int pop_counter = 2;
	while (pop_counter) {
		cout << "pop = " << q.top() << endl;
		q.dequeue();
		pop_counter--;
	}

	cout << "--->top = " << q.top() << endl;

	while (counter < 10) {
		cout << "put = " << counter << endl;
		q.enqueue(counter++);
	}

	while (!q.is_empty()) {
		cout << "pop = " << q.top() << endl;
		q.dequeue();
	}

	assert(q.is_empty());
}

TICKET_FN(274)
{
	cout << "#" << ticket << ": priority queue\n";

//	PrioriryQueue<std :: string, std :: less_equal<int> > pq(10);
//
//	cout << "enqueue\n";
//
//	pq.enqueue("two", 2);
//	cout << "top = " << pq.top() << endl;
//	pq.check();
//
//	pq.enqueue("one", 1);
//	cout << "top = " << pq.top() << endl;
//	pq.check();
//
//	pq.enqueue("three", 3);
//	cout << "top = " << pq.top() << endl;
//	pq.check();
//
//	pq.enqueue("zero", 0);
//	cout << "top = " << pq.top() << endl;
//	pq.check();
//
//	cout << "dequeue (size = " << pq.size() << ")\n";
//
//	cout << "top = " << pq.top() << endl;
//	pq.dequeue();
//	pq.check();
//
//	cout << "top = " << pq.top() << endl;
//	pq.dequeue();
//	pq.check();
//
//	cout << "top = " << pq.top() << endl;
//	pq.dequeue();
//	pq.check();
//
//	cout << "top = " << pq.top() << endl;
//	pq.dequeue();
//	pq.check();
//
//	cout << "size = " << pq.size() << endl;
//
//	while (q.size() > 0) {
//		cout << "top = " << q.top() << endl;
//		q.dequeue();
//		q.check();
//	}

	cout << "enqueue example\n";
	int test[] = {1, 2, 4, 5, 6, 8, 9, 10, 11, 16 };
	PrioriryQueue<std :: string> q(ARRAY_SIZE(test));

	for (std :: size_t i = 0; i < ARRAY_SIZE(test); ++i) {
		q.enqueue(std :: to_string(test[i]), test[i]);
		q.check();
	}

	q.remove("11");
	q.check();

	q.remove("5");
	q.print();
	q.check();

	q.changePriority("6", 17);
	q.print();
	q.check();

	q.changePriority("11", 0);
	q.print();
	q.check();

	q.remove("11");
	q.print();
	q.check();

	q.changePriority("1", 11);
	q.print();
	q.check();

	while (q.size() > 0) {
		cout << "top = " << q.top() << endl;
		q.dequeue();
		q.check();
	}
}

int main(int argc, char ** argv)
{
	/* uncomment one of them */

//	ticket_274(argc, argv);

//	ticket_33(argc, argv);

//	ticket_9(argc, argv);

	return 0;
}
