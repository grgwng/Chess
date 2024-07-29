CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -MMD -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib -lX11
EXEC = chess

# Source directories
SRC_DIRS = . display entities entities/pieces game game/player game/player/computer interpreter

# Find all .cc files in the source directories
CCFILES = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cc))

# Object files and dependency files
OBJECTS = $(CCFILES:.cc=.o)
DEPENDS = $(CCFILES:.cc=.d)

# Default target
${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

# Include dependency files
-include ${DEPENDS}

# Clean target
.PHONY: clean
clean:
	rm -f ${OBJECTS} ${DEPENDS} ${EXEC}
