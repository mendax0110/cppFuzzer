// Header file for the cppParser classes and functions
#include <iostream>

#ifndef PARSER_H
#define PARSER_H

namespace cppParser
{
    class cppParserInternals
    {
        public:

            int parseFile(std::string fileName);

            int parseString(std::string fileString);

            int parseFolder(std::string folderName);

        private:

            // TODO: add private members
    };
};

#endif // !CPPPARSER