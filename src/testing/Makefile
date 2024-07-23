# Variables
CXX = g++
CXXFLAGS = -Wall -g -I../interpreter -I../types -std=c++14
SRCS = inputtest.cc ../interpreter/commands.cc ../interpreter/interpreter.cc
OBJS = $(SRCS:.cc=.o)
DEPS = ../interpreter/commands.h ../interpreter/interpreter.h ../types/types.h

# Target
all: testprogram

# Rule for building the program
testprogram: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^	

# Rule for building object files
%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(OBJS) testprogram