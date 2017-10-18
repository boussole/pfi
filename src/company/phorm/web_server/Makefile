APP = web_server
OBJ = handle.o segment.o acceptor.o main.o
CXXFLAGS = -I. -pthread
LIBFLAGS = -L./lib -lnetwork -lthread -lhttp -lfilesystem

all: sub $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(APP) $(LIBFLAGS)

sub:
	$(MAKE) -C filesystem
	$(MAKE) -C network
	$(MAKE) -C thread
	$(MAKE) -C http
clean:
	rm -f $(APP).o $(APP)
	rm -f $(LIBRARY)
	rm -f $(OBJ)
	rm -f ./lib/*
	$(MAKE) clean -C network
	$(MAKE) clean -C thread
	$(MAKE) clean -C filesystem
	$(MAKE) clean -C http

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: all sub clean
