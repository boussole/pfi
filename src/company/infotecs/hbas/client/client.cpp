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
 * \file      client.cpp
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/

// std
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <mutex>
#include <unordered_map>
// boost
#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
// custom
#include <common/common.h>

using namespace boost :: asio;

#ifdef WITH_CLIENT_WELCOME
#	define CLIENT_WELCOME() do { std :: cout << "enter numbers: "; std :: flush(std :: cout); } while(0)
#else
#	define CLIENT_WELCOME() do {} while(0)
#endif

namespace _details {

using namespace std::placeholders;

class client : public std :: enable_shared_from_this<client>
{
	using self_type = client;

	/**
	 * \brief Constructor initializes socket by io_service
	 */
	client(io_service &io) :
		_sock(io),
		_console(io, ::dup(STDIN_FILENO))
	{
		_resp._code = static_cast<std :: uint16_t>(protocol :: code :: __MAX);
	}

	/**
	 * \brief Start connect-to-server process
	 */
	void connect(const ip :: tcp :: endpoint &ep) {
		_sock.async_connect(ep, MEM_FN_1(handle_connect));
	}

	/**
	 * \brief Print result
	 */
	void print(std :: list<std :: uint16_t> &res)
	{
		std :: stringstream ss;

		ss << _resp._value << " =>";

		for (auto i : res)
			ss << " " << i;

		ss << std :: endl;

		std :: cout << ss.str();

		CLIENT_WELCOME();
	}

	/**
	 * \brief  Write to socket
	 */
	void handler_write_socket(const boost::system::error_code& error, std :: size_t bytes_transferred)
	{
		if (error) {
			common :: log_error(__PRETTY_FUNCTION__, error);
			_sock.close();
			_sock.get_io_service().stop();
		}
		else {
			std :: lock_guard<std :: mutex> guard(_lock);
			_delayed_request.pop_front();
			if (_delayed_request.size() > 0) {
				async_write(_sock, buffer(_delayed_request.front()),
				            transfer_exactly(_delayed_request.front().length()),
				            MEM_FN_2(handler_write_socket));
			}
		}
	}

	/**
	 * \brief   Read commend line
	 * \details Analize whole line.
	 *          Line can contain a few values which are separeted by spaces
	 *          Example: "234 1 jkd3 4" => value_1 = 234, value_2 = 1, value_3 = 4.
	 */
	void handle_read_console(const boost::system::error_code &error, size_t sz)
	{
		std::istream is(&_consolebuf);
		std::string line;

		std::getline(is, line);
		std :: vector<std :: string> request;
		boost :: split(request, line, boost :: is_any_of(" \n\t"), boost :: token_compress_on);

		if (request.size() > 0) {
			for (auto r : request) {
				if (r.empty())
					continue;

				int value = 0;
				if (!common :: str_to_int(r.c_str(), 1, 0xFFFF, value))
					continue;

				// we have limit for awaiting task quantity
				// if we haven't exceeded it, we are adding new task
				std :: lock_guard<std :: mutex> guard(_lock);

				if (_delayed_request.size() < DELAYED_TASK_LIMIT) {
					std :: string msg;
					protocol :: serial_req(value, msg);
					_delayed_request.push_back(std :: move(msg));

					// if it's the first request, we are scheduling write operation
					if (_delayed_request.size() == 1)
						async_write(_sock, buffer(_delayed_request.front()),
						            transfer_exactly(_delayed_request.front().length()), MEM_FN_2(handler_write_socket));
				} else {
					std :: cout << "to many requests, skiping request of value = " << value << std :: endl;
				}
			}
		}

		CLIENT_WELCOME();

		async_read_until(_console, _consolebuf, '\n', MEM_FN_2(handle_read_console));
	}

	/**
	 * \brief   Read server response
	 * \details Depends
	 */
	void handle_response(const boost::system::error_code &error, std :: size_t bytes_transferred)
	{ // std :: cout << __PRETTY_FUNCTION__ << std :: endl;
		if (error) {
			common :: log_error(__PRETTY_FUNCTION__, error);
			_sock.close();
			_sock.get_io_service().stop();
		}
		else {
			// we use __MAX to detect what we are realy waiting for
			if (_resp._code == static_cast<std :: uint16_t>(protocol :: code :: __MAX)) {
				protocol :: deserial_resp_hdr(_input, _resp);
				if (_resp._code == static_cast<std :: uint16_t>(protocol :: code :: OK)) {
					async_read(_sock, _input, transfer_exactly(protocol :: RESULT_UNIT_SZ * _resp._quantity), MEM_FN_2(handle_response));
				} else {
					async_read(_sock, _input, transfer_exactly(protocol :: RESPONSE_SZ), MEM_FN_2(handle_response));
					common :: log_error(__PRETTY_FUNCTION__, "server error");
					_resp._code = static_cast<std :: uint16_t>(protocol :: code :: __MAX);
				}
			}
			else {
				std :: list<std :: uint16_t> result;
				protocol :: deserial_resp_payload(_input, _resp._quantity, result);
				print(result);
				// waiting next input header or server refuse
				_resp._code = static_cast<std :: uint16_t>(protocol :: code :: __MAX);
				async_read(_sock, _input, transfer_exactly(protocol :: RESPONSE_SZ), MEM_FN_2(handle_response));
			}
		}
	}

	/**
	 * \brief Connect handler
	 */
	void handle_connect(const boost::system::error_code &error)
	{
		if (!error) {
			std :: cout << __PRETTY_FUNCTION__ << ": connection established\n";
			CLIENT_WELCOME();
			async_read_until(_console, _consolebuf, '\n', MEM_FN_2(handle_read_console));
			//
			boost :: system :: error_code e_code;
			ip :: tcp :: socket :: keep_alive option(true);
			_sock.set_option(option, e_code);

			if (e_code) {
				common :: log_error(__PRETTY_FUNCTION__, e_code);
				_console.get_io_service().stop();
			}
			else
				async_read(_sock, _input, transfer_exactly(protocol :: RESPONSE_SZ), MEM_FN_2(handle_response));
		}
		else
			common :: log_error(__PRETTY_FUNCTION__, error);
	}

public:
	using _self = std :: shared_ptr<client>;

	static constexpr size_t DELAYED_TASK_LIMIT = 5; /**< this is border when we start ignore user commands */

	client(const client & rhs) = delete;

	/**
	 * \brief Factory method to create new client
	 */
	static _self create(io_service &io, const ip :: tcp :: endpoint &ep)
	{
		_self new_client(new client(io));

		new_client->connect(ep);

		return new_client;
	}

private:
	ip :: tcp :: socket _sock;
	posix :: stream_descriptor _console;
	streambuf _consolebuf, _input;
	protocol :: binary :: resp_hdr _resp;
	std :: list<std :: string> _delayed_request;
	std :: mutex _lock;
};

} /** namespace _details */

int main(int argc, char *argv[])
{
	using namespace std;

	if (argc < 3) {
		cout << "usage: " << *argv << " <ip address> <port>\n";
		return 1;
	}

	// read address
	boost::system::error_code e_code;
	ip :: address addr = ip :: address :: from_string(argv[1], e_code);
	if (e_code) {
		cout << "invalid ip address: \"" << argv[1] << "\"\n";
		return 1;
	}

	// read port
	int port = 0;
	if (!common :: str_to_int(argv[2], 1, 0xFFFF, port)) {
		cout << "invalid port: \"" << argv[2] << "\"\n";
		return 1;
	}

	io_service io;

	_details :: client :: _self cl = _details :: client :: create(io, ip :: tcp :: endpoint(addr, static_cast<uint16_t>(port)));

	return io.run();
}
