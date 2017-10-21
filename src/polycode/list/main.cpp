/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include "single_linked_list.h"

using namespace std;
using namespace conq_list;

/**
 * #226: change neighbours
 */
TICKET_FN(226)
{
	cout << "#" << ticket << endl;

	SingleLinkedList<std :: string> list;

	for (int i = 1; i < argc; i++) {
		list.pushTail(argv[i]);
	}

	cout << "src list:";

	list.forEach([](const std :: string & value) { cout << " " << value; });

	cout << endl;

	list.swapNeighbours();

	cout << "dst list:";

	list.forEach([](const std :: string & value) { cout << " " << value; } );

	cout << endl;
}

/**
 *  #41: revert single linked list
 */
TICKET_FN(41)
{
	cout << "#" << ticket << endl;

	SingleLinkedList<std :: string> list;

	for (int i = 1; i < argc; i++) {
		list.pushTail(argv[i]);
	}

	cout << "src list:";

	list.forEach([](const std :: string & value) { cout << " " << value; });

	cout << endl;

	list.revert();

	cout << "dst list:";

	list.forEach([](const std :: string & value) { cout << " " << value; } );

	cout << endl;
}

TICKET_FN(95)
{
	cout << "#" << ticket << ": merge sorted lists\n";

	if (argc < 4) {
		cout << "usage: " << *argv << " size1 \"array1\" size2 \"array2\"\n";
		return;
	}

	int size1 = atoi(argv[1]), size2 = atoi(argv[3]);
	if (size1 < 0 || size2 < 0) {
		cout << "size of lists must be >=0 (size1 = " << size1 << ", size2 = " << size2 << ")\n";
		return;
	}

	SingleLinkedList<int> in1, in2, merged;

	if (!fillFromString(in1, size1, argv[2]) || !fillFromString(in2, size2, argv[4])) {
		cout << "invalid size of array\n";
		return;
	}

	cout << "in1:";

	in1.forEach([](int value) { cout << " " << value; } );

	cout << "\nin2:";

	in2.forEach([](int value) { cout << " " << value; } );

	SingleLinkedList<int> :: mergeSortedLists(in1, in2, merged, std :: less<int>());

	cout << "\nmerged:";

	merged.forEach([](int value) {cout << " " << value; } );

	cout << endl;
}

TICKET_FN(232)
{
	cout << "#" << ticket << ": merge sort of single linked list\n";

	SingleLinkedList<int> l;

	if (argc < 3) {
		cout << "usage: " << *argv << "< list size >" " < a[0] a[1] ... a[size - 1] >\n";
		return;
	}

	int size = atoi(argv[1]);

	if ((size < 0) || !fillFromString(l, size, argv[2])) {
		std :: cout << "invalid input params\n";
		return;
	}

	cout << "src: ";
	l.forEach([](int value) {cout << " " << value; } );

	l.sortNaturalMerge< less<int> >();

	cout << "\nsorted: ";
	l.forEach([](int value) {cout << " " << value; } );

	testSortOrder(l);

	cout << endl;
}

TICKET_FN(227)
{
	cout << "#" << ticket << ": find cycle in single linked list (without modification)" << endl;

	// definition looks like ugly
	std :: unique_ptr<SingleLinkedList<int> :: _Node[] > unit(new SingleLinkedList<int> :: _Node[5]);
	for (int i = 0; i < 5; ++i) {
		unit[i].value = i;
	}

	SingleLinkedList<int> :: _Node * loop;
	std :: size_t loopLen = 0;
	bool res = false;

	// test 1
	unit[0].next = &unit[1];
	unit[1].next = &unit[2];
	unit[2].next = &unit[3];
	unit[3].next = &unit[2];
	res = SingleLinkedList<int> :: findLoop(&unit[0], loop, loopLen);
	cout << "found = " << res << " head = " << loop->value << " len = " << loopLen << endl;

	// test 2
	unit[3].next = &unit[4];
	unit[4].next = &unit[0];
	res = SingleLinkedList<int> :: findLoop(&unit[0], loop, loopLen);
	cout << "found = " << res << " head = " << loop->value << " len = " << loopLen << endl;

	// test 3
	unit[3].next = &unit[0];
	res = SingleLinkedList<int> :: findLoop(&unit[0], loop, loopLen);
	cout << "found = " << res << " head = " << loop->value << " len = " << loopLen << endl;

	// test 4
	unit[3].next = &unit[3];
	res = SingleLinkedList<int> :: findLoop(&unit[0], loop, loopLen);
	cout << "found = " << res << " head = " << loop->value << " len = " << loopLen << endl;

	// test 5
	unit[3].next = nullptr;
	res = SingleLinkedList<int> :: findLoop(&unit[0], loop, loopLen);
	cout << "found = " << res << " head = " << loop->value << " len = " << loopLen << endl;

	// test 6
	unit[0].next = &unit[0];
	res = SingleLinkedList<int> :: findLoop(&unit[0], loop, loopLen);
	cout << "found = " << res << " head = " << loop->value << " len = " << loopLen << endl;
}

TICKET_FN(61)
{

	cout << "#" << ticket << ": common part of single linked list\n";

	std :: unique_ptr<SingleLinkedList<int> :: _Node[] > unit(new SingleLinkedList<int> :: _Node[7]);

	for (int i = 0; i < 7; ++i) {
		unit[i].value = i;
	}

	std :: function<void(SingleLinkedList<int> :: _Node *, SingleLinkedList<int> :: _Node*)> test =
		[](SingleLinkedList<int> :: _Node * l1, SingleLinkedList<int> :: _Node * l2)->void {
			SingleLinkedList<int> :: _Node *it = nullptr;
			cout << "l1:"; it = l1; while (it) { cout << " " << it->value; it = it->next; } cout << endl;
			cout << "l2:"; it = l2; while (it) { cout << " " << it->value; it = it->next; } cout << endl;

			it = SingleLinkedList<int> :: findCommonPart(l1, l2);
			if (it)
				cout << "found in node = " << it->value << endl;
			else
				cout << "not found\n";
		};

	// test 0 : head both
	unit[0].next = &unit[1];
	unit[1].next = &unit[2];
	unit[2].next = &unit[3];
	unit[3].next = &unit[4];
	unit[4].next = &unit[5];
	unit[5].next = &unit[6];
	unit[6].next = nullptr;

	test(&unit[0], &unit[0]);

	// test 1 : l2 == last
	test(&unit[0], &unit[6]);

	// test 2 : l1 == last
	test(&unit[6], &unit[0]);

	// test 3 : in the middle
	unit[0].next = &unit[1];
	unit[1].next = &unit[2];
	unit[2].next = &unit[3];
	unit[3].next = &unit[4];
	unit[4].next = nullptr;
	unit[5].next = &unit[6];
	unit[6].next = &unit[3];
	test(&unit[0], &unit[5]);

	// test 4 : at the end
	unit[6].next = &unit[4];
	test(&unit[0], &unit[5]);

	// test 5 : no common
	unit[6].next = nullptr;
	test(&unit[0], &unit[5]);

	// test 6 : at the begin
	unit[6].next = &unit[0];
	test(&unit[0], &unit[5]);
}

TICKET_FN(34)
{
	cout << "#" << ticket << ": copy single linked list with random pointer\n";
#define NODES 5
#define NEXT1(n) n->next
#define NEXT2(n) NEXT1(NEXT1(n))
#define NEXT3(n) NEXT2(NEXT1(n))
#define NEXT4(n) NEXT2(NEXT2(n))
#define NEXT5(n) NEXT3(NEXT2(n))

	//
	SingleLinkedListWithRandomPointer<int> * orig = nullptr, * it = nullptr, * clone = nullptr;
	for (int i = 0; i < NODES; ++i) {
		if (!orig) {
			orig = new SingleLinkedListWithRandomPointer<int>(i + 1);
			it = orig;
		}
		else {
			NEXT1(it) = new SingleLinkedListWithRandomPointer<int>(i + 1);
			it = static_cast<SingleLinkedListWithRandomPointer<int> *> (NEXT1(it));
		}
	}

	// make random pointers
	orig->_random = static_cast<SingleLinkedListWithRandomPointer<int> *>(NEXT2(orig));
	static_cast<SingleLinkedListWithRandomPointer<int> *>(NEXT1(orig))->_random = orig;
	static_cast<SingleLinkedListWithRandomPointer<int> *>(NEXT2(orig))->_random = static_cast<SingleLinkedListWithRandomPointer<int> *>(NEXT4(orig));
	static_cast<SingleLinkedListWithRandomPointer<int> *>(NEXT3(orig))->_random = static_cast<SingleLinkedListWithRandomPointer<int> *>(NEXT2(orig));
	static_cast<SingleLinkedListWithRandomPointer<int> *>(NEXT4(orig))->_random = static_cast<SingleLinkedListWithRandomPointer<int> *>(NEXT1(orig));

	// print
	std :: function<void(const char *)> print =
		[&](const char * filename) {
			std::remove(filename);

			ofstream o(filename);

			if (o.fail()) {

				cout << "file opening fail" << filename << endl;
				return;
			}

			o << "digraph g {" << endl;

			while (it) {
				o << (uint64_t)it << "[label=" << it->value << "];" << endl;
				if (it->next)
					o << (uint64_t)it << " -> " << (uint64_t)it->next << std :: endl;

				o << (uint64_t)it << " -> " << (uint64_t)it->_random << " [color=\"red\"] "<< endl;

				it = static_cast<SingleLinkedListWithRandomPointer<int> *>(it->next);
			}

			o << "}" << endl;
		}
	;

	// delete
	std :: function<void()> clear = [&]() {
		while (it) {
			SingleLinkedListWithRandomPointer<int> * tmp = static_cast<SingleLinkedListWithRandomPointer<int> *>(NEXT1(it));
			delete it;
			it = tmp;
		}
	};

	it = orig; // for print function
	print("/tmp/34_orig");

	cloneSingleLinkedListWithRandomPointer(orig, clone);

	it = clone; // for print function
	print("/tmp/34_clone");

	it = orig; // for clear function
	clear();

	it = clone; // for clear function
	clear();

#undef NODES
#undef NEXT1
#undef NEXT2
#undef NEXT3
#undef NEXT4
#undef NEXT5
}

int main(int argc, char ** argv)
{
	/* uncomment one of them */

//	ticket_34(argc, argv);

//	ticket_61(argc, argv);

//	ticket_227(argc, argv);

//	ticket_232(argc, argv);

//	ticket_95(argc, argv);

//	ticket_226(argc, argv);

//	ticket_41(argc, argv);
}
