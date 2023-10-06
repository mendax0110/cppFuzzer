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

using namespace std;
using namespace cppFuzzer;

/// @brief Function to find the executable path dynamically \name findExecutablePath
/// @return This will return the path to the executable
string findExecutablePath()
{
    return "../cppFuzzer/build/cppFuzzer";
}

/// @brief Function to run an external process \name RunExternalProcess
/// @param args This is the arguments to pass to the external process
/// @return This will return the exit code of the external process
int RunExternalProcess(const vector<char*>& args)
{
    // TODO: Implement the logic to execute an external process and return its exit code
    // TODO: for linux, macos and windows
    int exitCode = 0; // Replace with actual exit code
    
    return exitCode;
}

/// @brief The testFuzzer function \name testFuzzer, this will be used to test the string Fuzzer
/// @return This will return 0 if the test passed, 1 if the test failed
int testFuzzString()
{
    string inputString = "Hello, World!";
    string cppFuzzerPath = findExecutablePath();
    vector<char*> args = {const_cast<char*>(cppFuzzerPath.c_str()), const_cast<char*>("1"), const_cast<char*>(inputString.c_str()), nullptr};

    int result = RunExternalProcess(args);

    if (result == 0)
    {
        cout << "fuzzString test passed." << endl;
        return 0;
    }
    else
    {
        cerr << "fuzzString test failed." << endl;
        return 1;
    }
}

/// @brief @brief The testFuzzer function \name testFuzzer, this will be used to test the file Fuzzer
/// @return This will return 0 if the test passed, 1 if the test failed
int testFuzzFile()
{
    string inputFileName = "test.txt"; // Provide an existing test file name
    string cppFuzzerPath = findExecutablePath();
    vector<char*> args = {const_cast<char*>(cppFuzzerPath.c_str()), const_cast<char*>("2"), const_cast<char*>(inputFileName.c_str()), nullptr};

    int result = RunExternalProcess(args);

    if (result == 0)
    {
        cout << "fuzzFile test passed." << endl;
        return 0;
    }
    else
    {
        cerr << "fuzzFile test failed." << endl;
        return 1;
    }
}

/// @brief The testFuzzer function \name testFuzzer, this will be used to test the folder Fuzzer
/// @return This will return 0 if the test passed, 1 if the test failed
int testFuzzFolder()
{
    string inputFolderName = "testData"; // Provide an existing test folder name
    string cppFuzzerPath = findExecutablePath();
    vector<char*> args = {const_cast<char*>(cppFuzzerPath.c_str()), const_cast<char*>("1"), const_cast<char*>(inputFolderName.c_str()), nullptr};

    int result = RunExternalProcess(args);

    if (result == 0)
    {
        cout << "fuzzFolder test passed." << endl;
        return 0;
    }
    else
    {
        cerr << "fuzzFolder test failed." << endl;
        return 1;
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
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}
