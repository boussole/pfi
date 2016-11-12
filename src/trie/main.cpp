/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include "trie.h"
#include "radix_trie.h"

using namespace conq_trie;
using namespace std;
using namespace boost;

/*******************************************************
 * Not compressed trie
 *******************************************************/
TICKET_FN(247)
{
	cout << "#" << ticket << ": trie\n";
#if 1
	Trie<char, int, StringTrieKey> trie;

	pair<string, int> test[] = {
		{"tra", 0},
		{"opa", 1},
		{"t", 2},
		{"", 3},
		{"to", 4},
		{"tea", 5},
		{"ted", 6},
		{"ten", 7},
		{"in", 8},
		{"i", 9},
		{"innn", 10},
		{"ina", 11}
	};

	cout << __PRETTY_FUNCTION__ << ": fill trie\n";

	for (std :: size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++)
		trie.insert(test[i].first, test[i].second);

	trie.print();

	cout << __PRETTY_FUNCTION__ << ": lookup\n";

	int value;
	BOOST_ASSERT(trie.lookup("sdf", value) == false);

	for (std :: size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++) {
		bool res = trie.lookup(test[i].first, value);
		BOOST_ASSERT(res && (test[i].second == value));
	}

	int remove_idx[] = { 0, 6, 9, 11, 10, 2, 3, 4, 5, 7, 8, 1};

	cout << __PRETTY_FUNCTION__ << ": remove\n";

	cout << "remove key = \"sometest\"\n";
	BOOST_ASSERT(trie.remove("sometest") == false);

	for (std :: size_t i = 0; i < sizeof(remove_idx)/sizeof(remove_idx[0]); ++i) {
		cout << "remove key = \"" << test[remove_idx[i]].first << "\"\n";
		BOOST_ASSERT(trie.remove(test[remove_idx[i]].first) == true);
		trie.print();
	}

#else
	Trie<int, std :: string, ByteTrieKey> trie;

	pair<int, std :: string> test[] = {
		{2130706433, "127.0.0.1"},
		{167772161, "10.0.0.1"},
		{167772162, "10.0.0.2"},
		{167842819, "10.1.20.3"},
		{0, "0.0.0.0"},
		{167908355, "10.2.20.3"},
		{167908356, "10.2.20.4"}
	};

	cout << __PRETTY_FUNCTION__ << ": fill trie\n";

	for (std :: size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++)
		trie.insert(test[i].first, test[i].second);

	trie.print();

	cout << __PRETTY_FUNCTION__ << ": lookup\n";

	string value;
	BOOST_ASSERT(trie.lookup(2346788, value) == false);

	for (std :: size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++) {
		bool res = trie.lookup(test[i].first, value);
		BOOST_ASSERT(res && (test[i].second == value));
	}

	cout << __PRETTY_FUNCTION__ << ": remove\n";

	cout << "remove key = \"23472983\"\n";
	BOOST_ASSERT(trie.remove(23472983) == false);

	for (std :: size_t i = 0; i < sizeof(test)/sizeof(test[0]); ++i) {
		cout << "remove key = \"" << test[i].first << "\"\n";
		BOOST_ASSERT(trie.remove(test[i].first) == true);
		trie.print();
	}
#endif

}

/*******************************************************
 * Compressed trie (patricia trie)
 *******************************************************/
TICKET_FN(248)
{
	cout << "#" << ticket << ": radix trie (patricia)\n";

	pair<string, int> test[] = {
		{ "romane", 0},
		{ "romanus", 1},
		{ "romulus", 2},
		{ "rubens", 3},
		{ "ruber", 4},
		{ "rubicon", 5},
		{ "rubicundus", 6}
	};

//	pair<string, int> test[] = {
//		{ "romanus", 0},
//		{ "romantic", 1},
//		{ "roman", 2},
//		{ "rock", 3},
//		{ "romantica", 4},
//		{ "slot", 5},
//		{ "slowly", 6},
//		{ "slowle", 7 }
//	};

	RadixTrie<int> r;

	cout << __PRETTY_FUNCTION__ << ": fill trie\n";

	for (std :: size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++) {
		cout << "add key = \"" << test[i].first << "\" value = \"" << test[i].second << "\"\n";
		r.insert(test[i].first, test[i].second);
	}

	r.print();

	cout << std :: endl << __PRETTY_FUNCTION__ << ": lookup trie\n";
	int value;
	BOOST_ASSERT(r.lookup("some test", value) == false);

	for (std :: size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++) {
		cout << "lookup key = \"" << test[i].first << "\" with value = \"" << test[i].second << "\"\n";
		BOOST_ASSERT(r.lookup(test[i].first, value));
		BOOST_ASSERT(test[i].second == value);
	}

	cout << std :: endl << __PRETTY_FUNCTION__ << ": erase trie\n";
	BOOST_ASSERT(r.remove("any key") == false);

	for (std :: size_t i = 0; i < sizeof(test)/sizeof(test[0]); i++) {
		cout << "remove key = \"" << test[i].first << "\" with value = \"" << test[i].second << "\"\n";
		BOOST_ASSERT(r.remove(test[i].first));
		r.print();
	}

	r.print();

//	test 3
//	r.insert("124", 124);
//	r.print();
//
//	r.insert("135", 135);
//	r.print();
//
//	r.insert("136", 136);
//	r.print();
//
//	r.insert("1367", 1367);
//	r.print();
//
//	r.remove("136");
//	r.print();
//
//	r.remove("135");
//	r.print();
//
//	r.remove("124");
//	r.print();
//
//	r.remove("1367");
//	r.print();

//	test 4
//	r.insert("111", 111);
//	r.insert("1", 1);
//	r.insert("112", 112);
//	r.insert("11", 11);
//	r.print();
//
//	r.remove("11");
//	r.print();
//
//	r.remove("112");
//	r.print();
//
//	r.remove("111");
//	r.print();
//
//	r.remove("1");
//	r.print();

//	test 5
//	r.insert("12", 12);
//	r.print();
//
//	r.insert("123", 123);
//	r.print();
//
//	r.insert("15", 15);
//	r.print();
//
//	r.insert("1567", 1567);
//	r.print();
//
//	r.insert("1568", 1568);
//	r.print();
//
//	r.remove("15");
//	r.print();
//
//	r.remove("123");
//	r.print();
//
//	r.remove("12");
//	r.print();
//
//	r.remove("1567");
//	r.print();
//
//	r.remove("1568");
//	r.print();

//	test 6
//	r.insert("0", 0);
//	r.print();
//
//	r.insert("01", 1);
//	r.print();
//
//	r.insert("012", 12);
//	r.print();
//
//	r.insert("013", 13);
//	r.print();

//	test 6
//	r.insert("1234", 1234);
//	r.print();
//
//	r.insert("12345", 12345);
//	r.print();
}

int main(int argc, char * argv[])
{
	/* uncomment one of the ticket function */

//	ticket_248(argc, argv);

//	ticket_247(argc, argv);

	return 0;
}
