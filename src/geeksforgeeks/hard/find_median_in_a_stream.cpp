/*
Given an input stream of n integers the task is to insert integers to stream and print the median of the new stream formed by each insertion of x to the stream.

Example

Flow in stream : 5, 15, 1, 3
5 goes to stream --> median 5 (5)
15 goes to stream --> median 10 (5, 15)
1 goes to stream --> median 5 (5, 15, 1)
3 goes to stream --> median 4 (5, 15, 1, 3)

Input:
The first line of input contains an integer N denoting the no of elements of the stream. Then the next N lines contains integer x denoting the no to be inserted to the stream.

Output:
For each element added to the stream print the floor of the new median in a new line.

Constraints:
1<=N<=10^5+7
1<=x<=10^5+7

Example:
Input:
4
5
15
1
3
Output:
5
10
5
4
 */

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

static vector<int> to_median, from_median;

void find_median_in_a_stream(int val)
{
	// the first in a stream
	if (to_median.empty() && from_median.empty()) {
		to_median.push_back(val);
		cout << val << endl;
		return;
	}

	if (val < to_median.front()) {
		to_median.push_back(val);
		push_heap(to_median.begin(), to_median.end());
	} else {
		from_median.push_back(val);
		push_heap(from_median.begin(), from_median.end(), greater<int>());
	}

	if (to_median.size() > from_median.size() + 1) {
		from_median.push_back(to_median.front()); push_heap(from_median.begin(), from_median.end(), greater<int>());
		pop_heap(to_median.begin(),to_median.end()); to_median.pop_back();
	} else if (from_median.size() > to_median.size() + 1) {
		to_median.push_back(from_median.front()); push_heap(to_median.begin(), to_median.end());
		pop_heap(from_median.begin(),from_median.end(), greater<int>()); from_median.pop_back();
	}

	if ((to_median.size() + from_median.size()) % 2 == 0) {
		cout << ((to_median.front() + from_median.front()) / 2) << endl;
	} else {
		cout << (to_median.size() > from_median.size() ? to_median.front() : from_median.front()) << endl;
	}
}

int main()
{
	int arr_sz;
	cin >> arr_sz;
	while (arr_sz--) {
		int val;
		cin >> val;
		find_median_in_a_stream(val);
	}

	return 0;
}
