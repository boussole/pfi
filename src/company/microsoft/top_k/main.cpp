/****************************************************************
 * Copyright (c) 2016 boussole (x dotty conquistador dotty x at gmail dotty com)
 * All rights reserved.
 *
 * This file is part of top_k.
 *
 * top_k is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * https://github.com/boussole/top_k
 *
 * \file      main.cpp
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/

#include <sstream>
#include <iterator>
//-
#include "top_k_buff.h"

using namespace std;

/**
 * \brief   Test basic top_k policy
 */
void __test_top_k()
{
	std :: cout << "======================================\n"
	            << __PRETTY_FUNCTION__ << ": " << "k b a d a a b b c c d u"
	            << "\n======================================\n";

	top_k<4> tk;

	// 1. storage is empty
	// add "k"
	tk.add("k");
	// output: freq = 1: k
	// result: added new element "k" with frequency = 1
	tk.debug();

	// 2. storage contains "k" with frequency = 1
	// add "b"
	tk.add("b");
	// output: freq = 1: b k
	// result: added new element "b" with frequency = 1, "k" is older than "b"
	tk.debug();

	// 3. storage contains "b" and "k" with frequency = 1
	// add "a"
	tk.add("a");
	// output: freq = 1: a b k
	// result: added new element "a" with frequency = 1, "b" is older than "a", "k" is older than "b"
	tk.debug();

	// 4. storage contains "a", "b" and "k"
	// add "d"
	tk.add("d");
	// output: freq = 1: d a b k
	// result: added new element "d" with frequency = 1, ..., k is the oldest element with frequency = 1
	tk.debug();

	// 5. storage is full (and below also): "d" "a" "b" "k"
	// add NOT NEW element "a" => updating frequency of "a"
	tk.add("a");
	// output:
	// freq = 2: a
	// freq = 1: d b k
	// result:
	// - update "a" frequency = 2;
	// - "a" is alone and the youngest element in frequency = 2 group;
	// - k is the oldest element with frequency = 1 (candidate to remove)
	tk.debug();

	// 6. storage:
	//             freq = 2: "a"
	//             freq = 1: "d" "b" "k"
	// add NOT NEW element "a" => updating frequency of "a"
	tk.add("a");
	// output:
	// freq = 3: a
	// freq = 1: d b k
	tk.debug();

	// 7. storage:
	//             freq = 3: a;
	//             freq = 1: d b k
	// add NOT NEW element "b" => updating frequency of "b" (gap test)
	tk.add("b");
	// output:
	// freq = 3: a
	// freq = 2: b
	// freq = 1: d k
	tk.debug();

	// 8. storage:
	//             freq = 3: a
	//             freq = 2: b
	//             freq = 1: d k
	// add NOT NEW element "b" => updating frequency of "b" (move to higher group)
	tk.add("b");
	// output:
	// freq = 3 (size = 2): b a
	// freq = 1 (size = 2): d k
	tk.debug();

	// 9. storage:
	//            freq = 3 (size = 2): b a
	//            freq = 1 (size = 2): d k
	// add NEW element "c" => replacing the oldest element with frequency = 1 ("k")
	tk.add("c");
	// output:
	// freq = 3 (size = 2): b a
	// freq = 1 (size = 2): c d
	// d - is the oldest with minumal frequency, k was dropped
	tk.debug();

	// 10-11. storage
	//             freq = 3 (size = 2): b a
	//             freq = 1 (size = 2): c d
	// Increase frequency for "c" and "d"
	tk.add("c");
	tk.add("d");
	// output:
	// freq = 3 (size = 2): b a
	// freq = 2 (size = 2): d c
	// "c" is the oldest element with frequency = 2
	tk.debug();

	// 12. storage
	//           freq = 3 (size = 2): b a
	//           freq = 2 (size = 2): d c
	// add NEW element "u"
	tk.add("u");
	// output
	//           freq = 3 (size = 2):  b a
	//           freq = 2 (size = 1):  d
	//           freq = 1 (size = 1):  u
	tk.debug();

	std :: cout << "======================================\n"
	            << "result:";
	for (auto i : tk)
		std :: cout << " " << i;
	std :: cout << "\n======================================\n";

	tk.clear();

	// another example
	std :: cout << "======================================\n"
	            << __PRETTY_FUNCTION__ << ": " << "k b a d a c b u a c u d"
	            << "\n======================================\n";

	// k b a d a c b u
	tk.add("k");
	tk.debug();
	tk.add("b");
	tk.debug();
	tk.add("a");
	tk.debug();
	tk.add("d");
	tk.debug();
	tk.add("a");
	tk.debug();
	tk.add("c");
	tk.debug();
	tk.add("b");
	tk.debug();
	tk.add("u");
	tk.debug();
	// output
	// freq = 2 (size = 2): b a
	// freq = 1 (size = 2): u c

	// a c u d
	tk.add("a");
	tk.debug();
	tk.add("c");
	tk.debug();
	tk.add("u");
	tk.debug();
	tk.add("d");
	tk.debug();
	// output
	// freq = 3 (size = 1): a
	// freq = 2 (size = 2): u c
	// freq = 1 (size = 1): d

	std :: cout << "======================================\n"
	            << "result:";
	for (auto i : tk)
		std :: cout << " " << i;
	std :: cout << "\n======================================\n";
}

/**
 * \brief Test top_k_buff
 */
void __test_top_k_buff()
{
	top_k_buff<4, 4> tkb;

	std :: cout << "======================================\n"
	            << __PRETTY_FUNCTION__ << ": k b a d a b k d u stub1 u u"
	            << "\n======================================\n";
	// k b a d a c b u

	// storage: empty
	// add new
	tkb.add("k");
	// output
	// freq = 1 (size = 1): k
	// buf: k
	tkb.debug();

	// storage:
	//          freq = 1 (size = 1): k
	// add new
	tkb.add("b");
	// output
	// freq = 1 (size = 2): b k
	// buf: k b
	tkb.debug();

	// storage:
	//          freq = 1 (size = 2): b k
	// add new
	tkb.add("a");
	// output
	// freq = 1 (size = 3): a b k
	// buf: k b a
	tkb.debug();

	// storage:
	//         freq = 1 (size = 3): a b k
	// add new
	tkb.add("d");
	// output
	// freq = 1 (size = 4): d a b k
	// buf: k b a d
	tkb.debug();

	// storage (full since this moment):
	//         freq = 1 (size = 4): d a b k
	// update "a"
	tkb.add("a");
	// output
	// freq = 2 (size = 1): a
	// freq = 1 (size = 3): d b k
	// buf: b a d a
	tkb.debug();

	/** !!! the difference between top_k starts here !!!*/
	// storage:
	//         freq = 2 (size = 1): a
	//         freq = 1 (size = 3): d b k
	// let's update all elements with frequency = 1 to frequency = 2
	tkb.add("b");
	tkb.add("k");
	tkb.add("d");
	// output
	// freq = 2 (size = 4): d k b a
	// buf: a b k d
	tkb.debug();

	// storage
	//         freq = 2 (size = 4): d k b a
	// try to add new element "u", candidate for replacing is "a"
	tkb.add("u");
	// output
	// freq = 2 (size = 4): d k b a
	// buf: b k d u
	// NO effect, cause frequency of the oldest element is 2, BUT "u" is situated in the buffer
	tkb.debug();

	// storage:
	//         freq = 2 (size = 4): d k b a
	// lets do the same operation with another 1 strings to check
	tkb.add("stub1");
	// output
	// freq = 2 (size = 4): d k b a
	// buf: k d u stub1
	// STILL no effect, but "u" is still in the buffer
	tkb.debug();

	// storage:
	//          freq = 2 (size = 4): d c b a
	// let's add twice "u" again to increase quantity to 3
	tkb.add("u");
	tkb.add("u");
	// output
	// freq = 3 (size = 1): u
	// freq = 2 (size = 3): d k b
	// buf: u stub1 u u
	// TADAM!!! "u" has the frequency higher then the oldest element
	tkb.debug();

	std :: cout << "======================================\n"
	            << "result:";
	for (const auto& i : tkb)
		std :: cout << " " << i;
	std :: cout << "\n======================================\n";
}

/**
 * \brief Example link
 *        http://www.geeksforgeeks.org/find-the-k-most-frequent-words-from-a-file/
 */
void __test()
{
	top_k<50> tk;

	string s = "Welcome to the world of Geeks "
               "This portal has been created to provide well written well thought and well explained "
               "solutions for selected questions If you like Geeks for Geeks and would like to contribute "
               "here is your chance You can write article and mail your article to contribute at "
               "geeksforgeeks org See your article appearing on the Geeks for Geeks main page and help "
               "thousands of other Geeks";

	istringstream buf(s);

	istream_iterator<std::string> beg(buf), end;

	vector<string> tokens(beg, end);

	for(auto& i: tokens) {
		tk.add(i);
	}

	tk.debug();

//	std :: cout << "======================================\n"
//	            << "result:";
//	for (auto i : tk)
//		std :: cout << " " << i;
//	std :: cout << "\n======================================\n";
}

int main(int argc, char * argv[])
{
	__test();

//	__test_top_k();
//
//	__test_top_k_buff();

	return 0;
}
