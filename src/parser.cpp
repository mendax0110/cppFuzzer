/**
 * @file parser.cpp
 * @author Adrian Goessl
 * @brief Parser implementation
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/parser.h"

using namespace std;
using namespace cppParser;
namespace fs = std::filesystem;

/// @brief This method parses a string, \fn parse
/// @param input This is the input string
/// @return This method returns 0 for success and 1 for failure
int StringParser::parse(const string& input)
{
    cout << "--------------------------------------------------\n";
    cout << "Parsing string: " << input << endl;
    cout << "{ \"parsedResult\": \"Parsed string\" }" << endl;
    cout << "--------------------------------------------------\n";
    return 0;
}

/// @brief This method parses a file, \fn parse
/// @param fileName This is the file name
/// @return This method returns 0 for success and 1 for failure
int FileParser::parse(const string& fileName)
{
    try 
    {
        if (fileName.empty()) 
        {
            throw runtime_error("File name is empty");
        }

        // Open the input file
        ifstream inputFile(fileName);

        if (!inputFile.is_open())
        {
            throw runtime_error("Failed to open the input file");
        }

        // Read the content of the file into a string
        stringstream buffer;
        buffer << inputFile.rdbuf();
        string fileContent = buffer.str();

        cout << "-------------------------------------------------------------------------\n";
        cout << "Parsing file: " << fileName << endl;

        inputFile.close();

        cout << "{ \"parsedResult\": \"Parsed file: " << fileName << "\" }" << endl;
        cout << "-------------------------------------------------------------------------\n";

        return 0;
    } 
    catch (const exception& e) 
    {
        cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This method parses a folder, \fn parse
/// @param folderName This is the folder name
/// @return This method returns 0 for success and 1 for failure
int FolderParser::parse(const string& folderName)
{
    try
    {
        if (folderName.empty()) 
        {
            throw runtime_error("Folder name is empty");
        }

        int fileCount = 0;
        for (const auto& entry : fs::directory_iterator(folderName)) 
        {
            if (entry.is_regular_file()) 
            {
                fileCount++;
            }
        }
        cout << "-------------------------------------------------------------------------------------------------\n";
        cout << "Parsing the folder: " << folderName << endl;
        cout << "{ \"parsedResult\": \"Parsed folder: " << folderName << "\", \"fileCount\": " << fileCount << " }" << endl;
        cout << "-------------------------------------------------------------------------------------------------\n";

        return 0;
    } 
    catch (const exception& e) 
    {
        cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This is the default constructor, \fn cppParserInternals
/// @param parser This is the parser which will be chosen by the user
/// @param input This is the input string or the file name or the folder name
/// @return This will return the parsed string or the parsed file or the parsed folder
int cppParserInternals::parse(AbstractParser& parser, const string& input)
{
    parseStringRunning = true;
    return parser.parse(input);
}

/// @brief This is regex parser, \fn regexParse
/// @param regexString This is the regex string
/// @return This will return 0 for success and 1 for failure
int cppParserInternals::regexParse(string regexString)
{
    regexParseRunning = true;

    try
    {
        if (regexString.empty()) 
        {
            throw runtime_error("Regex string is empty");
        }

        // TODO: add regex parsing logic here

        cout << "Parsing regex string: " << regexString << endl;

        cout << "{ \"parsedResult\": \"Parsed regex string\" }" << endl;
    } 
    catch (const exception& e) 
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

/// @brief This is the cleanup method, \fn cleanup
/// @return This will return 0 for success and 1 for failure
int cppParserInternals::cleanup()
{
    try 
    {
        if (parseStringRunning || parseFileRunning || parseFolderRunning || regexParseRunning) 
        {
            // TODO: add cleanup logic here as needed
        }

        // Print a message to indicate successful cleanup
        cout << "Cleanup complete." << endl;

        return 0; // Return 0 for success
    } 
    catch (const exception& e) 
    {
        cerr << e.what() << '\n';
        return 1; // Return 1 for failure
    }
}
