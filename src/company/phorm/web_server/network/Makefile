CXXFLAGS = -I. -I..
OBJ = network_tools.o socket_container.o
LIBRARY = libnetwork.a

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	ar rv $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY)
	mv $(LIBRARY) ../lib/

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ)

