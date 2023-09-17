/**
 * @file parser.h
 * @author Adrian Goessl
 * @brief Header file for the parser
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#ifndef PARSER_H
#define PARSER_H

/// @brief The parser namespace \name cppParser
namespace cppParser
{
    /// @brief The cppParserInternals class, which has the public and private members \class cppParserInternals
    class cppParserInternals
    {
        public:

            int parseFile(std::string fileName);

            int parseString(std::string fileString);

            int parseFolder(std::string folderName);

            int regexParse(std::string regexString);

            int cleanup();

        private:

            // TODO: add private members
    };
};

#endif // !CPPPARSER