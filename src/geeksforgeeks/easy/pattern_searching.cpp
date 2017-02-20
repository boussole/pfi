/*
   Given a text and a pattern, Find whether the pattern exist in the text or not.
   If it is present print "found" without quotes else print "not found" without quotes.

   Input:
   The first line of input contains an integer T denoting the number of test cases.
   Each test case consist of a string in 'lowercase' only in a separate line.

   Output:
   Print "found" or "not found" in a separate line.

   Constraints:
   1 ≤ T ≤ 30
   1 ≤ |s| ≤ 100

   Example:
      Input
      1
      geeksforgeeks
      geeks

      Output
      found
      **For More Examples Use Expected Output**
 */

#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

#define MIN_STRING_LEN (1)
#define MAX_STRING_LEN (100)

// speed = O(N * M)
// memory = O(1)
bool pattern_searching_naive(const string &haystack, const string &needle)
{
	if (haystack.length() < needle.length())
		return false;

// nop by constraints
#if (MIN_STRING_LEN < 1)
	if (haystack.length() == 0 && needle.length() == 0)
		return true;

	if (haystack.length() == 0 || needle.length() == 0)
		return false;
#endif

	size_t h_max = haystack.length() - needle.length() + 1;
	for (size_t h = 0; h < h_max; ++h) {
		size_t n = 0, h_cmp = h;
		while (haystack[h_cmp] == needle[n]) {
			++h_cmp;
			++n;
			if (n == needle.length())
				return true;
		}
	}

	return false;
}

// using power of 2
class rabin_karp_hash {
public:
	rabin_karp_hash() = delete;

	// make hash and save it
	rabin_karp_hash(const string &str, size_t length) : _value(0)
		{   make_hash(str.c_str(), length);   }

	// make hash and save it
	rabin_karp_hash(const string &str) : _value(0)
		{   make_hash(str.c_str(), str.length());   }

	~rabin_karp_hash()
		{}

	void make_hash(const char *str, size_t length)
	{
		assert(length > 0);

		uint64_t power = _power_max = length - 1;

		for (size_t i = 0; i < length; ++i)
			_value += str[i] * (1 << power--);
	}

	uint64_t value()
		{   return _value;   }

	void update(char del, char add)
		{   _value = ((_value - (del * (1 << _power_max))) << 1) + add;   }

private:

	uint64_t _value;

	uint64_t _power_max;
};

// avg speed = O(N), worst speed = O(N * M)
// memory = O(M)
bool pattern_searching_rabin_karp(const string &haystack, const string &needle)
{
	if (haystack.length() < needle.length())
		return false;

	// nop by constraints
	#if (MIN_STRING_LEN < 1)
		if (haystack.length() == 0 && needle.length() == 0)
			return true;

		if (haystack.length() == 0 || needle.length() == 0)
			return false;
	#endif

	rabin_karp_hash haystack_hash(haystack, needle.length()), needle_hash(needle);

	size_t h_max = haystack.length() - needle.length() + 1;

	for (size_t h = 0; h < h_max; ++h) {
		// fast path
		if (haystack_hash.value() == needle_hash.value()) {
			// slow path
			if (haystack.compare(h, needle.length(), needle) == 0)
				return true;
		}

		haystack_hash.update(haystack[h], haystack[h + needle.length()]);
	}

	return false;
}

class knuth_morris_pratt {
public:
	knuth_morris_pratt(const string &needle) : _needle(needle)
	{
		make_prefix_fn();
	}

	// speed O(M)
	// memory O(1)
	bool find_in(const string &haystack)
	{
		size_t needle_pos = 0;
		for (size_t i = 0; i < haystack.length(); ++i) {
			while (haystack[i] != _needle[needle_pos] && needle_pos)
				needle_pos = _pref_fn[needle_pos - 1];
		
			if (haystack[i] == _needle[needle_pos])
				++needle_pos;

			if (needle_pos == _needle.length())
				return true;
		}

		return false;
	}

protected:
	// speed O(N)
	// memory O(N)
	void make_prefix_fn()
	{
		assert(_needle.length() != 0);

		_pref_fn.reset(new int[_needle.length()]);

		_pref_fn[0] = 0;

		int pref_pos = 0;
		for (size_t i = 1; i < _needle.length(); ++i) {
			while (pref_pos != 0 && _needle[pref_pos] != _needle[i]) {
				pref_pos = _pref_fn[pref_pos - 1];
			}

			if (_needle[pref_pos] == _needle[i])
				++pref_pos;
			
			_pref_fn[i] = pref_pos;
		}
	}

private:
	string _needle;
	unique_ptr<int[]> _pref_fn;
};

// speed O(N + M)
// memory O(1)
bool pattern_searching_knuth_morris_pratt(const string &haystack, const string &needle)
{
	knuth_morris_pratt kmp(needle);

	return kmp.find_in(haystack);
}

int main()
{
	int nr_tests = 0;
	cin >> nr_tests;

	while (nr_tests--) {
		string haystack, needle;

		cin >> haystack;
		if (haystack.length() < MIN_STRING_LEN || haystack.length() > MAX_STRING_LEN) {
			cerr << "constraints error: 1 ≤ |s| ≤ 100\n";
			return 1;
		}

		cin >> needle;
		if (needle.length() < MIN_STRING_LEN || needle.length() > MAX_STRING_LEN) {
			cerr << "constraints error: 1 ≤ |s| ≤ 100\n";
			return 1;
		}

		cerr << haystack << " " << needle << endl;

		bool ans_1 = pattern_searching_naive(haystack, needle);
		bool ans_2 = pattern_searching_rabin_karp(haystack, needle);
		bool ans_3 = pattern_searching_knuth_morris_pratt(haystack, needle);
		assert(ans_1 == ans_2);
		assert(ans_2 == ans_3);

		cout << (ans_1 ? "found" : "not found") << endl;
	}

	return 0;
}
