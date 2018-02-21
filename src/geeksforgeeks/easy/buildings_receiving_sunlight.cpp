/*
Given are the heights of certain Buildings which lie adjacent to each other. Sunlight starts falling from left side of the buildings. If there is a building of certain Height, all the buildings to the right side of it having lesser heights cannot see the sun . The task is to find the total number of such buildings that receive sunlight.
Input:
First Line of input contains an integer T denoting the number of test cases. Then T test cases follow. Each test case consists of two lines. First line of each test case contains an integer N denoting the number of buildings. Second line contains N space separated integers H1, H2,...HN denoting heights of buildings.

Output:
Corresponding to each test case, print the desired output in a new line

Constraints:
1<=T<=100
1<=N<=100
1<=Hi<=100

Example:
Input:
3
6
6 2 8 4 11 13
5
2 5 1 8 3
7
3 4 1 0 6 2 3

Output:
4
3
3

Explanation:
In the first example only buildings of height 6 8 11 and 13 can see the sun, hence output is 4.
 */

#include <vector>
#include <iostream>

using namespace std;

int nr_buildings_receiving_sunlight(const vector<int> &arr)
{
	int ans = 1;
	int building_max = arr[0];
	for (size_t i = 1; i < arr.size(); ++i) {
		if (arr[i] >= building_max) {
			building_max = arr[i];
			++ans;
		}
	}

	return ans;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		vector<int> arr(arr_sz);
		for (int i = 0; i < arr_sz; ++i) {
			cin >> arr[i];
		}

		cout << nr_buildings_receiving_sunlight(arr) << endl;
	}

	return 0;
}


