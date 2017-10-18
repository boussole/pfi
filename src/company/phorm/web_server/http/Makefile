CXXFLAGS = -I. -I..
OBJ = answer.o request.o
LIBRARY = libhttp.a

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	ar rv $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY)
	mv $(LIBRARY) ../lib/

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ)


