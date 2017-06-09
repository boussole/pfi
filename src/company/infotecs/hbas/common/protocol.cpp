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
 * \file      protocol.cpp
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/

#include "protocol.h"

#include <arpa/inet.h>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace protocol {

using namespace boost :: asio;

/**
 * \brief  Serialize request
 * \return Bytes for transmit
 */
std :: size_t serial_req(std :: uint16_t value, std :: string &req)
{
#ifdef BINARY_PROTOCOL
	req.resize(sizeof(req_hdr));

	req_hdr *r = reinterpret_cast<req_hdr *>(const_cast<char*>(req.c_str()));

	r->_value = htons(value);
#else
	std :: stringstream os;

	os << std :: setfill('0') << std :: setw(4) << std :: hex << value;

	req = os.str();

//	std :: cout << __PRETTY_FUNCTION__ << ": value = 0x" << req << std :: endl;
#endif

	return req.size();
}

/**
 * \brief Deserialize request
 */
void deserial_req(streambuf &buf, binary :: req_hdr &req)
{
	assert(buf.in_avail() == protocol :: REQUEST_SZ);

#ifdef BINARY_PROTOCOL

	assert(buf.size() >= sizeof(req_hdr));

	const req_hdr *p_req = reinterpret_cast<const req_hdr *>(detail :: buffer_cast_helper(buf.data()));

	req._value = ntohs(p_req->_value);

	buf.consume(sizeof(req_hdr));

#else /* ! BINARY_PROTOCOL */

	std :: uint16_t value = 0;

	std :: istream is(&buf);

	is >> std :: hex >> value;

	req._value = value;

#endif

//	std :: cout << __PRETTY_FUNCTION__ << ": value = " << req._value << std :: endl;
}

/**
 * \brief Serialize response
 * \return Bytes for transmit
 */
std :: size_t serial_resp(std :: uint16_t value, code c,
                          const std :: list<std :: uint16_t> &result,
                          boost :: asio :: streambuf &buf)
{
#ifdef BINARY_PROTOCOL
	// todo implement it
#else /* ! BINARY_PROTOCOL */

	std :: ostream os(&buf);

	os << std :: setfill('0') << std :: setw(4) << std :: hex << value
	   << std :: setfill('0') << std :: setw(4) << std :: hex << static_cast<std :: uint16_t>(c)
	   << std :: setfill('0') << std :: setw(4) << std :: hex << static_cast<std :: uint16_t>(result.size());

	for (auto i : result) {
		os << std :: setfill('0') << std :: setw(4) << std :: hex << i;
	}

#endif

	return sizeof(resp_hdr) + RESULT_UNIT_SZ * result.size();
}

/**
 * \brief Deserialize response header
 * \todo  Add protocol error detection
 */
void deserial_resp_hdr(boost :: asio :: streambuf &buf, binary :: resp_hdr &resp)
{ // std :: cout << __PRETTY_FUNCTION__ << &buf << std :: endl;
#ifdef BINARY_PROTOCOL

	// todo implement it

#else /* ! BINARY_PROTOCOL */

	std :: istream is(&buf);
	char hdr_buf[protocol :: RESPONSE_SZ + 1] = "";
	is.get(hdr_buf, protocol :: RESPONSE_SZ + 1);
	protocol :: text :: resp_hdr *resp_hdr = reinterpret_cast<protocol :: text :: resp_hdr *>(hdr_buf);

	char *endptr = nullptr;
	resp._value = strtol(std::string(reinterpret_cast<char*>(resp_hdr->_value), protocol :: text :: VALUE_SZ).c_str(), &endptr, 16);
	resp._code = strtol(std::string(reinterpret_cast<char*>(resp_hdr->_code), protocol :: text :: CODE_SZ).c_str(), &endptr, 16);
	resp._quantity = strtol(std::string(reinterpret_cast<char*>(resp_hdr->_quantity), protocol :: text :: CODE_SZ).c_str(), &endptr, 16);

#endif

//	std :: cout << __PRETTY_FUNCTION__ << ": value = " << resp._value << "; code = " << resp._code << "; quantity = " << resp._quantity << std :: endl;
}

/**
 * \brief Deserialize response payload
 */
void deserial_resp_payload(boost :: asio :: streambuf &buf, std :: size_t quantity, std :: list<std :: uint16_t> &result)
{ //std :: cout << __PRETTY_FUNCTION__ << ": " << &buf << std :: endl;

	assert(static_cast<std :: size_t>(buf.in_avail()) == quantity * RESULT_UNIT_SZ);

	std :: istream is(&buf);
	char res[protocol :: RESULT_UNIT_SZ + 1];
	char *endptr = nullptr;
	while (is.get(res, sizeof(res))) {
		result.push_back(static_cast<std :: uint16_t>(strtol(res, &endptr, 16)));
	}
}

} /* namespace protocol */
