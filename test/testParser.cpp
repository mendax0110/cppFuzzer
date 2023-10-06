/**
 * @file testParser.cpp
 * @author Adrian Goessl
 * @brief Simple test for the parser
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "../src/includes/parser.h"

using namespace std;
using namespace cppParser;

int main();

/// @brief Function to find the path to the cppParser executable based on the relative location \name findExecutablePath
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

/// @brief Test the StringParser::parse method \name testStringParser
/// @return This will return 0 if the test passed, 1 if the test failed
int testStringParser() 
{
    string input = "Test string to parse";
    cppParser::StringParser stringParser;
    int result = stringParser.parse(input);
    
    if (result == 0) 
    {
        cout << "StringParser::parse test passed." << endl;
        return 0;
    } 
    else 
    {
        cerr << "StringParser::parse test failed." << endl;
        return 1;
    }
}

/// @brief Test the FileParser::parse method \name testFileParser
/// @return This will return 0 if the test passed, 1 if the test failed
int testFileParser() 
{
    string fileName = "test.txt"; // Provide an existing test file name
    cppParser::FileParser fileParser;
    int result = fileParser.parse(fileName);
    
    if (result == 0) 
    {
        cout << "FileParser::parse test passed." << endl;
        return 0;
    } 
    else 
    {
        cerr << "FileParser::parse test failed." << endl;
        return 1;
    }
}

/// @brief Test the FolderParser::parse method \name testFolderParser
/// @return This will return 0 if the test passed, 1 if the test failed
int testFolderParser() 
{
    string folderName = "testData"; // Provide an existing test folder name
    cppParser::FolderParser folderParser;
    int result = folderParser.parse(folderName);
    
    if (result == 0) 
    {
        cout << "FolderParser::parse test passed." << endl;
        return 0;
    } 
    else 
    {
        cerr << "FolderParser::parse test failed." << endl;
        return 1;
    }
}

/// @brief This is the main function for the test parser file, \name main
/// @return This will return 0 if all tests passed, 1 if any test failed
int main()
{
    // Get the path to the cppParser executable
    string cppParserPath = findExecutablePath();

    // Check if the executable exists
    if (ifstream(cppParserPath))
    {
        try
        {
            // Mock command-line arguments using std::vector
            vector<char*> argv = {const_cast<char*>(cppParserPath.c_str()), nullptr};
            int argc = 1;

            // Run the tests
            testStringParser();
            testFileParser();
            testFolderParser();

            return 0;
        }
        catch(const exception& e)
        {
            cerr << e.what() << '\n';
            return 1;
        }
    }
    else
    {
        cerr << "cppParser executable not found at: " << cppParserPath << endl;
        return 1;
    }
}