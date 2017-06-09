/****************************************************************
 * Copyright (c) 2016 boussole (x dotty conquistador dotty at gmail com)
 * All rights reserved.
 *
 * This file is part of hbas.
 *
 * Hbas is free software: you can redistribute it and/or modify
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
 * https://github.com/boussole/hbas
 *
 * \file      factorizaton.h
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/

#ifndef COMMON_FACTORIZATION_H_
#define COMMON_FACTORIZATON_H_

#include <vector>
#include <cstdint>
#include <list>

namespace factorization_details {

/**
 * \brief Implementation interface
 */
class impl {
public:
	impl() = delete;

	impl(const impl &) = delete;

	impl(impl &&) = delete;

	~impl() = delete;

	static void preprocess(std :: size_t high);

	static bool is_prime();

	static std :: size_t next(std :: size_t);
};

/**
 * \brief   Implementation is based no one-to-one principal: "value" <=> "flag"
 * \details Vector contains all numbers in [0 .. high] and marks them prime or not
 *          +: factorization value prime check with O(1);
 *          -: memory complexity O(high),
 *             but vector<bool> std optimization gives memory size = high / 8;
 *          -: search next element has O(N) in worst case depends on interval
 */
class impl_1 : public impl {
public:
	/**
	 * \brief Preprocessing - generate vector marked primes values within
	 *        (based on https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)
	 */
	static void preprocess(std :: size_t high);

	/**
	 * \brief   Check prime of value
	 * \details O(1)
	 */
	static bool is_prime(std :: size_t value);

	/**
	 * \brief   Find next prime number
	 * \details O(N)
	 */
	static std :: size_t next(std :: size_t value);

private:
	static std :: vector<bool> _sieve;
};

/**
 * \brief   Implementation is based no one-to-one principal: "value" <=> "offset to the nearest prime"
 * \details Vector contains all numbers in [0 .. high] and contains offset to the nearest prime
 *          +: factorization value prime check with O(1);
 *          +: search next prime value with O(1)
 *          -: memory complexity O(high)
 */
class impl_2 : public impl {
public:
	/**
	 * \brief Preprocessing - generate vector marked primes values within
	 *        (based on https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)
	 */
	static void preprocess(std :: size_t high);

	/**
	 * \brief   Check prime of value
	 * \details O(1)
	 */
	static bool is_prime(std :: size_t value);

	/**
	 * \brief   Find next prime number
	 * \details O(1)
	 * \return  Next prime number | -1 (MAXIMAX size_t)
	 */
	static std :: size_t next(std :: size_t value);

private:
	static std :: vector<std :: uint8_t> _sieve;
};

} /** namespace factorization_details */

/**
 * \class   factorization
 * \brief   Factorization of number
 * \details Static class
 */
template <typename implementation>
class factorization : /*private*/ public implementation
{
public:
	/**
	 * \brief   Do preprocess
	 * \details Using static maximal value == 65535
	 * \note    Fixed high border in this version
	 */
	static void init()
	{
		implementation :: preprocess(0xFFFF);
	}

	/**
	 * \brief  Factorize value
	 */
	static size_t decompose(std :: uint16_t value, std :: list<std :: uint16_t> &result)
	{
		std :: uint16_t divider = 2;

		while (!implementation :: is_prime(value)) {
			std :: uint16_t r = value % divider;

			while (static_cast<std :: int32_t>(r) > 0) {
				divider = implementation :: next(divider);
				r = value % divider;
			}

			result.push_back(divider);
			value = value / divider;
			divider = 2;
		}

		result.push_back(value);

		return result.size();
	}
};

#endif /* COMMON_FACTORIZATION_H_ */
