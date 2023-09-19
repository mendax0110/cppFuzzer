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
#include <regex>

#ifndef PARSER_H
#define PARSER_H

/// @brief The parser namespace \name cppParser
namespace cppParser
{
    /// @brief The AbstractParser class, which has the public members \class AbstractParser
    class AbstractParser {
    public:
        virtual int parse(const std::string& input) = 0;
    };

    /// @brief The StringParser class, which has the public members \class StringParser
    class StringParser : public AbstractParser {
    public:
        int parse(const std::string& input) override;
    };

    /// @brief The FileParser class, which has the public members \class FileParser
    class FileParser : public AbstractParser {
    public:
        int parse(const std::string& fileName) override;
    };

    /// @brief The FolderParser class, which has the public members \class FolderParser
    class FolderParser : public AbstractParser {
    public:
        int parse(const std::string& folderName) override;
    };

    /// @brief The cppParserInternals class, which has the public and private members \class cppParserInternals
    class cppParserInternals
    {
    public:
        int parse(AbstractParser& parser, const std::string& input);
        int regexParse(std::string regexString);
        int cleanup();

    private:
        bool parseStringRunning = false;
        bool parseFileRunning = false;
        bool parseFolderRunning = false;
        bool regexParseRunning = false;
    };
}

#endif // PARSER_H
