# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Executable and Object Files
TARGET = test6.exe
OBJS = test6.o graph.o

# Default target
all: $(TARGET)

# Rule for building the executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

# Rule for building object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target (Windows-compatible)
clean:
	del /f /q $(TARGET) $(OBJS)
