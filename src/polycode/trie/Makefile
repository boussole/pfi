PROJ=`basename $(realpath .)`.bin
OBJ=$(patsubst %.cpp,%.o,$(filter-out main.cpp, $(wildcard *.cpp)))
CXFLAGS += -Wall -Werror -std=c++14 -I.. -g -pg -DNEED_BOOST_BASIC

all: $(OBJ)
	rm -rf $(PROJ) 
	$(CXX) $(CXFLAGS) main.cpp -o $(PROJ) 

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf $(PROJ)

%.o: %.h %.cpp
	$(CXX) $(CXFLAGS) -c $^

.PHONY: all clean
