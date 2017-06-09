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
 * \file      factorizaton.cpp
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/

#include <iostream>
#include <assert.h>

#include "factorization.h"

namespace factorization_details {

/******************************************************************
 *                           impl_1
 ******************************************************************/

std :: vector<bool> impl_1 :: _sieve;

/**
 * \brief Preprocessing - generate vector marked primes values within
 *        (based on https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)
 * \note  Fix high border in this version
 */
void impl_1 :: preprocess(std :: size_t high)
{
	impl_1 :: _sieve.resize(high + 1, true);

	impl_1 :: _sieve[0] = true;
	impl_1 :: _sieve[1] = true;
	impl_1 :: _sieve[2] = true;

	std :: size_t i = 2;

	while (i < high) {
		if (impl_1 :: _sieve[i]) {
			for (std :: size_t j = i + i; j <= high; j += i) {
				impl_1 :: _sieve[j] = false;
			}
		}
		++i;
	}

#if 0
	std :: size_t quantity = 0;
	std :: cout << "primes:";
	for (std :: size_t i = 0; i < impl_1 :: _sieve.size(); ++i) {
		if (impl_1 :: _sieve[i]) {
			std :: cout << " " << i;
			++quantity;
		}
	}
	std :: cout << std :: endl << "total = " << quantity << std :: endl;
#endif
}

/**
 * \brief   Check prime of value
 * \details O(1)
 */
bool impl_1 :: is_prime(std :: size_t value)
{
	assert(value < impl_1 :: _sieve.size());

	return impl_1 :: _sieve[value];
}

/**
 * \brief   Find next prime number
 * \details O(N)
 * \return  Next prime number | -1 (MAXIMAX size_t)
 */
std :: size_t impl_1 :: next(std :: size_t value)
{
	while (++value < impl_1 :: _sieve.size()) {
		if (impl_1 :: _sieve[value])
			return value;
	}

	return -1;
}

/******************************************************************
 *                           impl_2
 ******************************************************************/

std :: vector<std :: uint8_t> impl_2 :: _sieve;

/**
 * \brief Preprocessing - generate vector marked primes values within
 *        (based on https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes)
 * \note  Fix high border in this version
 */
void impl_2 :: preprocess(std :: size_t high)
{
	impl_2 :: _sieve.resize(high + 1, 0);

	impl_2 :: _sieve[0] = 0;
	impl_2 :: _sieve[1] = 0;
	impl_2 :: _sieve[2] = 0;

	std :: size_t i = 2;

	while (i < high) {
		if (impl_2 :: _sieve[i] == 0) {

			std :: size_t prev = i - 1;
			std :: uint8_t offset = 1;

			while (impl_2 :: _sieve[prev] != 0) {
				impl_2 :: _sieve[prev--] = offset++;
			}

			for (std :: size_t j = i + i; j <= high; j += i) {
				impl_2 :: _sieve[j] = -1;
			}
		}
		++i;
	}

//	for (size_t k = 0; k < impl_2 :: _sieve.size(); ++k) {
//		std :: cout << "[" << k << "] = " << static_cast<int>(impl_2 :: _sieve[k]) << std :: endl;
//	}
}

/**
 * \brief   Check prime of value
 * \details O(1)
 */
bool impl_2 :: is_prime(std :: size_t value)
{
	assert(value < impl_2 :: _sieve.size());

	return impl_2 :: _sieve[value] == 0;
}

/**
 * \brief   Find next prime number
 * \details O(1)
 * \return  Next prime number | -1 (MAXIMAX size_t)
 */
std :: size_t impl_2 :: next(std :: size_t value)
{
	++value;
	if ((value < impl_2 :: _sieve.size()) && ((impl_2 :: _sieve[value] != -1))) {
		return impl_2 :: _sieve[value] + value;
	}

	return -1;
}

} /* namespace factorization_details */
