/**
 * \file    extremum_search.h
 * \brief
 * \details
 * \author  conquistador
 */
#ifndef EXTREMUM_SEARCH_EXTREMUM_SEARCH_H_
#define EXTREMUM_SEARCH_EXTREMUM_SEARCH_H_

#include <vector>
#include <assert.h>

/**
 * \brief   Naive extremum search
 * \details Speed       = O(N)
 *          Comparison  = (N - 2) * 2 + 2 (with last assert)
 */
std :: size_t extremum_search_naive(std :: vector<int> &v);

/**
 * \brief   Dichotomy extremum search
 * \details Speed      = O(logN)
 *          Comparison = 2 * logN + 1
 */
std :: size_t extremum_search_dichotomy(std :: vector<int> &v);

#endif /* EXTREMUM_SEARCH_EXTREMUM_SEARCH_H_ */
