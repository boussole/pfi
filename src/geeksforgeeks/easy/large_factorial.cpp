/*
   Calculate the factorial for a given number.

   Input:
   The first line contains an integer 'T' denoting the total number of test cases. In each test cases, it contains an integer 'N'.

   Output:
   In each seperate line output the answer to the problem.

   Constraints:
   1<=T<=101
   0<=N<=100

   Example:
      Input:
      1
      1

      Output:
      1
 */

#include <iostream>
#include <vector>

using namespace std;

static const int MinNrTests = 1;
static const int MaxNrTests = 101;

static const int MinValue = 0;
static const int MaxValue = 100;

class big_number : public vector<int>
{
	using _base = vector<int>;
	_base &_obj = *this;
public:
	big_number(uint64_t val = 0) {
		size_t len = 0;
		do {
			resize(len + 1);
			_obj[len++] = val % 10;
			val /= 10;
		} while (val);
	}

	big_number(const big_number &rhs) {
		if (this != &rhs)
			*this = rhs;
	}

	~big_number() {}

	big_number & operator=(const big_number &rhs) {
		if (this != &rhs)
			*static_cast<_base*>(this) = *static_cast<const _base*>(&rhs);

		return *this;
	}

	big_number & operator++()
	{
		int residue = 1;
		size_t len = size();

		for (size_t i = 0; (i < len && residue); ++i) {
			_obj[i] = _obj[i] + residue;
			residue = _obj[i] / 10;
			_obj[i] %= 10;
		}

		if (residue) {
			resize(len + 1);
			_obj[len++] = residue;
		}

		return *this;
	}

	big_number & operator*(const big_number &rhs)
	{
		big_number result;
		result.resize(_obj.size() + rhs.size() + 1);

		size_t max_len = 0;
		int carry = 0;
		for (size_t i = 0; i < _obj.size(); ++i) {
			size_t j = 0;
			carry = 0;
			for(; j < rhs.size(); ++j) {
				size_t pos = i + j;
				result[pos] += _obj[i] * rhs[j] + carry;
				carry = result[pos] / 10;
				result[pos] %= 10;
			}
			
			size_t pos = i + j;			

			if (carry) {
				result[pos] = carry;
				max_len = pos;
			} else
				max_len = pos - 1;
		}

		result.resize(max_len + 1);
		_obj = move(result);
		return *this;
	}
		
	friend ostream & operator<<(ostream &os, big_number &rhs)
	{
		return rhs.print(os);
	}

private:
	ostream& print(ostream &os)
	{
                int len = size();
                while (len > 0)
                        os << _obj[--len];
                
                return os;
	}
};

// speed O(exp ^ exp)
// memory O(exp ^ exp)
big_number & large_factorial(uint32_t n, big_number &bn)
{
	big_number multiplier(1), factorial(1);

	for (uint32_t i = 1; i <= n; ++i, ++multiplier)
		factorial = factorial * multiplier;

	bn = factorial;

	return bn;
}

int main()
{
	int nr_tests = 0;
	cin >> nr_tests;

	if (nr_tests < MinNrTests || nr_tests > MaxNrTests) {
		cerr << "constraints: 1 ≤ T ≤ 101\n";
		return 1;
	}

	while (nr_tests--) {
		int value;
		cin >> value;
		if (value < MinValue || value > MaxValue) {
			cerr << "constraints: 0<=N<=100\n";
			return 1;
		}

		big_number bn;
		cout << large_factorial(static_cast<uint32_t>(value), bn) << endl;
	}

	return 0;
}
