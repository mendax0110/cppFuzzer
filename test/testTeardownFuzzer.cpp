/**
 * @file testTeardownFuzzer.cpp
 * @author Adrian Goessl
 * @brief Simple test for the teardownFuzzer
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
//#include <iostream>
#include "../src/includes/teardownFuzzer.h"
//#include "../src/includes/fuzzer.h"
//#include "../src/includes/parser.h"
//#include "../src/includes/main.h"

using namespace std;
using namespace teardownFuzzer;

/// @brief This is the test function for the teardownFuzzer, \name testTeardownFuzzer
/// @return This will return 0 if the test passed, 1 if the test failed
int testTeardownFuzzer() 
{
    try 
    {
        // Create an instance of teardownFuzzerInternals
        teardownFuzzerInterals teardownFuzzer;

        // Call the stopFuzzer method
        teardownFuzzer.stopFuzzer();

        // Call the teardownFuzzer method
        teardownFuzzer.teardownFuzzer();

        cout << "Teardown Fuzzer tests passed." << endl;
        return 0; // Tests passed
    } 
    catch (const exception& e) 
    {
        cerr << "Teardown Fuzzer tests failed: " << e.what() << '\n';
        return 1; // Tests failed
    }
}

/// @brief This is the test function for the teardownFuzzer, \name RunTeardownFuzzerTests
/// @return This will return the testTeardownFuzzer function
int test() 
{
    try
    {
        testTeardownFuzzer();
        return 0;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}