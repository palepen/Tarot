# Require a minimum CMake version (3.16 is widely supported and sufficient for modern features)
cmake_minimum_required(VERSION 3.16)

# Project definition with C++ language
project(Tarot LANGUAGES CXX)

# Set C++ standard to 17 and make it required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Suggest clang++ as the compiler, but allow override via cache or command line
set(CMAKE_CXX_COMPILER "clang++" CACHE STRING "C++ compiler" FORCE)
# Include directories (scoped globally here, but prefer target-specific includes in subdirs)
include_directories(${CMAKE_SOURCE_DIR}/includes)
message(STATUS "SOURCE DIR: ${CMAKE_SOURCE_DIR}")

# Find LLVM package
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Enable testing with CTest
include(CTest)

# Add subdirectories for source and tools
add_subdirectory(src)
add_subdirectory(tools)

# Conditionally add tests if BUILD_TESTING is enabled
if(BUILD_TESTING)
    find_package(Catch2 CONFIG REQUIRED)
    if(Catch2_FOUND)
        message(STATUS "Found Catch2 for testing")
        add_subdirectory(test)
    else()
        message(WARNING "Catch2 not found; tests will not be built")
    endif()
endif()

install(TARGETS tarot DESTINATION bin)
