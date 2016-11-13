PROJ=`basename $(realpath .)`.bin
OBJ=$(patsubst %.cpp,%.o,$(filter-out main.cpp,$(wildcard *.cpp)))
CXXFLAGS += -std=c++11 -Wall -Werror -g -pg -DNEED_BOOST_BASIC -DNEED_BOOST_UBLAS
INC += -I../

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) $(OBJ) main.cpp -o $(PROJ) 

clean:
	rm -rf *.o
	rm -rf $(PROJ)
	rm -rf *.out
	rm -rf *.gch

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INC) -c $^

.PHONY: all clean
