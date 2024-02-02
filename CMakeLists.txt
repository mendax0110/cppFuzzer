cmake_minimum_required(VERSION 3.20)

project(cppFuzzer)
project(Basic-Http-Server-cpp)

# Set C++ standard (e.g., C++11, C++14, C++17)
set(CMAKE_CXX_STANDARD 17)

# Search for the MSVC Compiler and set it if it is found
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()

find_package( Threads REQUIRED )

add_executable(server
    ${CMAKE_CURRENT_SOURCE_DIR}/external/Basic-Http-Server-cpp/html_parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/external/Basic-Http-Server-cpp/main.cpp
)

if(WIN32)
    target_link_libraries(server ws2_32)
endif()

if(UNIX)
    #target_compile_options(server PUBLIC "-pthread")  Replaced with <thread>
endif()

target_link_libraries(server Threads::Threads)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/external/Basic-Http-Server-cpp/main.html
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# Specify the source files for your main program
set(MAIN_SOURCES
    src/fuzzer.cpp
    src/main.cpp
    src/parser.cpp
    src/setupFuzzer.cpp
    src/teardownFuzzer.cpp
    src/structurePrinter.cpp
    src/sanitizer.cpp
    src/sast.cpp
    src/fuzzerAPI.cpp
    src/rpcHub.cpp
    src/hostDeterminator.cpp
    src/pyIPC.cpp
)

# Specify the header files for your main program
set(MAIN_HEADERS
    src/includes/fuzzer.h
    src/includes/main.h
    src/includes/parser.h
    src/includes/setupFuzzer.h
    src/includes/teardownFuzzer.h
    src/includes/structurePrinter.h
    src/includes/sanitizer.h
    src/includes/sast.h
    src/includes/fuzzerAPI.h
    src/includes/atomizes.hpp
    src/includes/rpcHub.h
    src/includes/hostDeterminator.h
    src/includes/pyIPC.h
    src/includes/macroBase.h
)

# Create a library containing the common code
add_library(cppFuzzerLib STATIC ${MAIN_SOURCES} ${MAIN_HEADERS})

# Create the main program executable target and link it with the common library
add_executable(cppFuzzer src/main.cpp)
target_link_libraries(cppFuzzer PRIVATE cppFuzzerLib)
if(WIN32)
    target_link_libraries(cppFuzzerLib PRIVATE Ws2_32.lib)
endif()

# Specify the test source files
set(TEST_SOURCES
    test/testFuzzer.cpp
    #test/testParser.cpp
    test/testSetupFuzzer.cpp
    #test/testTeardownFuzzer.cpp
    test/testSast.cpp
    test/testSanitizer.cpp
    test/testAPI.cpp
    #test/testWebservice.cpp
    test/testRPC.cpp
)

# Create a separate executable target for each test source file and link them with the common library
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE cppFuzzerLib)
    
    # Add the test to the test target and exclude from all
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Enable testing
enable_testing()

