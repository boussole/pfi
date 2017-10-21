/**
 * \file    main.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include "common/common.h"
#include "memory.h"

using namespace std;
using namespace conq_mem;

TICKET_FN(51)
{
	cout << "#" << ticket << ": alignment allocator\n";

	const int max_align_value = 256;

	int align = 0;

	if ((argc > 1) && ((align = atoi(argv[1])) > 0)) {
		if (align > max_align_value) {
			std :: cout << "max align val == " << max_align_value << std :: endl;
			return;
		}

		cout << "alignment: " << align << endl;
		void * ptr = AllocAlign(20, align);
		assert(((uintptr_t)ptr % align) == 0);
		FreeAlign(ptr);

		return;
	}

	/* test with alignment [1..255] */
	for (align = 1; align < max_align_value; ++align) {
		cout << "alignment: " << align << endl;

		void * ptr = AllocAlign(20, align);
		assert(((uintptr_t)ptr % align) == 0);
		FreeAlign(ptr);
	}
}

int main(int argc, char ** argv)
{
	ticket_51(argc, argv);

	return 0;
}
