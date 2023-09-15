// Header file for the cppParser classes and functions
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

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

            int cleanup();

        private:

            // TODO: add private members
    };
};

#endif // !CPPPARSER