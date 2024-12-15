TARGET_EXEC := ./trt

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C, C++, and assembly files we want to compile
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

# Generate object file paths by prepending the build directory and appending .o
OBJS := $(SRCS:$(SRC_DIRS)/%=$(BUILD_DIR)/%.o)

# Define dependency file paths (replace .o with .d)
DEPS := $(OBJS:.o=.d)

# Find all the directories within SRC_DIRS and prepare include flags
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Compiler flags for Clang and Clang++ files, including dependency generation
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# Use Clang as the compiler
CXX := clang++
CFLAGS := -std=c11
CXXFLAGS := -std=c++17

# Linker flags (using llvm-config for LLVM libraries)
LDFLAGS := $(shell llvm-config --ldflags --libs)

# Final build step: linking object files into the final executable
$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Rule for compiling C++ source files
$(BUILD_DIR)/%.cpp.o: $(SRC_DIRS)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Clean build files
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) ./trt

# Include the .d dependency files. The - at the front suppresses errors for missing dependencies.
-include $(DEPS)
