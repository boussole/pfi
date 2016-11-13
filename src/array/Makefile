PROJ=`basename $(realpath .)`.bin
OBJ=$(patsubst %.cpp,%.o,$(filter-out main.cpp,$(wildcard *.cpp)))
CXXFLAGS += -std=c++14 -Wall -Werror -g -pg -DNEED_BOOST_BASIC -DNEED_BOOST_UBLAS
INC += -I../

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) $(OBJ) main.cpp -o $(PROJ) 

clean:
	rm -rf *.o
	rm -rf $(PROJ)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INC) -c $^

.PHONY: all clean
