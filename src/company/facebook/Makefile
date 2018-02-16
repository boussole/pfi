PROBLEMS = $(basename $(wildcard *.cpp))

all:
	@echo "Specify a problem: $(PROBLEMS)"

clean:
	rm -rf *.o *.out core *.bin

%:
	@echo "Building problem: '$@'..."
	@($(CXX) -p -pg -Wall -Werror -std=c++11 $@.cpp -o $@.bin)
	@echo "Running problem: '$@'..."
	@(./$@.bin <$@.test)
	@echo "Finished problem: '$@'.\n"

.PHONY: all clean
