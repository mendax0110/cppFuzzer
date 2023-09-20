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
#include "../src/includes/fuzzer.h"

/// @brief The testFuzzer function \name testFuzzer, this will be used to test the string Fuzzer
void testFuzzString()
{
    std::string inputString = "Hello, World!";
    cppFuzzer::cppFuzzerInternals fuzzer; // Create an instance of the class
    int result = fuzzer.fuzzString(inputString); // Call the member function on the instance

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
    cppFuzzer::cppFuzzerInternals fuzzer; // Create an instance of the class
    int result = fuzzer.fuzzFile(inputFileName); // Call the member function on the instance

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
    cppFuzzer::cppFuzzerInternals fuzzer; // Create an instance of the class
    int result = fuzzer.fuzzFolder(inputFolderName); // Call the member function on the instance

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
int RunFuzzerTests()
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
