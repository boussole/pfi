/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include <common/common.h>
#include "tree.h"
#include "bst.h"
#include "splay_tree.h"

using namespace std;
using namespace conq_tree;

/*
              __________________________ L0 ________________________
             /                            |                         \
           L1.1                          L1.2                       L1.3
         /     \                        /    \                       |
  ___L2.1____   L2.2                  L2.3  L2.4                   L2.5
 /    |     |                             |                          |
L3.1 L3.2  L3.3                          L3.4                      L3.5
      |                                                              |
     / \                                                             |
 L4.1 L4.2                                                          L4.3
                                                                  ___|____
                                                                 /   |    \
                                                              L5.1  L5.2  L5.3
*/
void tree_example_1()
{
	std :: cout << "\n ### ticket 6, example 1\n";

	Tree<std :: string> tree;

	Tree<std :: string> :: iterator it = tree.init("L0");

	it = tree.appendChild(it, "L1.1");
	it = tree.appendChild(it, "L2.1");
	tree.appendChild(it, "L3.1");       /**< leaf */
	it = tree.appendChild(it, "L3.2");
	tree.appendChild(it, "L4.1");       /**< leaf */
	tree.appendChild(it, "L4.2");       /**< leaf */
	it = it.up();
	tree.appendChild(it, "L3.3");       /**< leaf */
	it = it.up();
	tree.appendChild(it, "L2.2");       /**< leaf */

	it = it.up();
	it = tree.appendChild(it, "L1.2");
	tree.appendChild(it, "L2.3");
	tree.appendChild(tree.appendChild(it, "L2.4"), "L3.4");
	it = it.up();

	it = tree.appendChild(it, "L1.3");
	it = tree.appendChild(it, "L2.5");
	it = tree.appendChild(it, "L3.5");
	it = tree.appendChild(it, "L4.3");
	tree.appendChild(it, "L5.1");
	tree.appendChild(it, "L5.2");
	tree.appendChild(it, "L5.3");

	tree.printLevels();
}

/*
                                      L0
  ________________________________________|________________________________
  |                       |                       |                 |
L1.1____                 L1.2_________          L1.3_____         L1.4
  |     \                  |          \           |      \          |
L2.1   L2.2             L2.3        L2.4       L2.5    L2.6       L2.7
         |                            |
       L3.1                         L3.2
         |
       L4.1
*/
void tree_example_2()
{
	std :: cout << "\n### ticket 6, example 2\n";

	Tree<std :: string> tree;

	Tree<std :: string> :: iterator it = tree.init("L0");
	it = tree.appendChild(it, "L1.1");
	tree.appendChild(it, "L2.1");
	tree.appendChild(tree.appendChild(tree.appendChild(it, "L2.2"), "L3.1"), "L4.1");

	it = it.up();
	it = tree.appendChild(it, "L1.2");
	tree.appendChild(it, "L2.3");
	tree.appendChild(tree.appendChild(it, "2.4"), "L3.2");

	it = it.up();
	it = tree.appendChild(it, "L1.3");
	tree.appendChild(it, "L2.5");
	tree.appendChild(it, "L2.6");

	it = it.up();
	tree.appendChild(tree.appendChild(it, "L1.4"), "L2.7");

	tree.printLevels();
}

TICKET_FN(6)
{
	std :: cout << "#########################\n#" << ticket << ".1 - testing N-tree" << std :: endl;

	Tree<int> tree;

	std :: cout << "is empty : " << tree.isEmpty() << std :: endl;

	Tree<int> :: iterator it = tree.begin();

	std :: cout << "it == tree.end() => " << (it == tree.end())
	            << "\nit != tree.end() => " << (it != tree.end()) << std :: endl;

	it = tree.init(1);

	std :: cout << "it == tree.end() => " << (it == tree.end())
		            << "\nit != tree.end() => " << (it != tree.end()) << std :: endl;

	if (it != tree.end()) {
		std :: cout << "root = " << *it << std :: endl;
	}

	std :: cout << "postincrement root = " << *(it++) << std :: endl;

	it = tree.begin();

	std :: cout << "preincrement root is invalid = " << (++it == tree.end()) << std :: endl;

	Tree<int> :: iterator ch1 = tree.appendChild(tree.begin(), 2);

	tree.appendChild(tree.begin(), 4);

	tree.prependChild(tree.begin(), 5);

	Tree<int> :: iterator ch2 = tree.appendChild(ch1, 3);

	it = tree.begin();

	std :: cout << "1st level:";

	while (it) {
		std :: cout << " " << *(it++);
	}

	std :: cout << "\n 2d level:";

	it = tree.begin().down();

	while (it) {
		std :: cout << " " << *(it++);
	}

	std :: cout << "\n 3d level:";

	it = tree.begin().down();

	it++;

	it.down();

	while (it) {
		std :: cout << " " << *(it++);
	}

	std :: cout << "\n is 4th level exists = " << (tree.begin().down().down().down() != tree.end()) << std :: endl;

	std :: cout << "\n#########################\n#" << ticket << ".2 print by level\n";

	tree_example_1();

	tree_example_2();
}

enum class BstExample {
	E_1,
	E_2,
	E_3
};

void fillBst(BST<int> & bst, BstExample e)
{
	if (e == BstExample :: E_1) {
		bst.insert(8);
		bst.insert(3);
		bst.insert(1);
		bst.insert(6);
		bst.insert(4);
		bst.insert(7);
		bst.insert(10);
		bst.insert(14);
		bst.insert(13);
	} else if (e == BstExample :: E_2) {
		bst.insert(8);
		bst.insert(4);
		bst.insert(2);
		bst.insert(1);
		bst.insert(3);
		bst.insert(6);
		bst.insert(5);
		bst.insert(7);
		bst.insert(12);
		bst.insert(10);
		bst.insert(9);
		bst.insert(11);
		bst.insert(14);
		bst.insert(13);
		bst.insert(15);
	}
	else if (e == BstExample :: E_3) {
		bst. insert(5);
		bst.insert(3);
		bst.insert(7);
		bst.insert(2);
		bst.insert(4);
	}
}

TICKET_FN(252)
{
	cout << "#" << ticket << ": binary search tree (BST) main operation\n";

	BST<int> bst;

	BST<int>::iterator it = bst.begin();
	if (it == bst.end())
		cout << "bst is empty\n";

	it = bst.max();
	if (it == bst.end())
		cout << "no max, because bst is empty\n";

	it = bst.min();
	if (it == bst.end())
		cout << "no min, because bst is empty\n";

	it = bst.lookup(38);
	assert(it == bst.end());

	bst.insert(10);
	cout << "min = " << *bst.min() << ", max = " << *bst.max() << endl;
	bst.insert(11);
	cout << "min = " << *bst.min() << ", max = " << *bst.max() << endl;
	bst.insert(12);
	cout << "min = " << *bst.min() << ", max = " << *bst.max() << endl;
	bst.insert(7);
	cout << "min = " << *bst.min() << ", max = " << *bst.max() << endl;
	bst.insert(8);
	cout << "min = " << *bst.min() << ", max = " << *bst.max() << endl;
	bst.insert(6);
	cout << "min = " << *bst.min() << ", max = " << *bst.max() << endl;

	it = bst.begin();
	if (it != bst.end())
		cout << "bst is NOT empty: root = " << *it << endl;

	it = bst.lookup(5);
	assert(it == bst.end());
	it = bst.lookup(10);
	assert(it != bst.end());
	it = bst.lookup(13);
	assert(it == bst.end());
	it = bst.lookup(6);
	assert(it != bst.end());

	bst.clear();
	fillBst(bst, BstExample :: E_1);
	bst.printToFile("/tmp/e1");

	cout << "\nremoving tree\n";
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << endl;
	bst.remove(8);
	bst.printToFile("/tmp/r8");
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << endl;
	bst.remove(1);
	bst.printToFile("/tmp/r1");
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << endl;
	bst.remove(14);
	bst.printToFile("/tmp/r14");
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << endl;
	bst.remove(6);
	bst.printToFile("/tmp/r6");
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << endl;
	bst.remove(10);
	bst.printToFile("/tmp/r10");
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << endl;
	bst.remove(7);
	bst.printToFile("/tmp/r7");
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << endl;
	bst.remove(3);
	bst.printToFile("/tmp/r3");
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << endl;
	bst.remove(13);
	bst.printToFile("/tmp/r13");
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << endl;
	bst.remove(4);
	bst.printToFile("/tmp/r4");
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << endl;

	bst.clear();
	fillBst(bst, BstExample :: E_3);
	bst.printToFile("/tmp/src");
	it = bst.lookup(5);
	bst.rightRotation(it);
	bst.printToFile("/tmp/src_after_left_r");
	it = bst.lookup(3);
	bst.leftRotation(it);
	bst.printToFile("/tmp/src_after_right_r");

	// add some nodes and test not root rotation
	bst.insert(6);
	bst.insert(9);
	bst.insert(8);
	bst.insert(10);
	bst.printToFile("/tmp/src_plus_node");
	it = bst.lookup(7);
	bst.leftRotation(it);
	bst.printToFile("/tmp/src_plus_node_after_left");
	it = bst.lookup(9);
	bst.rightRotation(it);
	bst.printToFile("/tmp/src_plus_node_after_right");
}

TICKET_FN(263)
{
	cout << "#" << ticket << ": predessor / successor\n";

	BST<int> bst;
	BST<int> :: iterator it;

	auto test_predecessor = [&]() {
		cout << "predecessor";
		it = bst.max();
		while (it != bst.end()) {
			cout << " " << *it;
			it = bst.predecessor(it);
		}
		cout << endl;

		it = bst.min();
		it = bst.predecessor(it);
		assert(it == bst.end());
		if (it == bst.end())
			cout << "no predecessor for " << *bst.min() << endl;
	};

	auto test_successor = [&]() {
		cout << "successor:";
		it = bst.min();
		while (it != bst.end()) {
			cout << " " << *it;
			it = bst.successor(it);
		}
		cout << endl;
		it = bst.max();
		it = bst.successor(it);
		if (it == bst.end())
			cout << "no successor for " << *bst.max() << endl;
	};

	fillBst(bst, BstExample :: E_1);
	test_predecessor();
	test_successor();
	bst.clear();

	fillBst(bst, BstExample :: E_2);
	bst.printToFile("/tmp/E2");
	test_predecessor();
	test_successor();
}

TICKET_FN(96)
{
	cout << "#" << ticket << ": bst depth first search (dfs) traversal\n";

	BST<int> bst;

	fillBst(bst, BstExample :: E_1);

	cout << "In order traversal:";
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << "\n";
	cout << "Pre order traversal:";
	bst.preOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << "\n";
	cout << "Post order traversal:";
	bst.postOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << "\n";
	bst.clear();

	fillBst(bst, BstExample :: E_2);
	cout << "In order traversal:";
	bst.inOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << "\n";
	cout << "Pre order traversal:";
	bst.preOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << "\n";
	cout << "Post order traversal:";
	bst.postOrderTraversal([](int & v)->bool {cout << " " << v; return true;});
	cout << "\n";
}

TICKET_FN(255)
{
	cout << "#" << ticket << ": splay tree\n";

	SplayTree<int> splay;

	splay.insert(10);

	splay.printToFile("/tmp/splay0.txt");

	splay.insert(20);

	splay.printToFile("/tmp/splay1.txt");

	splay.insert(30);

	splay.printToFile("/tmp/splay2.txt");

	splay.insert(40);

	splay.printToFile("/tmp/splay3.txt");

	splay.insert(25);

	splay.printToFile("/tmp/splay4.txt");

	splay.insert(15);

	splay.printToFile("/tmp/splay5.txt");

	splay.insert(120);

	splay.printToFile("/tmp/splay6.txt");

	splay.remove(25);

	splay.printToFile("/tmp/splay7.txt");

	splay.remove(15);

	splay.printToFile("/tmp/splay8.txt");

	splay.remove(120);

	splay.printToFile("/tmp/splay9.txt");

	splay.remove(10);

	splay.printToFile("/tmp/splay10.txt");

	splay.insert(5);

	splay.printToFile("/tmp/splay11.txt");

	splay.remove(20);

	splay.printToFile("/tmp/splay12.txt");

	splay.remove(30);

	splay.printToFile("/tmp/splay13.txt");

	splay.remove(5);

	splay.printToFile("/tmp/splay14.txt");

	splay.remove(40);

	splay.printToFile("/tmp/splay15.txt");
}

TICKET_FN(105)
{
	cout << "#" << ticket << ": Lowest common ancestor of bst\n";

	BST<int> bst;

	BST<int> :: iterator v = bst.end(), w = bst.end();

	// e 1
	bst.insert(5);
	bst.insert(4);
	bst.insert(6);
	v = bst.lookup(4);
	w = bst.lookup(6);
	bst.printToFile("/tmp/105_e_1");
	BST<int> :: iterator res = bst.lca(v, w);
	cout << "lca (" << *v << ", " << *w << ")  = " << *res << endl;
	w = bst.lookup(5);
	res = bst.lca(v, w);
	cout << "lca (" << *v << ", " << *w << ")  = " << *res << endl;

	// e2
	bst.clear();
	bst.insert(6);
	bst.insert(3);
	bst.insert(1);
	bst.insert(2);
	bst.insert(8);
	bst.insert(7);
	bst.printToFile("/tmp/105_e_2");
	v = bst.lookup(2);
	w = bst.lookup(7);
	res = bst.lca(v, w);
	cout << "lca (" << *v << ", " << *w << ")  = " << *res << endl;

	// e3
	bst.clear();
	bst.insert(6);
	bst.insert(0);
	bst.insert(9);
	bst.insert(7);
	bst.insert(8);
	bst.insert(10);
    bst.printToFile("/tmp/105_e_3");
	v = bst.lookup(10);
	w = bst.lookup(8);
	res = bst.lca(v, w);
	cout << "lca (" << *v << ", " << *w << ")  = " << *res << endl;

	// e4
	bst.clear();
	bst.insert(6);
	bst.insert(0);
	bst.insert(11);
	bst.insert(8);
	bst.insert(7);
	bst.insert(10);
	bst.insert(9);
    bst.printToFile("/tmp/105_e_4");
	v = bst.lookup(0);
	w = bst.lookup(9);
	res = bst.lca(v, w);
	cout << "lca (" << *v << ", " << *w << ")  = " << *res << endl;

    // e5
    bst.clear();
    bst.insert(10);
    bst.insert(9);
    bst.insert(8);
    bst.insert(3);
    bst.insert(2);
    bst.insert(1);
    bst.insert(7);
	bst.insert(6);
    bst.printToFile("/tmp/105_e_5");
    v = bst.lookup(1);
    w = bst.lookup(2);
    res = bst.lca(v, w);
    cout << "lca (" << *v << ", " << *w << ")  = " << *res << endl;	

	w = bst.lookup(3);
	res = bst.lca(v, w);
	cout << "lca (" << *v << ", " << *w << ")  = " << *res << endl;

	v = bst.lookup(6);
	w = bst.lookup(3);
	res = bst.lca(v, w);
	cout << "lca (" << *v << ", " << *w << ")  = " << *res << endl;

    v = bst.lookup(2);
	w = bst.lookup(2);
	res = bst.lca(v, w);
	cout << "lca (" << *v << ", " << *w << ")  = " << *res << endl;
}

TICKET_FN(262)
{
	cout << "#"	<< ticket << ": show common element of 2 bst\n";

	BST<int> b1, b2;

	// test 1
	b1.insert(1);
	b1.printToFile("/tmp/262_1_bst1");
	b2.printToFile("/tmp/262_1_bst2");

	cout << "test1 : common elements:";
	bstCommon<int>(b1, b2, [](const int & v)->void { cout << " " << v; });
	cout << endl;

	// test 2
	b1.clear();
	b2.clear();

	b1.insert(10);
	b1.insert(3);
	b1.insert(2);
	b1.insert(9);
	b1.insert(14);
	b1.printToFile("/tmp/262_2_bst1");

	b2.insert(11);
	b2.insert(4);
	b2.insert(3);
	b2.insert(2);
	b2.insert(6);
	b2.insert(5);
	b2.insert(7);
	b2.insert(14);
	b2.printToFile("/tmp/262_2_bst2");
	cout << "test 2: common elements:";
	bstCommon<int>(b1, b2, [](const int & v)->void { cout << " " << v; });
	cout << endl;

	// test 3
	b1.clear();
	b2.clear();

	b1.insert(10);
	b1.insert(8);
	b1.insert(7);
	b1.insert(4);
	b1.insert(9);
	b1.insert(15);
	b1.insert(13);
	b1.printToFile("/tmp/262_3_bst1");

	b2.insert(11);
	b2.insert(3);
	b2.insert(1);
	b2.insert(5);
	b2.insert(16);
	b2.insert(14);
	b2.printToFile("/tmp/262_3_bst2");

    cout << "test 3: common elements:";
    bstCommon<int>(b1, b2, [](const int & v)->void { cout << " " << v; });
    cout << endl;
}

TICKET_FN(261)
{
	cout << "#" << ticket << ": maximal element in each level\n";
	
	BST<int> b;
	vector<int> v;

	// test 1
	b.insert(10);
	b.insert(1);
	b.insert(-1);
	b.insert(9);
	b.insert(-5);
	b.insert(0);
	b.insert(3);
	b.insert(25);
	b.insert(22);
	b.insert(27);
	b.insert(20);
	b.insert(23);
	b.insert(-6);
	b.printToFile("/tmp/261_1");
	b.maxInLevels(v);
	cout << "max element of tree with h = " << v.size() << endl;
	for (std :: size_t i = 0; i < v.size(); ++i) {
		cout << "max(" << i << ") = " << v[i] << endl;
	}

	// test 2
	b.clear();
	v.clear();
	b.insert(10);
	b.insert(5);
	b.insert(4);
	b.insert(6);
	b.insert(3);
	b.printToFile("/tmp/261_2");
	b.maxInLevels(v);
	cout << "max element of tree with h = " << v.size() << endl;
	for (std :: size_t i = 0; i < v.size(); ++i) {
		cout << "max(" << i << ") = " << v[i] << endl;
	}

	// test 3
	b.clear();
	v.clear();
	b.insert(10);
	b.insert(11);
	b.insert(4);
	b.insert(2);
	b.insert(6);
	b.insert(1);
	b.insert(3);
	b.insert(5);
	b.insert(5);
	b.printToFile("/tmp/261_3");
	b.maxInLevels(v);
	cout << "max element of tree with h = " << v.size() << endl;
	for (std :: size_t i = 0; i < v.size(); ++i) {
		cout << "max(" << i << ") = " << v[i] << endl;
	}

	b.clear();
	v.clear();
	fillBst(b, BstExample :: E_1);
	b.printToFile("/tmp/261_4");
	b.maxInLevels(v);
	cout << "max element of tree with h = " << v.size() << endl;
	for (std :: size_t i = 0; i < v.size(); ++i) {
		cout << "max(" << i << ") = " << v[i] << endl;
	}


}

TICKET_FN(102)
{
	cout << "#" << ticket << ": bst snake traversal\n";

	BST<int> b;

	// test 1
	b.insert(90);
	b.insert(50);
	b.insert(150);
	b.insert(20);
	b.insert(75);
	b.insert(5);
	b.insert(25);
	b.insert(66);
	b.insert(80);
	b.insert(95);
	b.insert(175);
	b.insert(92);
	b.insert(111);
	b.insert(166);
	b.insert(200);
	b.printToFile("/tmp/102_1");
	cout << "snake traversal:";
	b.snakeTraversal([](const int & v)->bool { cout << " " << v; return true; });
	cout << endl;

	// test 2
	b.clear();
	b.insert(20);
	b.insert(18);
	b.insert(16);
	b.insert(15);
	b.insert(19);
	b.insert(22);
	b.insert(21);
	b.insert(24);
	b.insert(23);
	b.insert(26);
	b.insert(25);
	b.printToFile("/tmp/102_2");
	cout << "snake traversal:";
	b.snakeTraversal([](const int & v)->bool { cout << " " << v; return true; });
	cout << endl;

	// test 3
	b.clear();
	b.insert(20);
	b.printToFile("/tmp/102_3");
	cout << "snake traversal:";
	b.snakeTraversal([](const int & v)->bool { cout << " " << v; return true; });
	cout << endl;

	// test 4
	b.clear();
	b.insert(20);
	b.insert(19);
	b.insert(18);
	b.insert(16);
	b.insert(17);
	b.printToFile("/tmp/102_4");
	cout << "snake traversal:";
	b.snakeTraversal([](const int & v)->bool { cout << " " << v; return true; });
	cout << endl;

	// test 5
	b.clear();
	b.insert(20);
	b.insert(19);
	b.insert(21);
	b.insert(22);
	b.insert(23);
	b.printToFile("/tmp/102_5");
	cout << "snake traversal:";
	b.snakeTraversal([](const int & v)->bool { cout << " " << v; return true; });
	cout << endl;


	// test 6
	b.clear();
	b.insert(20);
	b.insert(16);
	b.insert(19);
	b.insert(17);
	b.insert(25);
	b.insert(23);
	b.insert(24);
	b.printToFile("/tmp/102_6");
	cout << "snake traversal:";
	b.snakeTraversal([](const int & v)->bool { cout << " " << v; return true; });
	cout << endl;
}

TICKET_FN(39)
{
	cout << "#" << ticket << ": inner traversal iterative\n";

	BST<int> b;

	// test 1
	b.insert(10);
	b.printToFile("/tmp/39_1");
	cout << "inner traversal";
	b.inOrderTraversalI([](const int & v)->bool { cout << " " << v; return true;} );
	cout << endl;

	// test 2
	b.clear();
	b.insert(90);
	b.insert(50);
	b.insert(150);
	b.insert(20);
	b.insert(75);
	b.insert(5);
	b.insert(25);
	b.insert(66);
	b.insert(80);
	b.insert(95);
	b.insert(175);
	b.insert(92);
	b.insert(111);
	b.insert(166);
	b.insert(200);
	b.printToFile("/tmp/39_2");
	cout << "inner traversal";
	b.inOrderTraversalI([](const int & v)->bool { cout << " " << v; return true;} );
	cout << endl;

	// test 3
	b.clear();
	b.insert(10);
	b.insert(11);
	b.printToFile("/tmp/39_3");
	cout << "inner traversal";
	b.inOrderTraversalI([](const int & v)->bool { cout << " " << v; return true;} );
	cout << endl;

	// test 4
	b.clear();
	b.insert(10);
	b.insert(7);
	b.insert(6);
	b.insert(9);
	b.insert(8);
	b.insert(11);
	b.insert(16);
	b.insert(12);
	b.insert(14);
	b.insert(13);
	b.insert(15);
	b.printToFile("/tmp/39_4");
	cout << "inner traversal";
	b.inOrderTraversalI([](const int & v)->bool { cout << " " << v; return true;} );
	cout << endl;

	// test 5
	b.clear();
	b.insert(10);
	b.insert(11);
	b.insert(12);
	b.insert(14);
	b.insert(13);
	b.printToFile("/tmp/39_5");
	cout << "inner traversal";
	b.inOrderTraversalI([](const int & v)->bool { cout << " " << v; return true;} );
	cout << endl;

	// test 6
	b.clear();
	b.insert(10);
	b.insert(11);
	b.insert(9);
	b.insert(8);
	b.insert(7);
	b.printToFile("/tmp/39_6");
	cout << "inner traversal";
	b.inOrderTraversalI([](const int & v)->bool { cout << " " << v; return true;} );
	cout << endl;

	// test 7
	b.clear();
	b.insert(10);
	b.insert(6);
	b.insert(9);
	b.insert(8);
	b.insert(7);
	b.printToFile("/tmp/39_7");
	cout << "inner traversal";
	b.inOrderTraversalI([](const int & v)->bool { cout << " " << v; return true;} );
	cout << endl;
}

int main(int argc, char ** argv)
{
	ticket_39(argc, argv);

//	ticket_102(argc, argv);

//	ticket_261(argc, argv);

//	ticket_262(argc, argv);

//	ticket_105(argc, argv);

//	ticket_255(argc, argv);

//	ticket_252(argc, argv);

//	ticket_96(argc, argv);

//	ticket_263(argc, argv);

//	ticket_6(argc, argv);
}
