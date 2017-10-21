PROJ=`basename $(realpath .)`.bin
OBJ=$(patsubst %.cpp,%.o,$(filter-out main.cpp, $(wildcard *.cpp)))
CXFLAGS += -Wall -Werror -std=c++11 -I.. -g -pg

all: $(OBJ)
	$(CXX) $(CXFLAGS) main.cpp -o $(PROJ) ${OBJ}

clean:
	rm -rf *.out
	rm -rf *.o
	rm -rf $(PROJ)

%.o: %.h %.cpp
	$(CXX) $(CXFLAGS) -c $^

.PHONY: all clean