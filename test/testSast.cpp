/**
 * @file testSast.cpp
 * @author Adrian Goessl
 * @brief This is the test file for the sast
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../src/includes/sast.h"

using namespace std;
using namespace sast;

/// @brief This is the test function for the sast, \name testSast
/// @return This will return 0 if the test passed, 1 if the test failed
int testSast()
{
    // use the sastInternals class, to test the private methods
    sastInternals sast;

    // test the runSast method
    if (sast.runSast("test.cpp") == 0)
    {
        cout << "Sast test passed." << endl;
        return 0; // Test passed
    }
    else
    {
        cerr << "Sast test failed." << endl;
        return 1; // Test failed
    }
}

/// @brief This is the main function for the test sast file, \name main
/// @return This will return 0 if all tests passed, 1 if any test failed
int main()
{
    try
    {
        testSast();
        return 0;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}