TARGET_EXEC := ./trt

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C and C++ files
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

# Prepends BUILD_DIR and appends .o to every source file
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Use clang++ from LLVM
LLVM_CONFIG := llvm-config
CXX := clang++
CC := clang

# Include directories from LLVM
LLVM_CXXFLAGS := $(shell llvm-config --cxxflags | sed 's/-fno-rtti//g')
LLVM_LDFLAGS := $(shell $(LLVM_CONFIG) --ldflags)
LLVM_LIBS := $(shell $(LLVM_CONFIG) --libs core executionengine irreader) -lpthread -ldl -lz

# String substitution (suffix version without %)
DEPS := $(OBJS:.o=.d)

# Every folder in ./src needs to be passed for header file lookup
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Compiler flags
CPPFLAGS := $(INC_FLAGS) $(LLVM_CXXFLAGS) -MMD -MP -frtti
LDFLAGS := $(LLVM_LDFLAGS) $(LLVM_LIBS)

# Final build step
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Include the .d makefiles to enable automatic dependency tracking
-include $(DEPS)
