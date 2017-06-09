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
 * \file      protocol.h
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/
#ifndef COMMON_PROTOCOL_H_
#define COMMON_PROTOCOL_H_

#include <cstdio>
#include <boost/asio.hpp>
#include <string>
#include <list>

#ifdef __GNUC__
#	define PACKED(p) p __attribute__((__packed__))
#else
#	define PACKED(p) __pragma(pack(push, 1)) p __pragma(pack(pop))
#endif

namespace protocol {

	namespace binary {

		/**
		 * \struct req_hdr
		 * \brief  Header of request
		 */
		PACKED (
			struct req_hdr {
				std :: uint16_t _value;
			}
		);

		/**
		 * \struct resp_hdr
		 * \brief  Header of response full
		 */
		PACKED (
			struct resp_hdr {
				std :: uint16_t _value;
				std :: uint16_t _code;
				std :: uint16_t _quantity;
				std :: uint16_t _result[];
			}
		);

	} /** namespace binary */

	namespace text {

		constexpr size_t VALUE_SZ       = 4;
		constexpr size_t CODE_SZ        = 4;
		constexpr size_t QUANTITY_SZ    = 4;
		constexpr size_t RESULT_UNIT_SZ = 4;

		/**
		 * \struct req_hdr
		 * \brief  Header of request
		 */
		PACKED (
			struct req_hdr {
				std :: uint8_t _value[VALUE_SZ];
			}
		);

		/**
		 * \struct resp_hdr
		 * \brief  Header of response full
		 */
		PACKED (
			struct resp_hdr {
				std :: uint8_t _value[VALUE_SZ];
				std :: uint8_t _code[CODE_SZ];
				std :: uint8_t _quantity[QUANTITY_SZ];
				std :: uint8_t _result[];
			}
		);

	} /** namespace text */

#ifdef BINARY_PROTOCOL
	constexpr std :: size_t RESULT_UNIT_SZ = binary :: RESULT_UNIT_SZ;
	using req_hdr = binary :: req_hdr;
	using resp_hdr = binary :: resp_hdr;
#else
	constexpr std :: size_t RESULT_UNIT_SZ = text :: RESULT_UNIT_SZ;
	using req_hdr = text :: req_hdr;
	using resp_hdr = text :: resp_hdr;
#endif

	constexpr std :: size_t REQUEST_SZ = sizeof(req_hdr);
	constexpr std :: size_t RESPONSE_SZ = sizeof(resp_hdr);

	/**
	 * \enum Server response codes
	 */
	enum class code {
		OK = 0,
		ERROR,
		__MAX
	};

	/**
	 * \brief  Serialize request
	 * \return Bytes for transmit
	 */
	std :: size_t serial_req(std :: uint16_t value, std :: string &req);

	/**
	 * \brief Deserialize request
	 */
	void deserial_req(boost :: asio :: streambuf &buf, binary :: req_hdr &req);

	/**
	 * \brief  Serialize response
	 * \return Bytes for transmit
	 */
	std :: size_t serial_resp(std :: uint16_t value, code c,
	                          const std :: list<std :: uint16_t> &result,
	                          boost :: asio :: streambuf &buf);

	/**
	 * \brief Deserialize response header
	 * \todo  Add protocol error detection
	 */
	void deserial_resp_hdr(boost :: asio :: streambuf &buf, binary :: resp_hdr &resp);

	/**
	 * \brief Deserialize response payload
	 */
	void deserial_resp_payload(boost :: asio :: streambuf &buf, std :: size_t quantity, std :: list<std :: uint16_t> &result);

}; /** namespace protocol */

#undef PACK

#endif /* COMMON_PROTOCOL_H_ */
