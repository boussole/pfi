/***********************************************************
 * \file    string.h
 * \brief   Utilities for string tasks.
 * \details Each function is a ticket task. Input string is not necessary to be a null-terminated
 * \author  boussole
 * \warning Some functions could change input string
 **********************************************************/

#ifndef STRINGTASK_H_
#define STRINGTASK_H_

#include <matrix/matrix.h>
#include <common/common.h>

/***********************************************************
 * \namespace conq_string
 * \brief Group operations with strings
 **********************************************************/
namespace conq_string {

struct Bracket {
	Bracket(int p) : pos(p), used(false) {}
	int pos;
	bool used;
};

/***********************************************************
 * \brief Check bracket symmetry
 * \detailed
 * \return Return invalid bracket position OR string len in case of success
 **********************************************************/
template <typename T>
int checkBracketSymmetry(const T * s, int len)
{
	std :: list<Bracket> open;
	std :: list<Bracket> :: reverse_iterator last_open = open.rend();
	int pos = 0;

	while (pos < len) {
		if (s[pos] == '(') {
			open.push_back(Bracket(pos));
			last_open = open.rbegin();
		}
		else if (s[pos] == ')') {
			while (last_open != open.rend()) {
				if (!last_open->used) {
					last_open->used = true;
					break;
				}

				last_open++;
			}

			if (last_open == open.rend())
				return pos;
		}

		pos++;
	}

	while (last_open != open.rend()) {
		if (!last_open->used)
			return last_open->pos;

		last_open++;
	}

	return len;
}

/***********************************************************
 * \brief Find starting point of the largest reoccurring character (#38).
 * \param[in] str Input string
 * \param[in] len Length of input string
 * \return Return result position or -1 in case of empty string
 **********************************************************/
int findLargestReoccuringCharacter(const char * str, size_t len);

/***********************************************************
 * \brief Find minimal distance between symbols (#88).
 * \param[in] str Input string for analysis
 * \param[in] len Length of input string
 * \param[in] left Start symbol of required piece
 * \param[in] right Finish symbol of required piece
 * \return Return length of minimal required piece between symbols or -1 in case of error
 **********************************************************/
int findMinDistance(const char * str, size_t len, int left, int right);

/**********************************************************
 * \brief  Naive algorithm finding substring
 * \return Start position of substring
 **********************************************************/
template <typename TChar>
int findSubString_Naive(TChar * haystack, std :: size_t hSz, TChar * needle, std :: size_t nSz)
{
	if (hSz < nSz)
			return -1;

	std :: size_t h = 0, n = 0;

	while (h < hSz) {
		if (haystack[h] == needle[n]) {
			if (++n == nSz)
				return static_cast<int>(h - (nSz - 1));
		}
		else if (n > 0) {
			n = 0;
			continue;
		}
		++h;
	}

	return -1;
}

/**********************************************************
 * \brief  Rabin-Karp algorithm finding substring
 * \return Start position of substring
 **********************************************************/
template <typename TChar>
int findSubString_RK(TChar * haystack, std :: size_t hSz, TChar * needle, std :: size_t nSz)
{
	if ((hSz == 0) || (nSz == 0) || (hSz < nSz))
		return -1;

	int max_pow = 1;
	for (std :: size_t i = 1; i < nSz; ++i) {
		max_pow <<= 1;
	}

	// create hash for needle and haystack[0 .. nSz]
	int candidate_hash = 0, needle_hash = 0, pow = max_pow;
	for (std :: size_t pos = 0; pos < nSz; ++pos) {
		candidate_hash += haystack[pos] * pow;
		needle_hash += needle[pos] * pow;
		pow >>= 1;
	}

	if ((candidate_hash == needle_hash) && (strncmp(haystack, needle, nSz) == 0))
		return 0;

	for (std :: size_t i = nSz - 1, pos = 0; i < hSz; ++pos) {
		if (candidate_hash == needle_hash) {
			if (strncmp(&haystack[pos], needle, nSz) == 0)
				return static_cast<int>(pos);
		}

		candidate_hash = ((candidate_hash - haystack[pos] * max_pow) << 1) + haystack[++i];
	}

	return -1;
}

/**********************************************************
 * \brief   Knuth Morris Pratt prefix function
 * \details Calculate maximal prefix which is equal for 'self' suffix
 *          for input string
 * \note    's' size should be the same as prefix array and
 *          preallocated by caller
 **********************************************************/
template <typename TChar>
void prefixFunction_KMP(TChar * s, std :: size_t * prefix, std :: size_t sz)
{
	prefix[0] = 0; // always, cause it is the 'same' suffix
	int j = 0;

	for (std :: size_t i = 1; i < sz; ++i) {
		while (j != 0 && s[i] != s[j]) {
			j = prefix[j - 1];
		}

		if (s[i] == s[j])
			++j;

		prefix[i] = j;
	}
}

/**********************************************************
 * \brief Knuth Morris Pratt algorithm finding substring
 **********************************************************/
template <typename TChar>
int findSubString_KMP(TChar * haystack, std :: size_t hSz, TChar * needle, std :: size_t nSz)
{
	if ((hSz == 0) || (nSz == 0) || (hSz < nSz))
		return -1;

	std :: unique_ptr<std :: size_t[]> prefix(new std :: size_t[nSz]);

	prefixFunction_KMP(needle, prefix.get(), nSz);

	int k = 0;
	for (int i = 0; i < static_cast<int>(hSz); ++i) {
		while (k > 0 && haystack[i] != needle[k])
			k = prefix[k - 1];

		if (haystack[i] == needle[k])
			++k;

		if (k == static_cast<int>(nSz))
			return i - nSz + 1;
	}

	return -1;
}

/**********************************************************
 * \brief  Longest common substring
 * \param [out] lcs Position of lcSuff in lhs string
 * \return Start position of substring
 **********************************************************/
template <typename TChar>
std :: size_t lcSuff(std :: basic_string<TChar> & lhs, std :: basic_string<TChar> & rhs, std :: list<std :: pair<int, int> > & lcs)
{
	lcs.clear();

	boost :: numeric :: ublas :: matrix<int> m(lhs.size() + 1, rhs.size() + 1);

	for (std :: size_t l = 0; l < lhs.size(); ++l)
	for (std :: size_t r = 0; r < rhs.size(); ++r) {
		m(l + 1, r + 1) = (lhs[l] == rhs[r]) ? m(l, r) + 1 : 0;
	}

	// search multiple lcSuff
	int max_len = 0;
	for (std :: size_t i = 1; i < m.size1(); ++i)
	for (std :: size_t j = 1; j < m.size2(); ++j) {
		if (m(i, j) > max_len) {
			max_len = m(i, j);
			lcs.clear();
			lcs.push_back(std :: make_pair(static_cast<int>(i) - max_len, max_len));
		}
		else if (m(i, j) == max_len) {
			lcs.push_back(std :: make_pair(static_cast<int>(i) - max_len, max_len));
		}
	}

	// conq_matrix :: print(m);

	return lcs.size();
}

/**********************************************************
 * \brief Edit distance
 **********************************************************/
template <typename TChar>
int editDistance(const std :: basic_string<TChar> & src, const std :: basic_string<TChar> & dst)
{
	boost :: numeric :: ublas :: matrix<int> m(src.size() + 1, dst.size() + 1); // initialized by zero by default

	for (std :: size_t i = 0; i <= src.size(); ++i)
	for (std :: size_t j = 0; j <= dst.size(); ++j) {
		if (i == 0)
			m(i, j) = j; // if we are going from empty src to dst (we should insert symbol on each operation)
		else if (j == 0)
			m(i, j) = i; // if we are going from src to empty dst (we should delete symbol on each operation)
		else if (src[i - 1] != dst[j - 1])
			m(i, j) = 1 + conq_common :: min3(m(i - 1, j - 1), m(i, j - 1), m(i - 1, j));
		else
			m(i, j) = m(i - 1, j - 1);
	}

	return m(src.size(), dst.size());
}

/**********************************************************
 * \brief  Revert UTF-8 string
 * \return Success | Fail
 **********************************************************/
bool revertUtf8(char * str, int len);

/**********************************************************
 * \brief Make k-th column excel name
 **********************************************************/
std :: string kthExcelColumnName(int k);

/**********************************************************
 * \brief Remove side spaces
 ***********************************************************/
std :: string trim(std :: string && s);

class TextTreeParser
{
	typedef std :: pair<std :: size_t, std :: size_t> lex_t;

	enum class FA {
		Find_Item_Start,
		Find_Item_Stop,
		Find_Data_Start,
		Find_Data_Stop
	};

	struct Unit {
		std :: map<std :: size_t, Unit> _child;
		std :: list<std :: string> _value;
	};

public:
	TextTreeParser(const std :: string & text);
	~TextTreeParser() {}
	void print();

protected:
	void start();
	bool step();
	void stop();
	void findItemStart();
	void findItemStop();
	void findDataStart();
	void findDataStop();
	void putData(const std :: string && key, const std :: string && value);

private:
	const std :: string & _text;
	lex_t _item, _data;
	std :: size_t _nextItemStart;
	FA _state;
	std :: size_t _pos;
	Unit _tree;
};

/**********************************************************
 * \brief   Balance parenthes
 * \details Speed = O(N), Memory = O(1)
 **********************************************************/
void balance_parentheses(std :: string & str);

} /* namespace conq_string */

class StringTask {
public:
	StringTask();
	virtual ~StringTask();
	virtual bool doTask(int argc, char ** argv) = 0;

protected:
	virtual std :: size_t ticketNum() = 0;
	inline void printTicketNum() { std :: cout << "#" << ticketNum() << std :: endl; }
	inline void usage(char * app) { std :: cout << "usage: " << app << " \"string\"" << std :: endl; }
	static const std :: size_t MaxStringLen = 255;
};


class RevertWordsInString : public StringTask
{
public:
	RevertWordsInString() { printTicketNum(); }
	~RevertWordsInString() {}
	std :: size_t ticketNum() { return 37; }
	bool doTask(int argc, char ** argv);

private:
	void doTask(char * str, std :: size_t len);
	void doTaskWithStlString(char * str, std :: size_t len);
	// (ie. input:"abc def ghi" output:"ghi def abc")
	void doTaskUsingRevertFunc(char * str, std :: size_t len);
};

/**
 * print uniq strings from array
 */
class UniqStringPrint : public StringTask
{
public:
	UniqStringPrint() { printTicketNum(); }
	~UniqStringPrint() {}
	bool doTask(int argc, char ** argv);
	inline void usage(char * app) { std :: cout << "usage: " << app << " [ str0 str1 ... strN ]" << std :: endl; }
	std :: size_t ticketNum() { return 43; }
	static void printUniq(char ** str, int len);
};

/**
 * revert all words in a string
 * (ie. input:"abc def ghi" output:"ihg fed cba")
 */
class RevertString : public StringTask
{
public:
	RevertString() { printTicketNum(); }
	~RevertString() {}
	bool doTask(int argc, char ** argv);
	std :: size_t ticketNum() { return 90; }
	/** */
	static void revert(std :: string & str);
};

/**
 * find first unique symbol in a string
 */
class FindFirstUniqueSym : public StringTask
{
public:
	FindFirstUniqueSym() { printTicketNum(); }
	~FindFirstUniqueSym() {}
	std :: size_t ticketNum() { return 113; }
	bool doTask(int argc, char ** argv);
};

#endif /* STRINGTASK_H_ */
