/**
 * \file algorithm.h
 * \brief
 * \details
 * \author boussole
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <common/common.h>

namespace conq_algo {

/*********************************************************
 * \brief Build matrix and calc longest common subsequence
 *********************************************************/
template <typename T>
std :: size_t buildLongestCommonSubsequence(boost :: numeric :: ublas :: matrix<int> & m,
                                   T * left, std :: size_t lLen, T * right, std :: size_t rLen)
{
	std :: size_t rows = lLen + 1, cols = rLen + 1;
	m.resize(rows, cols);

	/** set empty sequence to zero */
	for (std :: size_t i = 0; i < rows; i++) m(i, 0) = 0;
	for (std :: size_t j = 1; j < cols; j++) m(0, j) = 0;

	for (std :: size_t i = 1, l_idx = 0; i < rows; i++, l_idx++)
		for (std :: size_t j = 1, r_idx = 0; j < cols; j++, r_idx++) {
			m(i, j) = (left[l_idx] == right[r_idx]) ? m(i - 1, j - 1) + 1 : std :: max(m(i - 1, j), m(i, j - 1));
		}

	return m(rows - 1, cols - 1);
}

/**********************************************************
 * \brief Backtracking diff
 *********************************************************/
template <typename T, typename Function>
void diffLCS(boost :: numeric :: ublas :: matrix<int> & m, T * left, T * right, std :: size_t i, std :: size_t j,
             Function leftDel, Function rightAdd, Function common)
{
	if ((i == 0) && (j == 0)) return;

	if ((i > 0) && (j > 0) && (left[i - 1] == right[j - 1])) {
		diffLCS(m, left, right, i - 1, j - 1, leftDel, rightAdd, common);
		common(left[i - 1]);
	}
	else if ((i > 0) && ((j == 0) || (m(i - 1, j) >= m(i, j - 1)))) {
		diffLCS(m, left, right, i - 1, j, leftDel, rightAdd, common);
		leftDel(left[i - 1]);
	}
	else if ((j > 0) && ((i == 0) || (m(i - 1, j) < m(i, j - 1)))) {
		diffLCS(m, left, right, i, j - 1, leftDel, rightAdd, common);
		rightAdd(right[j - 1]);
	}
}

/*********************************************************
 * \brief Simple interface to search diff
 *********************************************************/
template <typename T, typename Function>
void diffLongestCommonSubsequence(boost :: numeric :: ublas :: matrix<int> & m, T * left, T * right,
                                  Function del, Function add, Function common)
{
	diffLCS(m, left, right, m.size1() - 1, m.size2() - 1, del, add, common);
}


/********************************************************
 * \brief Prime detect
 ********************************************************/
static inline
bool isPrime(int val)
{
	if (val == 1)
		return true;

//	for (int i = 2; i <= val / 2; val++) {
	for (int i = 2; i * i <= val; ++i) {
		if (val % i == 0)
			return false;
	}

	return true;
}

} /* conq_algo */

#endif /* ALGORITHM_H_ */
