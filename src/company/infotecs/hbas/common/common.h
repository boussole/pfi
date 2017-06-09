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
 * \file      common.h
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/
#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include <common/protocol.h>
#include <common/factorization.h>

#define MEM_FN(x) std :: bind(&self_type :: x, shared_from_this())
#define MEM_FN_1(x) std :: bind(&self_type :: x, shared_from_this(), std :: placeholders :: _1)
#define MEM_FN_2(x) std :: bind(&self_type :: x, shared_from_this(), std :: placeholders :: _1, std :: placeholders :: _2)

namespace common {

	/**
	 * \brief String to int
	 */
	static inline
	bool str_to_int(const char *str, int min, int max, int &val)
	{
		char * endptr = nullptr;

		val = strtol(str, &endptr, 10);
		if ((endptr && *endptr) || (val < min || val > max)) {
			std :: cout << "skip invalid value [" << min << " .. " << max << "]: " << val << std :: endl;
			return false;
		}

		return true;
	}

	/**
	 * \brief Log boost error
	 */
	inline void log_error(const char *fn, const boost::system::error_code &error) {
		std :: cerr << std :: endl << fn << ": fail (" << error.message() << ")\n";
	}

	/**
	 * \brief Log custom error
	 */
	inline void log_error(const char *fn, const char *msg) {
		std :: cerr << std :: endl << fn << ": (" << msg << ")\n";
	}

} /** namespace common */

#endif /* COMMON_COMMON_H_ */
