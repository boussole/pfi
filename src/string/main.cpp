/**********************************************************
 * \file main.cpp
 *
 * \author boussole
 **********************************************************/

#include "string.h"

using namespace std;
using namespace conq_string;

/***********************************************************
 * \brief Bracket symmetry check
 ***********************************************************/
TICKET_FN(87)
{
	cout << "#" << ticket << endl;

	if (argc < 2) {
		cout << "usage: " << *argv << " \"string\"" << endl;
		return;
	}

	int len = strlen(argv[1]);

	int pos = checkBracketSymmetry(argv[1], len);

	if (pos == len)
		cout << "brackets are correct" << endl;
	else {
		cout << "invalid bracket at " << pos << endl;
		cout << argv[1] << endl;
		while (pos--) {
			cout << ' ';
		}
		cout << '^' << endl;
	}
}

/***********************************************************
 * \brief #38: Find largest reoccuring sequence
 **********************************************************/
TICKET_FN(38)
{
	cout << "#" << ticket << endl;

	if (argc < 2) {
		cout << "usage: " << *argv << " <string>\n";
		return;
	}

	cout << "input: " << "\"" << argv[1] << "\"\n";

	string s(argv[1]);

	cout << "res = " << findLargestReoccuringCharacter(s.c_str(), s.length()) << endl;
}

/***********************************************************
 * \brief #88: Minimal distance between two chars
 **********************************************************/
TICKET_FN(88)
{
	cout << "#" << ticket << endl;

	if (argc < 4) {
		cout << "usage: " << *argv << " <string> <left symbol> <right symbol>" << endl;
		return;
	}

	if ((strnlen(argv[2], 3) > 1) || (strnlen(argv[3], 3) > 1)) {
		cout << "left, right symbol should be acsii char\n";
		return;
	}

	int res = findMinDistance(argv[1], strlen(argv[1]), argv[2][0], argv[3][0]);

	if (res < 0) {
		cout << "distance doesn't exist" << endl;
	} else {
		cout << "minimal distance between \"" << argv[2][0] << "\" and \"" << argv[3][0] << "\" = " << res << endl;
	}
}

/***********************************************************
 * \brief #301: Naive search of substring
 ***********************************************************/
TICKET_FN(301)
{
	cout << "#" << ticket << ": Naive search of substring\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <haystack> <needle>\n";
		return;
	}

	const char * haystack = argv[1], * needle = argv[2];
	int h_sz = strlen(haystack), n_sz = strlen(needle);

	cout << "haystack = \"" << haystack << "\"; needle = \"" << needle << "\"." << endl;

	int res = findSubString_Naive(haystack, h_sz, needle, n_sz);
	int offset = 0;
	while (res != -1) {
		offset += res;
		cout << "pos = " << offset << endl;
		offset += n_sz;
		res = findSubString_Naive(&haystack[offset], h_sz - offset, needle, n_sz);
	}
}

/***********************************************************
 * \brief #301: Rabin-Karp search of substring
 ***********************************************************/
TICKET_FN(302)
{
	cout << "#" << ticket << ": Rabin-Karp search of substring\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <haystack> <needle>\n";
		return;
	}

	const char * haystack = argv[1], * needle = argv[2];
	int h_sz = strlen(haystack), n_sz = strlen(needle);

	cout << "haystack = \"" << haystack << "\"; needle = \"" << needle << "\"." << endl;
	int res = findSubString_RK(haystack, h_sz, needle, n_sz);
	assert(res == findSubString_Naive(haystack, h_sz, needle, n_sz));
	int offset = 0;
	while (res != -1) {
		offset += res;
		cout << "pos = " << offset << endl;
		offset += n_sz;
		res = findSubString_RK(&haystack[offset], h_sz - offset, needle, n_sz);
		assert(res == findSubString_Naive(&haystack[offset], h_sz - offset, needle, n_sz));
	}
}

/**********************************************************
 * \brief #89: Revert UTF-8 string
 **********************************************************/
TICKET_FN(89)
{
	cout << "#" << ticket << ": revert UTF-8 string\n";

	if (argc != 2) {
		//usage(*argv);
		cout << "usage: " << *argv << " \"<string>\"\n";
		return;
	}

	std :: cout << "src: " << argv[1] << std :: endl;

	if (!revertUtf8(argv[1], strlen(argv[1]))) {
		std :: cerr << "invalid utf8 string" << std :: endl; /** or throw */
		return;
	}

	std :: cout << "dst: " << argv[1] << std :: endl;
}

/***********************************************************
 * \brief #108: Longest common substring
 ***********************************************************/
TICKET_FN(108)
{
	cout << "#" << ticket << ": longest common substring\n";

	if (argc != 3) {
		cout << "usage: " << *argv << " \"<string1>\" \"<string2>\"\n";
		return;
	}

	list < pair<int, int> > lcs;

	string s1 = argv[1], s2 = argv[2];

	int lcsuff = lcSuff(s1, s2, lcs);

	if (lcsuff > 0)
		for (auto i : lcs)
			cout << s1.substr(i.first, i.second) << endl;
	else
		cout << "longest common substring has not been found\n";
}

/***********************************************************
 * \brief #119 Edit distance
 ***********************************************************/
TICKET_FN(119)
{
	cout << "#" << ticket << ": edit distance problem\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " \"<src string>\" \"<dst string>\"\n";
		return;
	}

	string src = argv[1], dst = argv[2];

	cout << "edit distance = " << editDistance(src, dst) << endl;
}

/**************************************************************
 * \brief #303 Knuth–Morris–Pratt search of substring
 **************************************************************/
TICKET_FN(303)
{
	cout << "#" << ticket << ": Knuth Morris Pratt search of substring\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <haystack> <needle>\n";
		return;
	}

	const char * haystack = argv[1], * needle = argv[2];
	int h_sz = strlen(haystack), n_sz = strlen(needle);

	cout << "haystack = \"" << haystack << "\"; needle = \"" << needle << "\"." << endl;
	int res = findSubString_KMP(haystack, h_sz, needle, n_sz);
	assert(res == findSubString_Naive(haystack, h_sz, needle, n_sz));
	int offset = 0;
	while (res != -1) {
		offset += res;
		cout << "pos = " << offset << endl;
		offset += n_sz;
		res = findSubString_KMP(&haystack[offset], h_sz - offset, needle, n_sz);
		assert(res == findSubString_Naive(&haystack[offset], h_sz - offset, needle, n_sz));
	}
}

TICKET_FN(101)
{
	cout << "#" << ticket << ": name of Kth excel column\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <kth column number>\n";
		return;
	}

	int k = atoi(argv[1]);
	if (k <= 0) {
		cout << "invalid k\n";
		return;
	}

	cout << "column №" << k << " name is \"" << kthExcelColumnName(k) << "\"\n";
}

TICKET_FN(280)
{
	cout << "#" << ticket << ": parse text tree\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <string>\n";
		return;
	}

	string s = argv[1];

	TextTreeParser parser(s);

	parser.print();
}

TICKET_FN(332)
{
	cout << "#" << ticket << ": parentheses problem\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <string>\n";
		return;
	}

	string s(argv[1]);

	cout << "input (length = " << s.length() << "): " << "\"" << s << "\"" << endl;

	balance_parentheses(s);

	cout << "output (length = " << s.length() << "): " << "\"" << s << "\"" << endl;
}

int main(int argc, char ** argv)
{
	/* uncomment one of them */

	// ticket_332(argc, argv);

	// ticket_280(argc, argv);

	// ticket_101(argc, argv);

	// ticket_303(argc, argv);

	// ticket_119(argc, argv);

	// ticket_108(argc, argv);

	// ticket_302(argc, argv);

	// ticket_89(argc, argv);

	// ticket_301(argc, argv);

	// ticket_87(argc, argv);

	// ticket_38(argc, argv);

	// ticket_88(argc, argv);

	// FindFirstUniqueSym algo;

	// RevertWordsInString algo;

	// UniqStringPrint algo;

	// RevertString algo;

	// algo.doTask(argc, argv);

	return 0;
}
