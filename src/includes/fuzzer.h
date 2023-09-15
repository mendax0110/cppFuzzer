// Header file for the cppMain classes and functions
#include <iostream>

#ifndef  CPPFUZZER_H
#define  CPPFUZZER_H

// name for cppFuzzer classes and functions
namespace cppFuzzer 
{
    class cppFuzzerInternals
    {
    public:

        int fuzzFile(std::string fileName);

        int fuzzString(std::string fileString);

        int fuzzFolder(std::string folderName);
            
    private:

        // TODO: add private members

    };
};

#endif // CPPFUZZER_H