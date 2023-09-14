// Header file for the cppMain classes and functions
#include <iostream>

#ifndef  CPPFUZZER_H

#endif // CPPFUZZER_H

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

    };
};

