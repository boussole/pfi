/*
Given a collection of Intervals,merge all the overlapping Intervals.
For example:

Given [1,3], [2,6], [8,10], [15,18],

return [1,6], [8,10], [15,18].

Make sure the returned intervals are sorted.

Input:

The first line contains an integer T, depicting total number of test cases.
Then following T lines contains an integer N depicting the number of Intervals and next line followed by the intervals starting and ending positions 'x' and 'y' respectively.

Output:
Print the intervals after overlapping in sorted manner.  There should be a newline at the end of output of every test case.

Constraints:
1 ≤ T ≤ 50
1 ≤ N ≤ 100
0 ≤ x ≤ y ≤ 100


Example:
Input
2
4
1 3 2 4 6 8 9 10
4
6 8 1 9 2 4 4 7

Output
1 4 6 8 9 10
1 9
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void merge_overlapping_intervals(vector<pair<int, int> > &intervals, vector<pair<int, int> > &merged)
{
	merged.resize(intervals.size());
	sort(intervals.begin(), intervals.end(), [](const pair<int,int> &l, const pair<int,int> &r) {
		return l.first < r.first;
	});

	size_t real_size = 1;
	merged[0] = intervals[0];
	for (size_t i = 1; i < intervals.size(); ++i) {
		if (merged[real_size - 1].second < intervals[i].first) {
			merged[real_size++] = intervals[i];
		} else if (merged[real_size - 1].second == intervals[i].first ||
		           merged[real_size - 1].second < intervals[i].second)
		{
			merged[real_size - 1].second = intervals[i].second;
		}
	}

	merged.resize(real_size);
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int nr_pairs;
		cin >> nr_pairs;
		vector< pair<int, int> > intervals(nr_pairs);
		for (int i = 0; i < nr_pairs; ++i) {
			pair<int, int> interval;
			cin >> interval.first >> interval.second;
			intervals[i] = interval;
		}

		vector<pair<int, int> > merged;
		merge_overlapping_intervals(intervals, merged);
		for (size_t i = 0; i < merged.size(); ++i) {
			cout << merged[i].first << " " << merged[i].second << " ";
		}
		cout << endl;
	}

	return 0;
}
