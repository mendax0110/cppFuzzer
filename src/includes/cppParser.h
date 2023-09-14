// Header file for the cppParser classes and functions
#include <iostream>

#ifndef CPPPARSER_H

#endif // !CPPPARSER

namespace cppParser
{
    class cppParserInternals
    {
        public:

            int parseFile(std::string fileName);

            int parseString(std::string fileString);

            int parseFolder(std::string folderName);

        private:
    };
};