/**
 * \file    matrix.cpp
 * \brief
 * \details
 * \author  boussole
 */

#include "matrix.h"

namespace conq_matrix {

/*************************************************************
 * \brief  #63: Find celebrety if it exists
 *
 * \return Celebrety index or -1 if it doesn't exist
 *************************************************************/
int findCelebrety(boost :: numeric :: ublas :: matrix<int> & m, int peopleNum)
{
	int cand = 0;

	// O(N)
	for (int j = 0; j < peopleNum; ++j) {
		if (cand != j) {
			std :: cout << "candidate = " << cand << " pos = (" << cand << ", " << j << ")";
			if (m(cand, j) == 1) {
				std :: cout << " №" << cand << " is not celebrety\n";
				cand = j;
				--j;
			}
			else if (m(cand, j) == 0) {
				std :: cout << " №" << j << " is not celebrety\n";
			}
		}
	}

	std :: cout << "candidate is №" << cand << std :: endl;

	// O(2*N)
	for (int c = 0; c < peopleNum; ++c) {
		if ((c != cand) && (!m(c, cand) || m(cand, c))) {
			std :: cout << "candidate failed in pos (" << c << ", " << cand << ") or ("
			            << cand << ", " << c << ")\n";
			return -1;
		}
	}

	return cand;
}

} /* namespace conq_matrix */
