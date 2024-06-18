# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Wextra -I.

# Define the target executable
TARGET = tree

# Define the source files
SRCS = main.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
