#include "../src/includes/parser.h"

using namespace std;
using namespace cppParser;
namespace fs = std::filesystem;


int cppParser::cppParserInternals::parseString(string fileString)
{
    try
    {
        if (fileString.empty())
        {
            throw runtime_error("File string is empty");
        }

        cout << "Parsing JSON string: " << fileString << endl;

        cout << "{ \"parsedResult\": \"Parsed JSON string\" }" << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

int cppParser::cppParserInternals::parseFile(string fileName)
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

        cout << "Parsing XML file: " << fileName << endl;

        inputFile.close();

        cout << "{ \"parsedResult\": \"Parsed XML file: " << fileName << "\" }" << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

int cppParser::cppParserInternals::parseFolder(string folderName)
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

        cout << "{ \"parsedResult\": \"Parsed folder: " << folderName << "\", \"fileCount\": " << fileCount << " }" << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

int cppParser::cppParserInternals::cleanup()
{
    try
    {
        // TODO: add cleanup logic here as needed
        /*if (inputFile.is_open())
        {
            inputFile.close();
        }*/

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



