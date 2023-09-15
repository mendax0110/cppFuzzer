#include <iostream>
#include "../src/includes/fuzzer.h"

using namespace std;
using namespace cppFuzzer;


int cppFuzzer::cppFuzzerInternals::fuzzString(string fileString)
{
    try
    {
        if(fileString.empty())
        {
            throw "File string is empty";
            return 1;
        }

        // fuzz the file String and return the result, listed as JSON format
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}

int cppFuzzer::cppFuzzerInternals::fuzzFile(string fileName)
{
    try
    {
        if(fileName.empty())
        {
            throw "File name is empty";

            return 1;
        }
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}

int cppFuzzer::cppFuzzerInternals::fuzzFolder(string folderName)
{
    try
    {
        if(folderName.empty())
        {
            throw "Folder name is empty";
            return 1;
        }

        // fuzz the folder and return the result, listed as JSON format
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}