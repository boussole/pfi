/*
   Given a string which consists of only 0, 1 or 2s, count the number of substring which have equal number of 0s, 1s and 2s.
   Examples:
   Input  :  str = “0102010”
   Output :  2
   Explanation : Substring str[2, 4] = “102” and
                 substring str[4, 6] = “201” has
                 equal number of 0, 1 and 2

   Input : str = "102100211"
   Output : 5

   Input:
   The first line of input contains a single integer T denoting the number of test cases.
   Then T test cases follow. Each test case consists of one line. The line contains a string of 0's, 1's and 2's.

   Output:
   Corresponding to each test case, in a new line, print the count all possible substrings
   that have same number of 0s, 1s and 2s.

   Constraints:
   1 ≤ T ≤ 100
   1 ≤ string length ≤ 1000

   Example:
   Input
   2
   0102010
   102100211
   Output
   2
   5
 */

#include <iostream>
#include <string>

#include <string.h>

using namespace std;

// speed O(N^3)
// memory O(1)
size_t equal_0_1_and_2(const string &s)
{
#define ASCII_ZERO_OFFSET (48)

	size_t counter[3] = {};
	size_t nr_substrings = 0;

	// O(N) => steps = N / 3 ~ N
	for (size_t i = 3; i <= s.length(); i += 3) {
		memset(counter, 0, sizeof(counter));
		// inner loop O(N) => N - 3 + N - 6 + N - 9 = N^2

		for (size_t j = 0; j < i; ++j)
			++counter[s[j] - ASCII_ZERO_OFFSET];

		if (counter[0] == counter[1] && counter[1] == counter[2])
			++nr_substrings;

		for (size_t j = i; j < s.length(); ++j) {
			--counter[s[j - i] - ASCII_ZERO_OFFSET];
			++counter[s[j] - ASCII_ZERO_OFFSET];
			if (counter[0] == counter[1] && counter[1] == counter[2])
				++nr_substrings;
		}
	}

#undef ASCII_ZERO_OFFSET

	return nr_substrings;
}

// O(NLogN)
// http://www.geeksforgeeks.org/substring-equal-number-0-1-2/
//Let zc[i] denotes number of zeros between index 1 and i
//    oc[i] denotes number of ones between index 1 and i
//    tc[i] denotes number of twos between index 1 and i
//for substring str[i, j] to be counted in result we should have :
//	zc[i] – zc[j-1] = oc[i] – oc[j-1] = tc[i] - tc[j-1]
//we can write above relation as follows :
//z[i] – o[i] = z[j-1] – o[j-1]	and z[i] – t[i] = z[j-1] – t[j-1]
//The above relations can be tracked while looping in string, at each index i we’ll calculate this difference pair and we’ll check how many time this difference pair has previously occurred and we’ll add that count to our result, for keeping track of previous difference pair we have used map in below code. Total time complexity of this solution is O(n log n) considering the fact that map operations, like search and insert take O(Log n) time.
//// C++ program to find substring with equal
//// number of 0's, 1's and 2's
//#include <bits/stdc++.h>
//using namespace std;
//
//// Method to count number of substring which
//// has equal 0, 1 and 2
//int getSubstringWithEqual012(string str)
//{
//    int n = str.length();
//
//    // map to store, how many times a difference
//    // pair has occurred previously
//    map< pair<int, int>, int > mp;
//    mp[make_pair(0, 0)] = 1;
//
//    //  zc (Count of zeroes), oc(Count of 1s)
//    //  and tc(count of twos)
//    //  In starting all counts are zero
//    int zc = 0, oc = 0, tc = 0;
//
//    //  looping into string
//    int res = 0;  // Initialize result
//    for (int i = 0; i < n; ++i)
//    {
//        // incresing the count of current character
//        if (str[i] == '0') zc++;
//        else if (str[i] == '1') oc++;
//        else tc++;  // Assuming that string doesn't contain
//                    // other characters
//
//        // making pair of differences (z[i] - o[i],
//        // z[i] - t[i])
//        pair<int, int> tmp = make_pair(zc - oc,
//                                       zc - tc);
//
//        // Count of previous occurrences of above pair
//        // indicates that the subarrays forming from
//        // every previous occurrence to this occurrence
//        // is a subarray with equal number of 0's, 1's
//        // and 2's
//        res = res + mp[tmp];
//
//        // increasing the count of current difference
//        // pair by 1
//        mp[tmp]++;
//    }
//
//    return res;
//}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		string s;
		cin >> s;
		cout << equal_0_1_and_2(s) << endl;
	}

	return 0;
}

