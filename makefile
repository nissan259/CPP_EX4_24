# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Wextra -I.

# Define the target executable for the main program
TARGET = tree

# Define the target executable for the tests
TEST_TARGET = test

# Define the source files for the main program
SRCS = main.cpp complex.cpp

# Define the source files for the tests
TEST_SRCS = test.cpp complex.cpp

# Define the object files for the main program
OBJS = $(SRCS:.cpp=.o)

# Define the object files for the tests
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Default target to build the main program
all: $(TARGET) $(TEST_TARGET)

# Rule to build the target executable for the main program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system

# Rule to build the target executable for the tests
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Rule to build object files from source files for the main program
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the build artifacts
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS)

# Rule to run the main program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
