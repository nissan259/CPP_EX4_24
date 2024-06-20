# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Wextra -I.

# Define the target executables
TARGET = tree
TEST_TARGET = test_tree

# Define the source files
SRCS = main.cpp
TEST_SRCS = test.cpp

# Define the object files
OBJS = $(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Default target to build the executable and test executable
all: $(TARGET) $(TEST_TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system

# Rule to build the test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Rule to build object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the build artifacts
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

# Rule to run the tests
test: $(TEST_TARGET)
	./$(TEST_TARGET) --success

.PHONY: all clean run test
