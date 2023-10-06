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

using namespace std;
using namespace setupFuzzer;

/// @brief This is the test function for the setupFuzzer, \name testSetupFuzzer
/// @return This function returns 0 if the test passed, 1 if the test failed
int testSetupFuzzer() 
{
    // Create an instance of setupFuzzerInternals
    setupFuzzerInternals fuzzer;

    // Call the setupFuzzer method
    fuzzer.setupFuzzer();

    // Check if the fuzzer is running
    if (fuzzer.isRunning()) 
    {
        cout << "Fuzzer setup test passed." << endl;
        return 0; // Test passed
    } 
    else 
    {
        cerr << "Fuzzer setup test failed." << endl;
        return 1; // Test failed
    }
}

/// @brief This is the test function for the setupFuzzer, \name RunSetupFuzzerTests
/// @return This will return 0 if all tests passed, 1 if any test failed
int main() 
{
    try
    {
       testSetupFuzzer();
       return 0;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}