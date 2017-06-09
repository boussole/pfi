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
# \brief     Build server
# \file      Makefile
# \copyright GNU Public License
# \author    boussole
###################################################################

# Binary name
PROJ=`basename $(realpath .)`.bin

# Build flags
CXXFLAGS=-Wall -Werror -std=c++14 -I..

# Link flags
LDFLAGS=-lboost_system -lboost_thread ../common/common.a

# Object files
OBJ=$(patsubst %cpp,%o,$(wildcard *.cpp))

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(PROJ) $(LDFLAGS)

clean:
	rm -rf *.o
	rm -rf $(PROJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $<

.PHONY: all clean