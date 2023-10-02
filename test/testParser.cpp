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

int main();

// Function to find the path to the cppParser executable based on the relative location
std::string findExecutablePath()
{
    return std::string("../cppParser/build/cppFuzzer");
}

// Function to run an external process
int RunExternalProcess(const std::vector<char*>& args)
{
    // TODO: Implement the logic to execute an external process and return its exit code
    // TODO: for linux, macos and windows
    int exitCode = 0; // Replace with actual exit code
    
    return exitCode;
}

/// @brief Test the StringParser::parse method \name testStringParser
void testStringParser() 
{
    std::string input = "Test string to parse";
    cppParser::StringParser stringParser;
    int result = stringParser.parse(input);
    
    if (result == 0) 
    {
        std::cout << "StringParser::parse test passed." << std::endl;
    } 
    else 
    {
        std::cerr << "StringParser::parse test failed." << std::endl;
    }
}

/// @brief Test the FileParser::parse method \name testFileParser
void testFileParser() 
{
    std::string fileName = "test.txt"; // Provide an existing test file name
    cppParser::FileParser fileParser;
    int result = fileParser.parse(fileName);
    
    if (result == 0) 
    {
        std::cout << "FileParser::parse test passed." << std::endl;
    } 
    else 
    {
        std::cerr << "FileParser::parse test failed." << std::endl;
    }
}

/// @brief Test the FolderParser::parse method \name testFolderParser
void testFolderParser() 
{
    std::string folderName = "testData"; // Provide an existing test folder name
    cppParser::FolderParser folderParser;
    int result = folderParser.parse(folderName);
    
    if (result == 0) 
    {
        std::cout << "FolderParser::parse test passed." << std::endl;
    } 
    else 
    {
        std::cerr << "FolderParser::parse test failed." << std::endl;
    }
}

int main()
{
    // Get the path to the cppParser executable
    std::string cppParserPath = findExecutablePath();

    // Check if the executable exists
    if (std::ifstream(cppParserPath))
    {
        try
        {
            // Mock command-line arguments using std::vector
            std::vector<char*> argv = {const_cast<char*>(cppParserPath.c_str()), nullptr};
            int argc = 1;

            // Run the tests
            testStringParser();
            testFileParser();
            testFolderParser();

            return 0;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 1;
        }
    }
    else
    {
        std::cerr << "cppParser executable not found at: " << cppParserPath << std::endl;
        return 1;
    }
}