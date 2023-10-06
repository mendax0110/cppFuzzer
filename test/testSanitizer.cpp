/**
 * @file testSanitizer.cpp
 * @author Adrian Goessl
 * @brief This is the test file for the sanitizer
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "../src/includes/sanitizer.h"

using namespace std;
using namespace sanitizer;

/// @brief This is the test function for the sanitizer, \name testSanitizer
/// @return This will return 0 if the test passed, 1 if the test failed
int testSanitizer()
{
    // use the sanitizerInternals class, to test the private methods
    sanitizerInternals sanitizer;

    // test the runSanitizer method
    if (sanitizer.runSanitizer(sanitizerInternals::sanitizerType::addressSanitizer, "test.cpp") == 0)
    {
        cout << "Sanitizer test passed." << endl;
        return 0; // Test passed
    }
    else
    {
        cerr << "Sanitizer test failed." << endl;
        return 1; // Test failed
    }
}

/// @brief This is the main function for the test sanitizer file, \name main
/// @return This will return 0 if all tests passed, 1 if any test failed
int main()
{
    try
    {
        testSanitizer();
        return 0;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}
