OBJ = file_utils.o
LIBRARY = libfilesystem.a

all: $(LIBRARY)

$(LIBRARY): $(OBJ)
	ar rv $(LIBRARY) $(OBJ)
	ranlib $(LIBRARY)
	mv $(LIBRARY) ../lib/

%.o: %.cpp
	$(CXX) -c $<

clean:
	rm -f $(OBJ)
