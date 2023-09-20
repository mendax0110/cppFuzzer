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
#include "../src/includes/parser.h"

/// @brief Test the StringParser::parse method \fn testStringParser
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

/// @brief Test the FileParser::parse method \fn testFileParser
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

/// @brief Test the FolderParser::parse method \fn testFolderParser
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

/// @brief This is the main method \fn main, this will be used to run the tests
/// @return This method returns 0 for success and 1 for failure
int RunParserTests() 
{
    try
    {
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
