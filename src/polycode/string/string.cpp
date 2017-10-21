/***********************************************************
 * \file    string.cpp
 * \brief   Utilities for string tasks.
 * \details Each function is a ticket task. Input string is not necessary to be a null-terminated
 * \author  boussole
 * \warning Some functions could change input string
 **********************************************************/

#include "string.h"

#include <string.h>
#include <strings.h>
#include <locale>
#include <vector>
#include <boost/scoped_array.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

namespace conq_string {

using namespace std;

/**********************************************************
 * \brief Function returns the position of the starting point of the largest reoccurring character.
 * (ie. given:"AAABBCCCCD" would return 5 (starting point of C)).
 * \note https://en.wikipedia.org/wiki/Longest_repeated_substring_problem
 **********************************************************/
int findLargestReoccuringCharacter(const char * str, size_t len)
{
	int res = -1, pos = 0;
	std :: size_t max_seq_sz = 0;

	while (static_cast<size_t>(pos) < len) {
		int start_pos = pos;
		std :: size_t seq_sz = 0;
		char sym = str[pos];

		while ((str[pos] == sym) && (static_cast<size_t>(pos) < len)) {
			seq_sz++;
			pos++;
		}

		if (seq_sz > max_seq_sz) {
			max_seq_sz = seq_sz;
			res = start_pos;
		}
	}

	return res;
}

/**********************************************************
 * \brief Function searches two symbols in the string.
 * If there are more than one piece, function returns
 * minimal of them.
 * If start or finish or both symbols of piece doesn't exist then function returns -1
 * \note http://www.geeksforgeeks.org/find-the-minimum-distance-between-two-numbers/
 **********************************************************/
int findMinDistance(const char * str, size_t len, int left, int right)
{
	size_t distance = len;

	string s(str, len);

	size_t left_min = 0, right_min = 0;

	while ( (left_min = s.find(static_cast<char>(left), left_min)) != string :: npos) {
		if ((right_min = s.find(static_cast<char>(right), left_min)) != string :: npos) {
			size_t new_distance = right_min - left_min;
			if (new_distance < distance) {
				distance = new_distance;
				if (distance <= 1) { // possible left == right
					break;
				}
			}
		}

		left_min++;
	}

	if (distance == len) {
		return -1;
	}

	return distance;
}

#ifndef DOXYGEN_IGNORE

/** 0XXXXXXX */
//static inline bool isAsciiByte(uint8_t byte)
//{
//	static const uint8_t AsciiByteMask = 0x80;
//
//	return ((byte & AsciiByteMask) == 0);
//}

#endif

#define MAX_UTF8_SYM_SZ 6

/**********************************************************
 * @brief Function check byte and return true if that byte is not master
 * @param [in] byte Testing byte
 * @return TRUE if byte is not a master
 **********************************************************/

static inline bool isUtf8SlaveByte(uint8_t byte)
{
	static const uint8_t Utf8SlaveByteMask = 0xC0;

	return ((byte & Utf8SlaveByteMask) == 0x80);
}

/**********************************************************
 * @brief Check first byte of utf8 symbol
 * @details First byte of utf8 symbol should contain length of symbol.
 * Function read first byte check it and return length of symbol or false in case of error
 *
 * @param [in] byte First byte of utf8 symbol
 * @param [out] len Length of full utf8 symbol (valid in case of success call)
 * @return true in case of correct byte, false in other case
 ***********************************************************/
static inline bool isUtf8MasterByte(uint8_t byte, int & len)
{
	if (!isUtf8SlaveByte(byte)) {
		if (byte < 0x80) {
			len = 1;
		} else if (byte < 0xE0) {
			len = 2;
		} else if (byte < 0xF0) {
			len = 3;
		} else if (byte < 0xF8) {
			len = 4;
		} else if (byte < 0xFC) {
			len = 5;
		} else if (byte < 0xFE) {
			len = 6;
		} else {
			return false;
		}

		return true;
	}

	return false;
}

/**********************************************************
 * \brief  Revert UTF-8 string
 * \return Success | Fail
 **********************************************************/
bool revertUtf8(char * str, int len)
{
	uint8_t head[MAX_UTF8_SYM_SZ], tail[MAX_UTF8_SYM_SZ];
	int head_len = 0, tail_len = 0, head_pos = 0, tail_pos = len, head_res = 0, tail_res = len - 1;

	while (head_pos < tail_pos) {
		/** fill out from head */
		if (!head_len) {
			int sym_len = 0;
			if (!isUtf8MasterByte(str[head_pos], sym_len) || (head_pos + sym_len > len)) { return false; }
			head[head_len++] = str[head_pos++];
			while(--sym_len) {
				head[head_len++] = str[head_pos];
				if (!isUtf8SlaveByte(str[head_pos++])) { return false; }
			}
		}
		/** fill out from tail */
		if (!tail_len) {
			int sym_len = 0;
			while ((tail_len < MAX_UTF8_SYM_SZ) && (head_pos <= --tail_pos)) {
				tail[tail_len++] = str[tail_pos];
				if (isUtf8MasterByte(str[tail_pos], sym_len)) { break; }
				else if (!isUtf8SlaveByte(str[tail_pos])) { return false; }
			}

			if (sym_len != tail_len) { return false; }
		}

		/** swap */
		while (head_len && tail_len) {
			str[tail_res--] = head[--head_len];
			str[head_res++] = tail[--tail_len];
		}
	}

	/** residue */
	while (head_len) { str[tail_res--] = head[--head_len]; }
	while (tail_len) { str[head_res++] = tail[--tail_len]; }

	return true;
}

#undef MAX_UTF8_SYM_SZ

/**********************************************************
 * \brief Make k-th column excel name
 **********************************************************/
std :: string kthExcelColumnName(int k)
{
	assert(k >= 0);

	std :: string revert, name;

	char base = 'A';

	while (k > 26) {
		int residue = k % 26;
		revert += (base + residue - 1);
		k /= 26;
	}

	revert += (base + k - 1);

	// normalize name
	name.resize(revert.size());
	for (std :: size_t i = 0, j = revert.size() - 1; i < name.size(); ++i, --j) {
		name[j] = revert[i];
	}

	return name;
}

/**********************************************************
 * \brief Remove side spaces
 ***********************************************************/
std :: string trim(std :: string && s)
{
	static const std::string whitespaces (" \t\f\v\n\r");
	std::size_t first = s.find_first_not_of(whitespaces);

	if (first != std :: string :: npos) {
		std::size_t last = s.find_last_not_of(whitespaces);
		return s.substr(first, last - first + 1);
	}

	return std :: string();
}

TextTreeParser :: TextTreeParser(const std :: string & text) : _text(text)
{
	start();

	for ( ; step(); );

	stop();
}

void TextTreeParser :: print()
{
	std :: function<void(std :: size_t, const Unit &)> fn = [&](std :: size_t level, const Unit & u) {
		std :: map<std :: size_t, Unit> :: const_iterator it = u._child.cbegin();
		std :: string indent(level * 3, ' ');
		for (; it != u._child.cend(); ++it) {
			std :: cout << indent << it->first << " (";
			std :: list<std :: string> :: const_iterator v = it->second._value.cbegin();
			for (; v != it->second._value.cend(); ++v) {
				std :: cout << " \"" << *v <<"\"";
			}
			std :: cout << " )\n";

			fn(level + 1, it->second);
		}
	};

	fn(0, _tree);
}

void TextTreeParser :: start()
{
	_item.first = _text.npos;
	_nextItemStart = _text.npos;
	_data.first = _text.npos;
	_state = FA :: Find_Item_Start;
	_pos = 0;
}

bool TextTreeParser :: step()
{
	if (_pos == _text.length())
		return false;

	switch (_state) {
		case(FA :: Find_Item_Start): findItemStart(); break;
		case(FA :: Find_Item_Stop): findItemStop(); break;
		case(FA :: Find_Data_Start): findDataStart(); break;
		case(FA :: Find_Data_Stop): findDataStop(); break;
	};

	++_pos;

	return true;
}

void TextTreeParser :: stop()
{
	if (_state == FA :: Find_Data_Stop || _state == FA :: Find_Item_Start) {
//		std :: cout << "item: " << _text.substr(_item.first, _item.second - _item.first) << std :: endl;
//		std :: cout << "data: " << _text.substr(_data.first, _pos - _data.first) << std :: endl;
		putData(_text.substr(_item.first, _item.second - _item.first), trim(_text.substr(_data.first, _pos - _data.first)));
	}
}

void TextTreeParser :: findItemStart()
{
//	std :: cout << __PRETTY_FUNCTION__ << std :: endl;

	if (isdigit(_text[_pos])) {
		_nextItemStart = _pos;
		_state = FA :: Find_Item_Stop;
	}
	else if (_text[_pos] != '.' && !isspace(_text[_pos])) {
		_state = FA :: Find_Data_Stop;
	}
}

void TextTreeParser :: findItemStop()
{
//	std :: cout << __PRETTY_FUNCTION__ << std :: endl;

	if (isspace(_text[_pos])) {
		// case in start position
		if (_item.first != _text.npos) {
			// show, dump it
//			std :: cout << "item: " << _text.substr(_item.first, _item.second - _item.first) << std :: endl;
//			std :: cout << "data: " << _text.substr(_data.first, _data.second - _data.first) << std :: endl;
			putData(_text.substr(_item.first, _item.second - _item.first),  _text.substr(_data.first, _data.second - _data.first));
		}

		_item.first = _nextItemStart;
		_item.second = _pos;
		_state = FA :: Find_Data_Start;
	}
	else if (_text[_pos] != '.' && !isdigit(_text[_pos])) {
		_nextItemStart = _text.npos;
		_state = FA :: Find_Data_Stop;
	}
}

void TextTreeParser :: findDataStart()
{
//	std :: cout << __PRETTY_FUNCTION__ << std :: endl;

	if (!isspace(_text[_pos])) {
		_data.first = _pos;
		_state = FA :: Find_Data_Stop;
	}
}

/**
 * \note Potential stop
 */
void TextTreeParser :: findDataStop()
{
//	std :: cout << __PRETTY_FUNCTION__ << std :: endl;

	if (isspace(_text[_pos])) {
		_data.second = _pos;
		_state = FA :: Find_Item_Start;
	}
}

void TextTreeParser :: putData(const std :: string && key, const std :: string && value)
{
	Unit * u = &_tree;

	std :: size_t digit = key.npos;

//	std :: cout << "parse key = \"" << key << "\"" << std :: endl;
	for (std :: size_t i = 0; i < key.length(); ++i) {
		if (isdigit(key[i])) {
			if (digit == key.npos)
				digit = i;
		}
		else if (digit != key.npos) {
			int d = atoi(&key[digit]);
//			std :: cout << d << std :: endl;
			u = &u->_child[d];
			digit = key.npos;
		}
	}

	if (digit != key.npos) {
		int d = atoi(&key[digit]);
//		std :: cout << "last = " << d << std :: endl;
		u = &u->_child[d];
		digit = key.npos;
	}

//	std :: cout << "push = " << value << std :: endl;

	u->_value.push_back(value);
}

/**********************************************************
 * \brief   Balance parenthes
 * \details Speed = O(N), Memory = O(1)
 **********************************************************/
void balance_parentheses(std :: string &s)
{
	// O(N)
	auto balance = [&s](char plusCh, char minusCh) {
		size_t i = 0, real_i = 0;
		int balance = 0;

		while (real_i < s.length()) {
			// replace
			s[i] = s[real_i];

			if (s[i] == plusCh)
				++balance;
			else if (s[i] == minusCh) {
				if (balance == 0) {
					++real_i;
					continue;
				}
				--balance;
			}

			++i;
			++real_i;
		}

		// O(1)
		s.resize(i);
	};

	balance('(', ')');

	// O(N)
	std :: reverse(s.begin(), s.end());

	balance(')', '(');

	// O(N)
	std :: reverse(s.begin(), s.end());
}

} /** namespace conq_string */

StringTask::StringTask() {

}

StringTask::~StringTask() {
}


/** +++ REVERT ALL WORDS IN A STRING +++ */

bool RevertWordsInString :: doTask(int argc, char ** argv)
{
	if (argc < 2) {
		usage(*argv);
		return false;
	}

	std :: size_t len = strnlen(argv[1], MaxStringLen);
	if (len == MaxStringLen) {
		std :: cout << "invalid string len more than " << MaxStringLen << std :: endl;
		return false;
	}

	doTask(argv[1], len);
	std :: cout << std :: endl;
	doTaskWithStlString(argv[1], len);
	std :: cout << std :: endl;
	doTaskUsingRevertFunc(argv[1], len);

	return true;
}

static inline
void getSubStringLex(const char * str, std :: size_t len, std :: size_t pos, std :: size_t & seqLen, bool space)
{
	seqLen = 0;
	std :: locale loc;

	for (; pos < len; pos++) {
		if (std :: isspace(str[pos], loc) == space) {
			break;
		}

		seqLen++;
	}
}

void RevertWordsInString :: doTask(char * str, std :: size_t len)
{
	std :: cout << __func__ << ": src = \"" << str << "\"" << std :: endl;

	boost :: scoped_array<char> dst(new char[len + 1]);
	dst[len] = 0;

	std :: locale loc;
	std :: size_t pos = 0, seq_len = 0;
	bool space = !std :: isspace(str[0], loc);

	while (pos < len) {
		getSubStringLex(str, len, pos, seq_len, space);
		space = !space;
		strncpy(&dst[len - pos - seq_len], &str[pos], seq_len);
		pos += seq_len;
	}

	std :: cout << __func__ << ": dst = \"" << dst.get() << "\"" << std :: endl;
}

/**
 * simplify without space replacement
 */
void RevertWordsInString :: doTaskWithStlString(char * str, std :: size_t len)
{
	std :: cout << __func__ << ": src = \"" << str << "\"" << std :: endl;

	std :: vector<std :: string> words;

	boost :: algorithm :: split(words, str, boost :: is_any_of("\t "));
	int lex_num = words.size();

	for (int i = 0; i < (lex_num / 2); i++) {
		std :: swap(words[i], words[lex_num - i - 1]);
	}

	std :: string dst;
	for (int i = 0; i < lex_num; i++) {
		dst += words[i];

		if (i + 1 < lex_num) {
			dst += ' ';
		}
	}

	std :: cout << __func__ << ": dst = \"" << dst << "\"" << std :: endl;
}

// (ie. input:"abc def ghi" output:"ghi def abc")
void RevertWordsInString :: doTaskUsingRevertFunc(char * str, std :: size_t len)
{
	std :: string s = str;

	std :: cout << __func__ << ": src = \"" << s << "\"" << std :: endl;

	RevertString :: revert(s);

	std :: vector<std :: string> words;

	boost :: algorithm :: split(words, s, boost :: is_any_of("\t "));

	int word_num = words.size();

	std :: string d;

	for (int i = 0; i < word_num; i++) {
		if (words[i].empty()) {
			d += ' ';
		} else {
			RevertString :: revert(words[i]);
			d += words[i];
			d += ' ';
		}
	}

	std :: cout << __func__ << ": dst = \"" << d << "\"" << std :: endl;
}

/** --- REVERT ALL WORDS IN A STRING --- */

/** +++ PRINT UNIQ STRING +++ */

void UniqStringPrint :: printUniq(char ** str, int len)
{
	for (int i = 0; i < len; i++) {
		bool uniq = true;
		for (int j = i + 1; j < len; j++) {
			if (strcmp(str[i], str[j]) == 0) {
				uniq = false;
				break;
			}
		}

		if (uniq) {
			std :: cout << " " << str[i];
		}
	}
}

bool UniqStringPrint :: doTask(int argc, char ** argv)
{
	if (argc < 2) {
		usage(argv[0]);
		return false;
	}

	std :: cout << "uniq :";

	printUniq(argv + 1, argc - 1);

	std :: cout << std :: endl;

	return true;
}

/** --- PRINT UNIQ STRING --- */

/** +++ REVERT STRING +++ */

bool RevertString :: doTask(int argc, char ** argv)
{
	if (argc < 2) {
		usage(*argv);
		return false;
	}

	if (strnlen(argv[1], MaxStringLen) == MaxStringLen) {
		std :: cout << "to long input string length, max = " << MaxStringLen << std :: endl;
		return false;
	}

	std :: string str = argv[1];

	std :: cout << "src: \"" << str << "\"" << std :: endl;

	revert(str);

	std :: cout << "dst: \"" << str << "\"" << std :: endl;

	return true;
}

void RevertString :: revert(std :: string & str)
{
	int hi = str.length() - 1, half = str.length() / 2;
	for (int i = 0; i < half; i++) {
		std :: swap(str[i], str[hi - i]);
	}
}


/** -- REVERT STRING -- */

/** +++ UNIQUE SYMBOL +++ */

bool FindFirstUniqueSym :: doTask(int argc, char ** argv)
{
	if (argc != 2) {
		usage(*argv);
		return false;
	}

	char * str = argv[1];
	int len = strnlen(str, MaxStringLen);

	std :: cout << "find first unique symbol in the string: \"" << str <<
		"\", len = " << len << std :: endl;

	int sym = -1;
	for (int i = 0; i < len; i++) {
		if ((strchr(str, str[i]) == &str[i]) &&
		    (strrchr(&str[i + 1], str[i]) == NULL)) {
			sym = i;
			break;
		}
	}

	if (sym < 0) {
		std :: cout << "symbol not found\n";
	} else {
		std :: cout << "first unique symbol is \"" << argv[1][sym] << "\"" << std :: endl;
	}

	return true;
}

/** --- UNIQUE SYMBOL --- */

