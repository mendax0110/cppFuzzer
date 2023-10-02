cmake_minimum_required(VERSION 3.26)

project(cppFuzzer)

# Set C++ standard (e.g., C++11, C++14, C++17)
set(CMAKE_CXX_STANDARD 17)

# Specify the source files for your main program
set(MAIN_SOURCES
    src/fuzzer.cpp
    src/main.cpp
    src/parser.cpp
    src/setupFuzzer.cpp
    src/teardownFuzzer.cpp
    src/structurePrinter.cpp
)

# Specify the header files for your main program
set(MAIN_HEADERS
    src/includes/fuzzer.h
    src/includes/main.h
    src/includes/parser.h
    src/includes/setupFuzzer.h
    src/includes/teardownFuzzer.h
    src/includes/structurePrinter.h
)

# Create a library containing the common code
add_library(cppFuzzerLib STATIC ${MAIN_SOURCES} ${MAIN_HEADERS})

# Create the main program executable target and link it with the common library
add_executable(cppFuzzer src/main.cpp)
target_link_libraries(cppFuzzer PRIVATE cppFuzzerLib)

# Specify the test source files
set(TEST_SOURCES
    test/testFuzzer.cpp
    test/testParser.cpp
    test/testSetupFuzzer.cpp
    test/testTeardownFuzzer.cpp
)

# Create a separate executable target for each test source file and link them with the common library
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE cppFuzzerLib)
    
    # Add the test to the test target and exclude from all
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    
    # Exclude specific tests from all
    if(TEST_NAME MATCHES "testParser" OR TEST_NAME MATCHES "testTeardownFuzzer")
        set_target_properties(${TEST_NAME} PROPERTIES EXCLUDE_FROM_ALL 1)
    endif()
endforeach()

# Enable testing
enable_testing()
