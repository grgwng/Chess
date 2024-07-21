CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD
EXEC = chess

# Source directories
SRC_DIRS = . display entities entities/pieces

# Find all .cc files in the source directories
CCFILES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cc))

# Object files and dependency files
OBJECTS = $(CCFILES:.cc=.o)
DEPENDS = $(CCFILES:.cc=.d)

# Default target
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

# Include dependency files
-include ${DEPENDS}

# Clean target
.PHONY: clean
clean:
	rm -f ${OBJECTS} ${DEPENDS} ${EXEC}
