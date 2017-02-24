/*
   Given the start time and end time of a race in the format hh:mm:ss. You task is to print the time taken to complete the race.

   Input :
   The first line of input contains an integer T, denoting number of test case.
   Then T test cases follow.
   The first line of each test case contains string s, denoting the start time of the race.
   The second line of each test case contains a string e, denoting the end time of the race.

   Output :
   For each test case in a new line print the time taken to complete the race in the format hh:mm:ss.

   Constraints :
   1<=T<=100
   0<=hh<=23
   0<=mm<=59
   0<=ss<=59
   start time<=end time

   Example:
      Input :
      2
      13:50:45
      14:55:50
      12:00:00
      24:00:00

      Output:
      01:05:05
      12:00:00
 */

#include <assert.h>

#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

struct race_time {
	race_time()
	{}

	race_time(const string &s)
	{
		size_t pos = s.find(":");
		assert(pos != string :: npos);
		string t = s.substr(0, pos);
		_times[0] = stoi(t);

		pos = s.find(":", pos + 1);
		assert(pos != string :: npos);
		t = s.substr(t.length() + 1, pos - t.length() - 1);
		_times[1] = stoi(t);

		assert(s.find(":", pos + 1) == string :: npos);
		t = s.substr(pos + 1);
		_times[2] = stoi(t);
	}

	race_time operator-(race_time &rhs) {
		race_time result;

		for (int i = 2; i >= 0; --i) {
			if (_times[i] < rhs._times[i]) {
				// descrease one of the higher measure
				for (int j = i - 1; j >= 0; --j) {
					if (_times[j] > 0) {
						--_times[j];
						break;
					}
					// `rhs` is larger than `this`
					assert(j == 0);
				}

				result._times[i] = _times[i] + 60 - rhs._times[i];
			} else
				result._times[i] = _times[i] - rhs._times[i];
		}

		return result;
	}

	uint32_t _times[3];
};

ostream &operator<<(ostream &o, race_time &rt)
{
	o << setfill('0') << setw(2) << rt._times[0] << ":" << setfill('0') << setw(2) << rt._times[1] << ":" << setfill('0') << setw(2) << rt._times[2];

	return o;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s, e;
		cin >> s >> e;

		race_time start_time(s), end_time(e), diff = end_time - start_time;
		cout << diff << endl;
	}

	return 0;
}
