PROBLEMS = $(basename $(wildcard *.cpp))

all:
	@echo "Specify a problem: $(PROBLEMS)"

clean:
	rm -rf *.o *.out core *.bin

%:
	@echo "Building problem: '$@'..."
	@($(CXX) -p -pg -std=c++11 -Wall -Werror $@.cpp -o $@.bin)
	@echo "Running problem: '$@'..."
	@(./$@.bin <$@.test)
	@echo "Finished problem: '$@'.\n"

.PHONY: all clean
