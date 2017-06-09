##################################################################
# Copyright (c) 2016 boussole (x dotty conquistador dotty at gmail com)
# All rights reserved.
#
# This file is part of hbas.
#
# Hbas is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>
#
# https://github.com/boussole/hbas
#
# \brief     Build common, server, client
# \file      Makefile
# \copyright GNU Public License
# \author    boussole
###################################################################

all: build_common build_client build_server
	@mkdir -p bin
	@cp client/client.bin bin
	@cp server/server.bin bin

clean: clean_common clean_client clean_server

build_common:
	$(MAKE) -C common

clean_common:
	$(MAKE) -C common clean

build_client:
	$(MAKE) -C client

clean_client:
	$(MAKE) -C client clean

build_server:
	$(MAKE) -C server

clean_server:
	$(MAKE) -C server clean
	rm -rf core gmon.out bin

test:
	$(MAKE) -C common test

.PHONY: all clean build_client build_server clean_client clean_server test
