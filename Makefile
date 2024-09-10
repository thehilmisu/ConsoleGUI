# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# Source files
SRCS = main.cpp Button.cpp Label.cpp TUIManager.cpp

# Object files (in the build directory)
OBJS = $(patsubst %.cpp, build/%.o, $(SRCS))

# Executable name (in the build directory)
TARGET = build/tui_manager

# Build directory
BUILD_DIR = build

# Default target
all: $(TARGET)

# Ensure the build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to link the final executable
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lncurses
	@echo "Linking complete: $(TARGET)"

# Rule to compile each .cpp file into an object file
build/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiled $< into $@"

# Clean up build artifacts
clean:
	rm -rf $(BUILD_DIR)
	@echo "Cleaned up build directory"

# Phony targets to prevent conflicts with files of the same name
.PHONY: all clean
