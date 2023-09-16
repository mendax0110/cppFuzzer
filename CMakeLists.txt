cmake_minimum_required(VERSION 3.26)

project(cppFuzzer)

# Set C++ standard (e.g., C++11, C++14, C++17)
set(CMAKE_CXX_STANDARD 17)

# Specify the source files
set(SOURCES
    src/fuzzer.cpp
    src/main.cpp
    src/parser.cpp
    src/setupFuzzer.cpp
    src/teardownFuzzer.cpp
)

# Specify the header files
set(HEADERS
    src/includes/fuzzer.h
    src/includes/main.h
    src/includes/parser.h
    src/includes/setupFuzzer.h
    src/includes/teardownFuzzer.h
)

# Specify the test source files
set(TEST_SOURCES
    test/testFuzzer.cpp
    test/testParser.cpp
    test/testMain.cpp
    test/testSetupFuzzer.cpp
    test/testTeardownFuzzer.cpp
)

# Create the executable target
add_executable(cppFuzzer ${SOURCES} ${HEADERS})
