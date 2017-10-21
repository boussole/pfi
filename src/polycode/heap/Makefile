PROJ=`basename $(realpath .)`.bin
OBJ=$(patsubst %.cpp,%.o,$(filter-out main.cpp, $(wildcard *.cpp)))
CXFLAGS += -Wall -Werror -std=c++11 -I.. -g -pg

all: $(OBJ)
	rm -rf $(PROJ)
	$(CXX) $(CXFLAGS) main.cpp -o $(PROJ)

clean:
	rm -rf *.out
	rm -rf *.o
	rm -rf $(PROJ)

%.o: %.h %.cpp
	$(CXX) $(CXFLAGS) -c $^

.PHONY: all clean
