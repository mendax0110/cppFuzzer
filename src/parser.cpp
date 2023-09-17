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


/// @brief Parse the input string
/// @param fileString The input string to parse
/// @return The parsed string
int cppParser::cppParserInternals::parseString(string fileString)
{
    parseStringRunning = true;

    try
    {
        if (fileString.empty())
        {
            throw runtime_error("File string is empty");
        }

        cout << "--------------------------------------------------\n";
        cout << "Parsing JSON string: " << fileString << endl;

        cout << "{ \"parsedResult\": \"Parsed JSON string\" }" << endl;
        cout << "--------------------------------------------------\n";
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

/// @brief Parse the input file
/// @param fileName The input file to parse
/// @return The parsed file
int cppParser::cppParserInternals::parseFile(string fileName)
{
    parseFileRunning = true;

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
        cout << "Parsing XML file: " << fileName << endl;

        inputFile.close();

        cout << "{ \"parsedResult\": \"Parsed XML file: " << fileName << "\" }" << endl;
        cout << "-------------------------------------------------------------------------\n";
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

/// @brief Parse the input folder
/// @param folderName The input folder to parse
/// @return The parsed folder
int cppParser::cppParserInternals::parseFolder(string folderName)
{
    parseFolderRunning = true;

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
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

/// @brief Parse the input regex string
/// @param regexString The input regex string to parse
/// @return The parsed regex string
int cppParser::cppParserInternals::regexParse(string regexString)
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

/// @brief Cleanup the Parser
/// @return The cleanup result
int cppParser::cppParserInternals::cleanup()
{
    try
    {
        if(parseStringRunning || parseFileRunning || parseFolderRunning || regexParseRunning)
        {
            // TODO: add cleanup logic here as needed
        }

        // Print a message to indicate successful cleanup
        cout << "Cleanup complete." << endl;

        return 0; // Return 0 for success
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1; // Return 1 for failure
    }
}



