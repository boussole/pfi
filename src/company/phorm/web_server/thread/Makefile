CXXFLAGS = -I. -I.. -pthread
OBJ = thread.o
LIBRARY = libthread.a

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	ar rv $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY)
	mv $(LIBRARY) ../lib/

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ)


