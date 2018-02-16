/*
Return true or false depending on whether input array 'words' is sorted in increasing order according to the character ordering 'ordering'.

Input:
  words = ['cc', 'cb', 'bb', 'bbc', 'ac']
  ordering = ['c', 'b', 'a']
  Output: True

Input:
  words = ['cc', 'cb', 'bbc', 'bb', 'ac']
  ordering = ['c', 'b', 'a']
  Output: False

Input:
  words = ['cc', 'cb', 'bb', 'ac']
  ordering = ['b', 'c', 'a']
  Output: False
 */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

bool is_left_less_or_equel_than_right(string &l, string &r, unordered_map<char, int> &order)
{
	size_t i = 0, j = 0;
	while (i < l.size() && j < r.size()) {
		if (order[l[i]] < order[r[j]])
			return true;
		else if (order[l[i]] > order[r[j]])
			return false;
		++i;
		++j;
	}

	return l.size() <= r.size();
}

bool is_sorted_in_specific_order(vector<string> &v, vector<char> &o)
{
	unordered_map<char, int> order;
	for (size_t i = 0; i < o.size(); ++i) {
		order.insert(make_pair(o[i], i));
	}

	for (size_t i = 1; i < v.size(); ++i) {
		if (!is_left_less_or_equel_than_right(v[i - 1], v[i], order)) {
			return false;
		}
	}

	return true;
}

int main()
{
	vector<string> v1{"cc", "cb", "bb", "bbc", "ac"};
	vector<char> o1{'c', 'b', 'a'};
	cout << is_sorted_in_specific_order(v1, o1) << endl;

	vector<string> v2{"cc", "cb", "bbc", "bb", "ac"};
	vector<char> o2{'c', 'b', 'a'};
	cout << is_sorted_in_specific_order(v2, o2) << endl;

	vector<string> v3{"cc", "cb", "bb", "ac"};
	vector<char> o3{'b', 'c', 'a'};
	cout << is_sorted_in_specific_order(v3, o3) << endl;

	return 0;
}
