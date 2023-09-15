cmake_minimum_required(VERSION 3.27)  # Use the same or higher CMake version as in your cache

project(cppFuzzer)  # Use the same project name as in your cache

# Set C++ standard (e.g., C++11, C++14, C++17)
set(CMAKE_CXX_STANDARD 17)

# Specify the source files and header files
set(SOURCES
    cppFuzzer/src/fuzzer.cpp
    cppFuzzer/src/main.cpp
    cppFuzzer/src/parser.cpp
    cppFuzzer/src/setupFuzzer.cpp
    cppFuzzer/src/teardownFuzzer.cpp
)

set(HEADERS
    cppFuzzer/includes/fuzzer.h
    cppFuzzer/includes/main.h
    cppFuzzer/includes/parser.h
    cppFuzzer/includes/setupFuzzer.h
    cppFuzzer/includes/teardownFuzzer.h
)

# Include directories for header files
include_directories(${CMAKE_SOURCE_DIR}/src/includes)

# Create the executable target
add_executable(MyCppExecutable ${SOURCES} ${HEADERS})

# Optionally, set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}")  # Include debug flags

# Optionally, set linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")  # Include debug linker flags
