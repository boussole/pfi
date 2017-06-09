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
 * \file      server.cpp
 * \copyright GNU Public License
 * \author    boussole
 ****************************************************************/

// std
#include <iostream>
#include <stdlib.h>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>
#include <list>
// boost
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp> //< for group_thread, I like it
// custom
#include <common/common.h>

using namespace boost :: asio;
// using namespace std::placeholders; !!! conflicting with /boost/thread/thread.hpp
using factorizer = factorization<factorization_details :: impl_2>;

#define WORKERS_QUANTITY 3

#define STD_PH std::placeholders

namespace _details {

class peer : public std :: enable_shared_from_this<peer>
{
	using self_type = peer;

	using task = std :: pair<std :: uint16_t, std :: list<std :: uint16_t> >;

	const static std :: size_t TASK_LIMIT = 5; // brute force attack :-)

	/**
	 * \brief Constructor initializes socket by io_service
	 */
	peer(io_service &io) :
		_sock(io)
	{

	}

public:
	~peer()
	{
		std :: cout << __PRETTY_FUNCTION__ << ": connection closed " << _info << std :: endl;
	}

	using _self = std :: shared_ptr<peer>;

	/**
	 * \brief Factory method to create new peer
	 */
	static _self create(io_service &io)
	{
		_self client(new peer(io));

		return client;
	}

	/**
	 * \brief   Do task and send response
	 * \details 1. factorize value
	 *          2. pack response
	 *          3. send response
	 */
	void do_task()
	{
		using namespace protocol;

		task &t = _task_list.front();

		code c = (factorizer :: decompose(t.first, t.second) == 0) ? code :: ERROR : code :: OK;

		std :: size_t bytes = serial_resp(t.first, c, t.second, _output);

		async_write(_sock, _output, transfer_exactly(bytes), MEM_FN_2(handler_write));
	}

	/**
	 * \brief Reading request
	 */
	void handler_request(const boost::system::error_code &error, std::size_t bytes_transferred)
	{
		if (error) {
			common :: log_error(__PRETTY_FUNCTION__, error);
			_sock.close();
		}
		else {
			protocol :: binary :: req_hdr req;

			protocol :: deserial_req(_input, req);

			bool force_start_task = false;
			{
				// brute force detection
				// todo: send response
				std::lock_guard<std::mutex> locker(_lock);

				if (_task_list.size() < TASK_LIMIT) {

					_task_list.push_back(std :: move(task()));

					_task_list.back().first = req._value;

					force_start_task = (_task_list.size() == 1);
				}
			}

			async_read(_sock, _input, transfer_exactly(protocol :: REQUEST_SZ), MEM_FN_2(handler_request));

			if (force_start_task)
				do_task();
		}
	}

	/**
	 * \brief Writing request
	 */
	void handler_write(const boost::system::error_code &error, std::size_t bytes_transferred)
	{
		using namespace protocol;

		bool schedule_next = false;

		if (error) {
			common :: log_error(__PRETTY_FUNCTION__, error);
			_sock.close();
		}
		else {
			// task completed, remove it from task_list and schedule next if it exists
			std::lock_guard<std::mutex> locker(_lock);

			_task_list.pop_front();

			schedule_next = (_task_list.size() > 0);
		}

		if (schedule_next)
			do_task();
	}

	/**
	 * \brief Start handling
	 */
	void start()
	{
		boost :: system :: error_code e_code;

		ip :: tcp :: socket :: keep_alive option(true);

		_sock.set_option(option, e_code);

		if (e_code)
			common :: log_error(__PRETTY_FUNCTION__, e_code);
		else {
			// save info about connection for logger
			ip :: tcp :: endpoint ep = _sock.remote_endpoint();
			_info = ep.address().to_string() + ":" + std :: to_string(ep.port());
			// server down detection in idle state
			async_read(_sock, _input, transfer_exactly(protocol :: REQUEST_SZ), MEM_FN_2(handler_request));
		}
	}

	/**
	 * \brief Asio socket access
	 */
	ip::tcp::socket &sock() { return _sock; }

private:
	ip :: tcp :: socket _sock;
	std :: mutex _lock;
	streambuf _input, _output;
	std :: list<task> _task_list;
	protocol :: resp_hdr _resp_hdr;
	std :: list<std :: uint16_t> _result;
	std :: string _info;
};

} /** namespace _details */

/**
 * \brief Service incomming connections
 */
static void handle_accept(_details :: peer :: _self peer,
                          ip :: tcp :: acceptor &acceptor,
                          const boost :: system :: error_code &error)
{
	if (!error) {
		peer->start();
		_details :: peer :: _self peer = _details :: peer :: create(acceptor.get_io_service());
		acceptor.async_accept(peer->sock(), std :: bind(handle_accept, peer, std :: ref(acceptor), STD_PH :: _1));
	}
	else
		common :: log_error(__PRETTY_FUNCTION__, error);
}

int main(int argc, char * argv[])
{
	using namespace std;

	if (argc < 2) {
		cout << "usage: " << *argv << " <port>\n";
		return 1;
	}

	// read port
	int port = 0;
	if (!common :: str_to_int(argv[1], 1, 0xFFFF, port)) {
		cout << "invalid port\n";
		return 1;
	}

	try {
		factorizer :: init();

		io_service io;

		ip :: tcp :: acceptor acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), static_cast<std :: uint16_t>(port)));

		/** addition scope to emulate std :: move for peer */
		{
			_details :: peer :: _self peer = _details :: peer :: create(io);

			acceptor.async_accept(peer->sock(), std :: bind(handle_accept, peer, std :: ref(acceptor), STD_PH :: _1));
		}

		/**
		 *  asio model: 'one io_service + few workers'
		 */
		boost :: thread_group workers;
		int w_counter = WORKERS_QUANTITY;
		while (w_counter-- > 0) {
			workers.create_thread([&io]() {
				io.run();
			});
		}
		std :: this_thread :: sleep_for(std :: chrono :: seconds(1));
		workers.join_all();
	}
	catch (const boost::system::system_error &err) {
		cout << "invalid acceptor params\n";
		return 1;
	}

	return 0;
}
