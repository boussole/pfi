/*
   Given a string s consisting of lowercase Latin Letters, find the first non repeating character in s.

   Input:
   The first line contains T denoting the number of testcases. Then follows description of testcases.
   Each case begins with a single integer N denoting the length of string. The next line contains the string s.

   Output:
   For each testcase, print the first non repeating character present in string.
   Print -1 if there is no non repeating character.

   Constraints:
   1<=T<=30
   1<=N<=100

   Example:
      Input:
      3
      5
      hello
      12
      zxvczbtxyzvy
      6
      xxyyzz

      Output :
      h
      c
      -1

   **For More Examples Use Expected Output**
 */

#include <assert.h>
#include <string.h>

#include <iostream>
#include <memory>
#include <string>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 30;

static const size_t MinStringLen = 1;
static const size_t MaxStringLen = 100;

#define code_of_a 97
#define code_of_z 122

// speed O(N)
// memory O(N + MAP)
char first_non_repeating_character_v1(string &s, int len)
{
	char ch = '\0';

	int sym_map[code_of_z - code_of_a + 1] = { 0 };

	for (int i = 0; i < len; ++i)
		++sym_map[s[i] - code_of_a];

	for (int i = 0; i < len; ++i) {
		if (sym_map[s[i] - code_of_a] == 1)
			return s[i];
	}

	return ch;
}

// speed O(N)
// memory O(N + MAP)
// \note in one pass
//
// use each map item as double linked list pointers, via index's
char first_non_repeating_character_v2(string &s, int len)
{
	struct link_list {
		uint8_t prev, next;

		uint32_t visited : 1;
	};

	char ch = '\0';

	link_list map[code_of_z - code_of_a + 1] = { 0 };
	int begin = -1, end = -1;

	for (int i = 0; i < len; ++i) {
		uint32_t pos = s[i] - code_of_a;

		if (!map[pos].visited) {
			map[pos].visited = 1;

			if (begin == -1) {
				begin = pos;
				map[pos].prev = pos;
			} else {
				map[end].next = pos;
				map[pos].prev = end;
			}

			map[pos].next = pos;
			end = pos;
		} else {
			if (map[pos].next == map[pos].prev) {
				if (begin == pos)
					begin = end = -1;
			} else {
				if (begin == pos)
					begin = map[pos].next;
				else if (end == pos)
					end = map[pos].prev;
				else {
					map[map[pos].prev].next = map[pos].next;
					map[map[pos].next].prev = map[pos].prev;
				}
			}

			map[pos].next = map[pos].prev;
		}
	}

	return begin != -1 ? begin + code_of_a : '\0';
}

/*
And one more solution, it is also doesn't need the second pass full string to find the first unique element, but it needs extra pass through counting map
`
   http://www.geeksforgeeks.org/given-a-string-find-its-first-non-repeating-character/

   Can we do it by traversing the string only once?
   The above approach takes O(n) time, but in practice it can be improved.
   The first part of the algorithm runs through the string to construct the count array (in O(n) time).
   This is reasonable. But the second part about running through the string again just to find the first non-repeater is not good in practice.
   In real situations, your string is expected to be much larger than your alphabet.
   Take DNA sequences for example: they could be millions of letters long with an alphabet of just 4 letters.
   What happens if the non-repeater is at the end of the string? Then we would have to scan for a long time (again).
   We can augment the count array by storing not just counts but also the index of the first time you encountered the character e.g. (3, 26)
   for ‘a’ meaning that ‘a’ got counted 3 times and the first time it was seen is at position 26.
   So when it comes to finding the first non-repeater, we just have to scan the count array, instead of the string.
`
*/
char first_non_repeating_character_v3(string &s, int len);

int main()
{
	int nr_tests = 0;
	cin >> nr_tests;

	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints error: 1 <= T <= 30\n";
		return 1;
	}

	while (nr_tests--) {
		int len;
		cin >> len;
		if (len < MinStringLen || len > MaxStringLen) {
			cerr << "constraints error: 1 <= T <= 100\n";
			return 1;
		}

		string s;
		cin >> s;

		char ans_1 = first_non_repeating_character_v1(s, len), ans_2 = first_non_repeating_character_v2(s, len);

		assert(ans_1 == ans_2);

		cout << (ans_1 ? string(1, ans_1) : "-1") << endl;
	}

	return 0;
}



