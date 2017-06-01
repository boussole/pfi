PROJ=`basename $(realpath .)`.bin
CFLAGS += -std=c99 -Wall -Werror -D_POSIX_SOURCE -g -pg -D_GNU_SOURCE

all: $(OBJ)
	$(CC) $(CFLAGS) ls.c -o $(PROJ)

clean:
	rm -rf *.gch *.out
	rm -rf *.o
	rm -rf $(PROJ)

#%.o: %.cpp %.h
#	$(CXX) $(CXXFLAGS) $(INC) -c $^

.PHONY: all clean