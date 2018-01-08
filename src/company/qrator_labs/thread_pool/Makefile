PROJ=`basename $(realpath .)`.bin
OBJ=$(patsubst %.cpp,%.o,$(filter-out main.cpp,$(wildcard *.cpp)))
CXXFLAGS += -Wall -Werror -g -pg
INC += -I../
LDFLAGS=-lboost_system -lboost_thread -pthread

all: $(OBJ) thread_pool.h
	$(CXX) $(CXXFLAGS) $(INC) $(OBJ) main.cpp -o $(PROJ) $(LDFLAGS) 

clean:
	rm -rf *.o
	rm -rf $(PROJ)
	rm -rf *.gch
	rm -rf gmon.out core

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $(INC) -c $^

.PHONY: all clean
