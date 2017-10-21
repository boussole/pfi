/**
 * \file    common.h
 * \brief   Common including files and useful functions
 * \details
 * \author  boussole
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <cstdint>
#include <cstddef>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <list>
#include <queue>
#include <stack>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include <functional>
#include <random>
#include <fstream>
#include <memory>
#include <unistd.h>

// boost
#ifdef NEED_BOOST_BASIC
#	include <boost/noncopyable.hpp>
#	include <boost/function.hpp>
#	include <boost/scoped_array.hpp>
#	include <boost/bind.hpp>
#	include <boost/math/special_functions/factorials.hpp>
#endif /** NEED_BOOST_BASIC */

#ifdef NEED_BOOST_UBLAS
#	include <boost/numeric/ublas/matrix.hpp>
#	include <boost/numeric/ublas/io.hpp>
#	include <boost/geometry.hpp>
#	include <boost/geometry/geometries/point_xy.hpp>
#endif /** NEED_BOOST_UBLAS */

/**
 * Function definition for ticket
 */
#define TICKET_FN(num) \
	void ticket_##num(int argc, char ** argv, const size_t ticket = num)

/**
 * Array size
 */
#define ARRAY_SIZE(arr) sizeof(arr) / sizeof(arr[0])

namespace conq_common {

/**
 * \brief minimal of three
 */
template <typename T>
T min3(const T & x, const T & y, const T & z)
{
	return std :: min(x, std :: min(y, z));
}

} /** namespace conq_common */

#endif /* COMMON_H_ */
