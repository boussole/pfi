PROJ=`basename $(realpath .)`.bin
OBJ=$(patsubst %.cpp,%.o,$(filter-out main.cpp,$(wildcard *.cpp)))
CXXFLAGS += -std=c++14 -Wall -Werror -g -pg
INC += -I../

all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) $(OBJ) main.cpp -o $(PROJ) 

clean:
	rm -rf *.o
	rm -rf $(PROJ)
	rm -rf *.h.gch gmon.out

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INC) -c $^

.PHONY: all clean