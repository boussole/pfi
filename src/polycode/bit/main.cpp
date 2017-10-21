/**
 * \file   main.cpp
 * \author boussole
 */

#include "bit.h"

using namespace std;
using namespace conq_bit;

TICKET_FN(220)
{
	std :: cout << "#" << ticket << std :: endl;

	if (argc < 2) {
		cout << "usage: val\n";
		return;
	}

	unsigned long v = atol(argv[1]);

	cout << "src = " << v << endl;

	int pow = roundPow2(v);

	if (pow < 0) {
		std :: cout << "impossible to round, val is overflow\n";
	}

	cout << "dst = " << v << " (pow = " << pow << ")" << endl;
}

int main(int argc, char ** argv)
{
	ticket_220(argc, argv);

	return 0;

	/** old engine */

	uint32_t val = atoi(argv[1]);

	show_bin(val);

	cout << "setup bits (== 1): " << count_setup_bits(val) << endl;

	replace_neighbor(val);

	show_bin(val);

	cout << "setup bits (== 1): " << count_setup_bits(val) << endl;
}
