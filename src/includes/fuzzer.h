// Header file for the cppMain classes and functions
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <filesystem>

#ifndef  FUZZER_H
#define  FUZZER_H

// name for cppFuzzer classes and functions
namespace cppFuzzer 
{
    class cppFuzzerInternals
    {
    public:

        int fuzzFile(std::string fileName);

        int fuzzString(std::string fileString);

        int fuzzFolder(std::string folderName);

        int cleanup();
            
    private:

        // TODO: add private members

    };
};

#endif // CPPFUZZER_H