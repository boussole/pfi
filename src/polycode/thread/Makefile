PROJ=`basename $(realpath .)`.bin
OBJ=$(patsubst %.cpp,%.o,$(filter-out main.cpp,$(wildcard *.cpp)))
CXXFLAGS += -std=c++14 -Wall -Werror -g -pg
INC += -I../
LD_FLAGS = -lpthread

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) $(OBJ) main.cpp -o $(PROJ) $(LD_FLAGS)

clean:
	rm -rf *.o
	rm -rf $(PROJ)
	rm -rf *.out
	rm -rf *.gch 

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INC) -c $^

.PHONY: all clean
