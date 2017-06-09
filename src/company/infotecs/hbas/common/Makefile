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
# \brief     Build common
# \file      Makefile
# \copyright GNU Public License
# \author    boussole
###################################################################

# Library name
LIB=`basename $(realpath .)`.a

# Binary name
PROJ=`basename $(realpath .)`.bin

# Build flags
CXXFLAGS=-Wall -Werror -std=c++14# -g -pg

# Link flags
LDFLAGS=-lboost_system

# Object files
OBJ=$(patsubst %cpp,%o,$(filter-out test.cpp,$(wildcard *.cpp)))

all: lib
#	$(CXX) $(CXXFLAGS) $(OBJ) -o $(PROJ) $(LDFLAGS)

test: lib
	$(CXX) $(CXXFLAGS) $(OBJ) test.cpp -o $(PROJ) $(LDFLAGS)

lib: $(OBJ)
	echo $(OBJ)
	ar r -s $(LIB) $^

clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf $(PROJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $<

.PHONY: all clean lib test