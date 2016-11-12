PROJ=`basename $(realpath .)`.bin
OBJ=$(patsubst %.cpp,%.o,$(filter-out main.cpp,$(wildcard *.cpp)))
CXXFLAGS += -std=c++14 -Wall -Werror -g -pg
INC += -I../

all: $(OBJ) dep
	$(CXX) $(CXXFLAGS) $(INC) $(OBJ) main.cpp -o $(PROJ) chess_board.o 

dep:
	$(CXX) $(CXXFLAGS) $(INC) -c ../common/chess_board.cpp

clean:
	rm -rf *.o *.gch *.out
	rm -rf $(PROJ)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INC) -c $^

.PHONY: all clean
