/**
 * @file testAPI.cpp
 * @author Adrian Goessl
 * @brief This is the test which will test the API
 * @version 0.1
 * @date 2023-11-24
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include "../src/includes/fuzzerAPI.h"
#include "../external//Basic-Http-Server-cpp/html_parser.h"
#include "../external/Basic-Http-Server-cpp/main.h"

using namespace std;
using namespace fuzzerAPI;

/// @brief This is the method to set the findExecutablePath, \name findExecutablePath
/// @return This will return the path to the executable
string findExecutablePath()
{
    return "../cppFuzzer/build/cppFuzzer";
}

/// @brief This is the method to call the 
/// @param args This is the vector of arguments
/// @return This will return the exit code
int RunEternalProcess(const vector<char*>& args)
{
    int exitCode = 0;

    return exitCode;
}

/// @brief This is the method to test the fuzzerAPI, \name testFuzzerAPI
/// @return This will return 0 if the test passed, 1 if the test failed
int testFuzzerAPI()
{
    fuzzerAPIInterals fuzzerAPI;

    fuzzerAPI.FuzzerAPI();

    return 0;
}

/// @brief This is the method to call the testFuzzerAPI, \name main
/// @return This will return 0 if the test passed, 1 if the test failed
int main()
{
    try
    {
        testFuzzerAPI();
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    } 
}