/*
   An array of buildings is facing the sun.
   The heights of the building is given in an array.
   You have to tell which all buildings will see the sunset.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   The first line of each test case is N,N is the number of buildings.
   The second line of each test case contains N input H[i],height of building.

   Output:
   Print the total number of buildings which will see the sunset.

   Constraints:
   1 ≤ T ≤ 100
   1 ≤ N ≤ 500
   1 ≤ H[i] ≤ 1000

   Example:
      Input:
      2
      5
      7 4 8 2 9
      4
      2 3 4 5
      Output:
      3
      4
 */

#include <iostream>
#include <memory>

using namespace std;

// speed O(N)
// memory O(1)
int facing_the_sun(const unique_ptr<int[]> &arr, int arr_sz)
{
	int nr_buildings = 1, highest_building = arr[0];

	for (int i = 1; i < arr_sz; ++i) {
		if (arr[i] > highest_building) {
			highest_building = arr[i];
			++nr_buildings;
		}
	}

	return nr_buildings;
}

int main()
{
	int nr_tests;
	cin >> nr_tests;

	while (nr_tests--) {
		int arr_sz;
		cin >> arr_sz;

		unique_ptr<int[]> arr(new int[arr_sz]);
		for (int i = 0; i < arr_sz; ++i)
			cin >> arr[i];

		cout << facing_the_sun(arr, arr_sz) << endl;
	}

	return 0;
}

