#include <iostream>
#include "../src/includes/parser.h"

using namespace std;
using namespace cppParser;


int cppParser::cppParserInternals::parseString(string fileString)
{
    try
    {
        if(fileString.empty())
        {
            throw "File string is empty";
            return 1;
        }

        // parse the file String and return the result
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n'; 
    }

    return 0;
}

int cppParser::cppParserInternals::parseFile(string fileName)
{
    try
    {
        if(fileName.empty())
        {
            throw "File name is empty";
            return 1;
        }

        // parse the file and return the result
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}

int cppParser::cppParserInternals::parseFolder(string folderName)
{
    try
    {
        if(folderName.empty())
        {
            throw "Folder name is empty";
            return 1;
        }

        // parse the folder and return the result
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}