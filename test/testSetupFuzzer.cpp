/**
 * @file testSetupFuzzer.cpp
 * @author Adrian Goessl
 * @brief Simple test for the setupFuzzer
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/setupFuzzer.h"
#include <iostream>
#include <ctime>

/// @brief This is the test function for the setupFuzzer, \fn testSetupFuzzer
/// @return This function returns 0 if the test passed, 1 if the test failed
int testSetupFuzzer() 
{
    using namespace setupFuzzer;

    // Create an instance of setupFuzzerInternals
    setupFuzzerInternals fuzzer;

    // Call the setupFuzzer method
    fuzzer.setupFuzzer();

    // Check if the fuzzer is running
    if (fuzzer.isRunning()) 
    {
        std::cout << "Fuzzer setup test passed." << std::endl;
        return 0; // Test passed
    } 
    else 
    {
        std::cerr << "Fuzzer setup test failed." << std::endl;
        return 1; // Test failed
    }
}

/// @brief This is the test function for the setupFuzzer, \fn RunSetupFuzzerTests
/// @return This will return the testSetupFuzzer function
int RunSetupFuzzerTests() 
{
    return testSetupFuzzer();
}