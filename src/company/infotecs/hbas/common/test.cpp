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
 * \file      test.cpp
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/

#include <iostream>
#include "factorization.h"

void __testFactorization()
{
//	using factorization = factorization<factorization_details :: impl_1>;

	using factorization = factorization<factorization_details :: impl_2>;

	factorization :: init();

	std :: cout << "10 is prime: " << factorization :: is_prime(10) << std :: endl;

	std :: cout << "13 is prime: " << factorization :: is_prime(13) << std :: endl;

	std :: cout << "15 is prime: " << factorization :: is_prime(15) << std :: endl;

	std :: cout << "print first prime 30 numbers\n";

	size_t counter = 0, value = 1;
	while ((counter++ < 30) && (static_cast<int>(value = factorization :: next(value)) > 0)) {
		std :: cout << " " << value;
	}
	std :: cout << std :: endl;

	std :: list<std :: uint16_t> res;

	std :: cout << "prime dividors of 15 (" << factorization :: decompose(15, res) << "): ";

	for (auto i : res) {
		std :: cout << " " << i;
	}

	std :: cout << std :: endl;

	res.clear();

	std :: cout << "prime dividors of 525 (" << factorization :: decompose(525, res) << "): ";

	for (auto i : res) {
		std :: cout << " " << i;
	}

	std :: cout << std :: endl;

	res.clear();

	std :: cout << "prime dividors of 34 (" << factorization :: decompose(34, res) << "): ";

	for (auto i : res) {
		std :: cout << " " << i;
	}

	std :: cout << std :: endl;
}

int main()
{
	__testFactorization();

	return 0;
}
