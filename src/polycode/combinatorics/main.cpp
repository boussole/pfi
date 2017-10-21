/**
 * \file   main.cpp
 * \brief
 * \author boussole
 */

#include "combinatorics.h"

using namespace std;
using namespace conq_combinatorics;

TICKET_FN(307)
{
	cout << "#" << ticket << ": permutation\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <N>\n";
		return;
	}

	int n = atoi(argv[1]);
	if (n <= 0) {
		cout << "invalid N\n";
		return;
	}

	permutation_R(static_cast<std :: size_t>(n), [=](std :: unique_ptr<std :: size_t[]> & perm) {
		for (int i = 0; i < n; ++i)
			cout << " " << perm[i];
		cout << endl;
	});
}

TICKET_FN(308)
{
	cout << "#" << ticket << ": next permutation\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <N> [ <steps> ]\n";
		return;
	}

	int n = atoi(argv[1]), steps = 0;
	if (n <= 0 || steps < 0) {
		cout << "invalid N or steps\n";
		return;
	}

	if (argc == 3) {
		steps = atoi(argv[2]);
		if (steps <= 0) {
			cout << "invalid steps\n";
			return;
		}
	}

	if (steps == 0) {
		permutation_I(n, [=](std :: unique_ptr<std :: size_t[]> & perm) {
			for (int i = 0; i < n; ++i)
				cout << " " << perm[i];
			cout << endl;
		});

		return;
	}

	std :: unique_ptr<std :: size_t[]> perm(new std :: size_t[n]);

	// fill basic
	std :: size_t val = 1;
	for (int i = 0; i < n; ++i) {
		perm[i] = val++;
		cout << " " << perm[i];
	}
	cout << endl;

	for (int i = 0; i < steps; ++i) {
		if (!nextPermutation(perm, static_cast<std :: size_t>(n))) {
			cout << "no more permutation\n";
			break;
		}

		for (int i = 0; i < n; ++i)
			cout << " " << perm[i];
		cout << endl;
	}
}

TICKET_FN(309)
{
	cout << "#" << ticket << ": sets\n";

	if (argc < 2) {
		cout << "usage: " << *argv << " <N>\n";
		return;
	}

	int n = atoi(argv[1]);
	if (n <= 0) {
		cout << "invalid N\n";
		return;
	}

	makeFullSet(n, [=](unique_ptr<std :: size_t[]> & subset, std :: size_t sz) {
		cout << "{";
		for (size_t i = 0; i < sz; ++i)
			cout << " " << subset[i];
		cout << " }\n";
	});
}

TICKET_FN(120)
{
	cout << "#" << ticket << ": combinations\n";

	if (argc < 3) {
		cout << "usage: " << *argv << " <N> <K-th>\n";
		return;
	}

	int n = atoi(argv[1]), k = atoi(argv[2]);
	if (n < 0) {
		cout << "invalid n\n";
		return;
	}

	if (k < 0 || n < k) {
		cout << "invalid k\n";
		return;
	}

	combinations(n, k, [=](unique_ptr<std :: size_t[]> & subset) {
		cout << "{";
		for (int i = 0; i < k; ++i)
			cout << " " << subset[i];
		cout << " }\n";
	});
}

int main(int argc, char * argv[])
{
	/* uncomment one of them */

	// ticket_120(argc, argv);

	// ticket_309(argc, argv);

	// ticket_308(argc, argv);

	// ticket_307(argc, argv);

	return 0;
}
