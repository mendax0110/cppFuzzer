/**
 * @file testFuzzer.cpp
 * @author Adrian Goessl
 * @brief Simple test for the fuzzer
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include <vector>
#include "../src/includes/fuzzer.h"

// Function to find the executable path dynamically
std::string findExecutablePath()
{
    return "../cppFuzzer/build/cppFuzzer";
}

// Function to run an external process
int RunExternalProcess(const std::vector<char*>& args)
{
    // TODO: Implement the logic to execute an external process and return its exit code
    // TODO: for linux, macos and windows
    int exitCode = 0; // Replace with actual exit code
    
    return exitCode;
}

/// @brief The testFuzzer function \name testFuzzer, this will be used to test the string Fuzzer
void testFuzzString()
{
    std::string inputString = "Hello, World!";
    std::string cppFuzzerPath = findExecutablePath();
    std::vector<char*> args = {const_cast<char*>(cppFuzzerPath.c_str()), const_cast<char*>("1"), const_cast<char*>(inputString.c_str()), nullptr};

    int result = RunExternalProcess(args);

    if (result == 0)
    {
        std::cout << "fuzzString test passed." << std::endl;
    }
    else
    {
        std::cerr << "fuzzString test failed." << std::endl;
    }
}

/// @brief The testFuzzer function \name testFuzzer, this will be used to test the file Fuzzer
void testFuzzFile()
{
    std::string inputFileName = "test.txt"; // Provide an existing test file name
    std::string cppFuzzerPath = findExecutablePath();
    std::vector<char*> args = {const_cast<char*>(cppFuzzerPath.c_str()), const_cast<char*>("2"), const_cast<char*>(inputFileName.c_str()), nullptr};

    int result = RunExternalProcess(args);

    if (result == 0)
    {
        std::cout << "fuzzFile test passed." << std::endl;
    }
    else
    {
        std::cerr << "fuzzFile test failed." << std::endl;
    }
}

/// @brief The testFuzzer function \name testFuzzer, this will be used to test the folder Fuzzer
void testFuzzFolder()
{
    std::string inputFolderName = "testData"; // Provide an existing test folder name
    std::string cppFuzzerPath = findExecutablePath();
    std::vector<char*> args = {const_cast<char*>(cppFuzzerPath.c_str()), const_cast<char*>("1"), const_cast<char*>(inputFolderName.c_str()), nullptr};

    int result = RunExternalProcess(args);

    if (result == 0)
    {
        std::cout << "fuzzFolder test passed." << std::endl;
    }
    else
    {
        std::cerr << "fuzzFolder test failed." << std::endl;
    }
}

/// @brief This is the main function \name main, this will be used to run the tests
/// @return This will return 0 if all tests pass, and 1 if any test fails
int main()
{
    try
    {
        // Run the tests
        testFuzzString();
        testFuzzFile();
        testFuzzFolder();
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
