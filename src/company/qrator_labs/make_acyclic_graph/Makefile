PROJ=`basename $(realpath .)`.bin
OBJ=$(patsubst %.cpp,%.o,$(filter-out main.cpp,$(wildcard *.cpp)))
CXXFLAGS += -Wall -Werror -g -pg
INC += -I../

all: $(OBJ) graph.h
	$(CXX) $(CXXFLAGS) $(INC) $(OBJ) main.cpp -o $(PROJ) 

clean:
	rm -rf *.o
	rm -rf $(PROJ)
	rm -rf gmon.out *.gch
	rm -rf $(PROJ)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INC) -c $^

.PHONY: all clean
