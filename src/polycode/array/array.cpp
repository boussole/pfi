/**
 * \file    array.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include "array.h"
#include <sort/sort.h>

namespace conq_array {

/**
 * @details Callback who will use for finding triplet
 */
bool SumOfQuad(int a, int b, int c)
{
	return ((a * a + b * b) == c * c);
}

namespace naive {
/**
 * SumOfQuad specific search O(N^3)
 */
void findTriplet_SumOfQuad(boost :: scoped_array<int> & arr, int size)
{
	std :: sort(arr.get(), arr.get() + size,
		[](int left, int right){
				return abs(left) < abs(right);
		}
	);

	print(arr.get(), size, "sort: ");

	int counter = 0;
	
	for (int a = 0; a < size; a++)
		for (int b = a + 1; b < size; b++)
			for (int c = 0; c < size; c++) {
				if ((a != c) && (b != c) && SumOfQuad(arr[a], arr[b], arr[c])) {
					std :: cout << "Triplet: a = " << arr[a] << " b = " << arr[b] << " c = " << arr[c] << "; index: " << a << " " << b << " " << c << std :: endl;
					std :: cout << "Triplet: a = " << arr[b] << " b = " << arr[a] << " c = " << arr[c] << "; index: " << b << " " << a << " " << c << std :: endl;
					counter += 2;
				}
			}

	std :: cout << __func__ << " result: " << counter << " matches\n";
}

}

/**
 * SumOfQuad specific search O(N^2)
 */
void findTriplet_SumOfQuad(boost :: scoped_array<int> & arr, int size)
{
	std :: for_each(arr.get(), arr.get() + size, [](int & value){ value *= value; });

	std :: sort(arr.get(), arr.get() + size);

	for (int i = size - 1; i >= 2; --i) {
		int l = 0, r = i - 1;
		while (l < r) {
			int sum = arr[l] + arr[r];
			if (sum < arr[i])
				++l;
			else if (sum > arr[i])
				--r;
			else {
				std :: cout << "triplet: a = " << std :: sqrt(arr[i]) <<
				              " b = " << std :: sqrt(arr[l]) <<
				              " c = " << std :: sqrt(arr[r]) << std :: endl;
				++l;
				--r;
				break;
			}
		}
	}
}

namespace greedy {

/***********************************************************
 * \brief  Create change from coints and return minimal number of coints
 * \return Minimal quantity of coins
 ***********************************************************/
int makeMinChange(int * coin, int coinSz, int changeSum, int * changeCoin)
{
	assert(coinSz > 0);

	// sort coin to grow
	conq_sort :: insertSort(coin, coinSz);

	if (changeSum == 0)
		return 0;

	if (changeSum < coin[0])
		return -1;

	// search max(coin) <= changeSum
	int start = 0;
	for (; (coin[start] < changeSum) && (start < coinSz); ++start);
	--start;

	// max border level
	for (; start >= 0; --start) {
		std :: memset(changeCoin, 0, coinSz);
		// down to sublevel
		int sum = 0, res = 0;
		for (int j = start; j >= 0; --j) {
			assert(coin[j] > 0);
			while (sum + coin[j] <= changeSum) {
				sum += coin[j];
				++res;
				++changeCoin[j];
			}
			if (sum == changeSum) {
				return res;
			} else if (j == 0) {
				int nearest = j + 1;
				for (; (nearest <= start) && (changeCoin[nearest] == 0); ++nearest);
				if (nearest <= start) {
					--changeCoin[nearest];
					sum -= coin[nearest] + coin[j] * changeCoin[j];
					res -= 1 + changeCoin[j];
					changeCoin[j] = 0;
					j = nearest;
				}
			}
		}
	}

	return -1;
}

} /* namespace greedy */

namespace dp {

/*************************************************************
 * \brief  Create change from coints and return minimal number of coints
 * \return Minimal quantity of coins
 *************************************************************/
int makeMinChange(int * coin, int coinSz, int changeSum, int * changeCoin)
{
	assert(coinSz > 0);

	// sort coin to grow
	conq_sort :: insertSort(coin, coinSz);

	if (changeSum == 0)
		return 0;

	if (changeSum < coin[0])
		return -1;

	// create array of change and fill it basic values
	struct ChangeStep {
		ChangeStep() : _min(0), _coin(0) {}
		ChangeStep(int min, int coin) : _min(min), _coin(coin) {}
		int _min;
		int _coin;
	};

	std :: unique_ptr<ChangeStep[]> ch(new ChangeStep[changeSum + 1]);

	for (int i = 1; i <= changeSum; ++i) {
		ch[i]._min = -1;
		ch[i]._coin = -1;
		// for each available coin
		for (int c = 0; (c < coinSz) && (coin[c] <= i); ++c) {
			int prev = i - coin[c];
			if (ch[prev]._min != -1) {
				ChangeStep step(1 + ch[prev]._min, coin[c]);
				if ((ch[i]._min == -1) || (ch[i]._min > step._min))
					ch[i] = step;
			}
		}

//		std :: cout << i << ": " << ch[i]._min << " (" << ch[i]._coin << ")\n";
	}

	if (ch[changeSum]._min > 0) {
		int i = changeSum;
		std :: memset(changeCoin, 0, coinSz);
		while (i != 0) {
			// slowly, but only for example
			for (int j = 0; j < coinSz; ++j) {
				if (coin[j] == ch[i]._coin) {
					++changeCoin[j];
					break;
				}
			}
			i -= ch[i]._coin;
		}

		return ch[changeSum]._min;
	}

	return -1;
}

/*************************************************************
 * \brief  Find continuous subsequence with maximal sum
 * \return Sum of subsequence
 *************************************************************/
int findContinuousSubsequenceWithMaxSum(int * seq, int seqSz, int & start, int & finish)
{
	assert(seqSz > 0);

	std :: unique_ptr<int[]> sum(new int[seqSz]);

	sum[0] = seq[0];

	for (int i = 1; i < seqSz; ++i) {
		sum[i] = std :: max(seq[i], seq[i] + sum[i - 1]);
	}

	start = finish = seqSz - 1;
	int max_sum = sum[finish];
	bool search_start = true;

	for (int i = start; i >= 0; --i) {
		if (sum[i] > max_sum) {
			max_sum = sum[i];
			start = finish = i;
			search_start = true;
		}

		if (search_start) {
			if (sum[i] == seq[i])
				search_start = false;
			else
				--start;
		}
	}

	return max_sum;
}

/*************************************************************
 * \brief  Longest zig-zag subsequence
 * \return Length of the longest subsequnce
 *************************************************************/
int longestZigZag(int * sequence, int size)
{
	int len = 0;

	if (size == 0)
		return len;

	std :: unique_ptr<int[]> f_min(new int[size]), f_max(new int[size]), f(new int[size]);

	for (int i = 0; i < size; ++i) {
		f_min[i] = f_max[i] = f[i] = 1; // induction basis
		for (int j = 0; j < i; ++j) {
			// up
			if (sequence[j] < sequence[i]) {
				f_max[i] = std :: max(f_min[j] + 1, f_max[i]);
			}
			// down
			else if (sequence[j] > sequence[i]) {
				f_min[i] = std :: max(f_max[j] + 1, f_min[i]);
			}

			f[i] = std :: max(f_min[i], f_max[i]);
		}
	}
#if 0
	std :: cout << "f_min: ";
	for (int i = 0; i < size; ++i)
		std :: cout << " " << f_min[i];
	std :: cout << "\nf_max: ";
	for (int i = 0; i < size; ++i)
		std :: cout << " " << f_max[i];
	std :: cout << "\nf: ";
	for (int i = 0; i < size; ++i)
		std :: cout << " " << f[i];
	std :: cout << std :: endl;
#endif
	len = 1;

	for (int i = 1; i < size; ++i) {
		if (len < f[i]) {
			len = f[i];
		}
	}

	return len;
}

} /** namespace dp */

/************************************************************
 * \brief Replace numbers in array for merge maximal number
 ************************************************************/
void buildMaximalMergeNumber(int * arr, int size)
{
	std :: function<int(int &)> order = [](int & val)->int {
			int o = 10;
			for (; val >= o; o *= 10);
			return o;
		}
	;

	std :: sort(arr, arr + size, [&](int & lhs, int & rhs)->bool {
			int lo = order(lhs);
			int ro = order(rhs);

			if (lo > ro) {
				int tmp = lhs / (lo / ro);

				if (tmp > rhs)
					return true;
				return false;
			}
			else if (lo < ro) {
				int tmp = rhs / (ro / lo);

				if (tmp > lhs)
					return false;
				return true;
			}

			return lhs > rhs;
		}
	);
}

/************************************************************
 * \brief Find subsequence closest to zero
 ************************************************************/
std :: pair<int, int> findSubsequenceClosestZero(int * arr, int size)
{
	assert(size > 0);

	// build prefix
	std :: unique_ptr<std :: pair<int, int>[]> pref(new std :: pair<int, int>[size]);
	pref[0].first = 0;
	pref[0].second = arr[0];
	for (int i = 1; i < size; ++i) {
		pref[i].first = i;
		pref[i].second = arr[i] + pref[i - 1].second;
	}

	std :: pair<int, int> first = pref[0], last = pref[size - 1];

	std :: cout << "prefix:";
	for (int i = 0; i < size; ++i)
		std :: cout << " [" << pref[i].first << "] = " << pref[i].second;
	std :: cout << std :: endl;

	std :: sort(pref.get(), pref.get() + size, [](std :: pair<int, int> &lhs, std :: pair<int, int> &rhs) {
		return lhs.second < rhs.second;
	});

	std :: cout << "prefix sorted:";
	for (int i = 0; i < size; ++i)
		std :: cout << " [" << pref[i].first << "] = " << pref[i].second;
	std :: cout << std :: endl;

	std :: pair<int, int> subseq;
	int min = abs(pref[size - 1].second);
	subseq.first = 0;
	subseq.second = 1;

	for (int i = 1; i < size; ++i) {
		int new_min = abs(pref[i].second - pref[i - 1].second);
		std :: cout << "gout (" << new_min << ":" << pref[i].first << ":" << pref[i - 1].first << ")\n";
		if (new_min < min) {
			subseq.first = pref[i - 1].first + 1;
			subseq.second = pref[i].first + 1;
			min = new_min;
		}
	}

	// special cases
	if (abs(first.second) <= min) {
		subseq.first = first.first;
		subseq.second = subseq.first + 1;
		std :: cout << "hop\n";
	}
	else if (abs(last.second) <= min) {
		// full sequence has result
		subseq.first = first.first;
		subseq.second = last.first + 1;
	}

	// normalize
	if (subseq.first > subseq.second)
		std :: swap(subseq.first, subseq.second);

	return subseq;
}

/************************************************************
 * \brief Maximum Product Subsequence
 ************************************************************/
int maximumProductSubsequence(int * arr, int size, std :: list<int> &subseq)
{
	assert(size > 0);

	int product = 1;

	int zero_counter = 0, neg_counter = 0, max_neg_pos = 0, pos_counter = 0;

	for (int i = 0; i < size; ++i) {
		if (arr[i] > 0) {
			product *= arr[i];
			++pos_counter;
		}
		else if (arr[i] < 0) {
			product *= arr[i];
			++neg_counter;
			if ((neg_counter == 1) || (arr[max_neg_pos] < arr[i]))
				max_neg_pos = i;
		}
		else
			++zero_counter;
	}

	// we have only zero's
	if (pos_counter == 0 && neg_counter == 0) {
		subseq.assign(size, 0);
		product = 0;
	}
	else if (product < 0 && size > 1) {
	// try to increase product if we have more than 1 element
		// 1) we have 1 negative and zero's
		if (neg_counter == 1 && pos_counter == 0) {
			for (int i = 0; i < size; ++i)
				if (arr[i] == 0)
					subseq.push_back(arr[i]);
			product = 0;
		}
		// 2) we have odd number of negatives
		else {
			product /= arr[max_neg_pos];
			for (int i = 0; i < max_neg_pos; ++i)
				if (arr[i])
					subseq.push_back(arr[i]);
			for (int i = max_neg_pos + 1; i < size; ++i)
				if (arr[i])
					subseq.push_back(arr[i]);
		}
	}
	else {
		for (int i = 0; i < size; ++i)
			if (arr[i] != 0)
				subseq.push_back(arr[i]);
	}

	return product;
}

} /** conq_array */

using namespace boost;

/** +++ FIND K MAX ELEMENTS +++ */

bool FindKMaxElements :: doTask(int argc, char ** argv)
{
	if (argc < 3) {
		std :: cout << "usage: " << *argv << " k=[val] [ array[0] ... array[n] ]" << std :: endl;
		return false;
	}

	if (strncmp(argv[1], "k=", 2) != 0) {
		std :: cout << "usage: " << *argv << " k=[val] [ array[0] ... array[n] ]" << std :: endl;
		return false;
	}

	int k = atoi(argv[1] + 2);
	if (k <= 0) {
		std :: cout << "invalid K = " << k << std :: endl;
		return false;
	}

	doTask(argv + 2, argc - 2, k);

	return true;
}

/*
 * show K maximal elements from stream
 */
void FindKMaxElements :: doTask(char ** stream, int streamSz, int k)
{
	scoped_array<int> array(new int[k]);

	int array_sz = 0, stream_idx = 0;
	/** fill out first K elements */
	for (array_sz = 0; (array_sz < k) && (stream_idx < streamSz); array_sz++, stream_idx++) {
		array[array_sz] = atoi(stream[stream_idx]);
	}

	/** for other stream element */
	for (; stream_idx < streamSz; stream_idx++) {
		int val = atoi(stream[stream_idx]);

		/** search the least element */
		for (int idx = 0; idx < k; idx++) {
			if (array[idx] < val) {
				int min = idx; /**< safe the least elememt */
				for (idx += 1; idx < k; idx++) {
					if (array[idx] < array[min]) {
						min = idx;
					}
				}

				array[min] = val; /** replacement */
			}
		}
	}

	/** show array */
	std :: cout << "array of " << k << " maximal element(s) :";
	for (int i = 0; i < array_sz; i++) {
		std :: cout << " " << array[i];
	}

	std :: cout << std :: endl;
}

/** --- FIND K MAX ELEMENTS --- */

bool FindMinElementOfIndexK :: doTask(int * arr, int arrSz, int kMin)
{
	if ((kMin <= 0) || (kMin > arrSz)) {
		std :: cout << "invalid K = " << kMin << std :: endl;
		return false;
	}

	doTaskStable(arr, arrSz, kMin);
	doTaskSorting(arr, arrSz, kMin);

	return true;
}

bool FindMinElementOfIndexK :: checkAround(const int * array, int pos, int sz, int value, int & less, int & greater, int & equal, boost::function<bool(int, int)> & runner)
{
	for (; pos < sz; pos++) {
		if (array[pos] == value) {
			equal++;
		}
		else {
			array[pos] < value ? less++ : greater++;
		}

		if (!runner(less, greater)) {
			return false;
		}
	}

	return true;
}

bool FindMinElementOfIndexK :: checkIdx(const int * array, int sz, int idx, boost::function<bool(int, int)> & runner)
{
	int less = 0, greater = 0;

	return (
		checkAround(array, 0, idx, array[idx], less, greater, less, runner) &&
		checkAround(array, idx + 1, sz, array[idx], less, greater, greater, runner)
	);
}

void FindMinElementOfIndexK :: doTaskStable(int * arr, int arrSz, int kMin)
{
	boost :: scoped_array<int> array(new int[arrSz]);

	for (int i = 0; i < arrSz; i++)
		array[i] = arr[i];

	const int less_num = kMin - 1;
	const int greater_num = arrSz - kMin;

	std :: cout << "less = " << less_num << " greater = " << greater_num << std :: endl;

	boost::function<bool(int, int)> runner = boost :: bind<bool>(
		[](int less, int greater, int lessLimit, int greaterLimit)->bool {
			return ((less <= lessLimit) && (greater <= greaterLimit));
		}, _1, _2, less_num, greater_num);

	int idx = 0;
	/** for each element */
	for (idx = 0; idx < arrSz; idx++) {
		/** check with each one before */
		if (checkIdx(array.get(), arrSz, idx, runner)) {
			break;
		}
	}

	assert(idx < arrSz);

	std :: cout << __PRETTY_FUNCTION__ << " Min(A)[" << kMin << "] = " << array[idx] << " , idx = " << idx << std :: endl;
}

void FindMinElementOfIndexK :: doTaskSorting(int * arr, int arrSz, int kMin)
{
	// save array to prevent change src data for another methods
	boost :: scoped_array<int> array(new int[arrSz]);

	for (int i = 0; i < arrSz; i++)
		array[i] = arr[i];

	std::sort(array.get(), array.get() + arrSz, std::less<int>());

	conq_array :: print(array.get(), arrSz, "sort: ");

	std :: cout << __PRETTY_FUNCTION__ << " Min[" << kMin << "] = " << array[kMin - 1] << std :: endl;
}
