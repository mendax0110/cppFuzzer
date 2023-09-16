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

        int fuzzFile(std::string fileName); // TODO: add fuzzedFile as output

        int fuzzString(std::string fileString); // TODO: add fuzzedString as output

        int fuzzFolder(std::string folderName); // TODO: add fuzzedFolder as output

        int cleanup();
            
    private:

        // TODO: add private members

    };
};

#endif // CPPFUZZER_H