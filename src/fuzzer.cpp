#include "../src/includes/fuzzer.h"

using namespace std;
using namespace cppFuzzer;
namespace fs = std::filesystem;


int cppFuzzer::cppFuzzerInternals::fuzzString(string fileString)
{
    try
    {
        if (fileString.empty())
        {
            throw runtime_error("File string is empty");
        }

        fileString = "Fuzzed: " + fileString;

        // Return the fuzzed string as a JSON format (replace with your actual result)
        cout << "{ \"result\": \"" << fileString << "\" }" << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

int cppFuzzer::cppFuzzerInternals::fuzzFile(string fileName)
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

        shuffle(fileContent.begin(), fileContent.end(), default_random_engine());

        // Close the input file
        inputFile.close();

        // Write the modified content back to the file
        ofstream outputFile(fileName);

        if (!outputFile.is_open())
        {
            throw runtime_error("Failed to open the output file");
        }

        outputFile << fileContent;
        outputFile.close();

        cout << "{ \"result\": \"Fuzzed file: " << fileName << "\" }" << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

int cppFuzzer::cppFuzzerInternals::fuzzFolder(string folderName)
{
    try
    {
        if (folderName.empty())
        {
            throw runtime_error("Folder name is empty");
        }

        for (const auto& entry : fs::directory_iterator(folderName))
        {
            if (entry.is_regular_file())
            {
                // Read the file's content
                ifstream inputFile(entry.path());
                stringstream buffer;
                buffer << inputFile.rdbuf();
                string fileContent = buffer.str();

                shuffle(fileContent.begin(), fileContent.end(), default_random_engine());

                // Write the modified content back to the file
                ofstream outputFile(entry.path());

                if (!outputFile.is_open())
                {
                    throw runtime_error("Failed to open the output file");
                }

                outputFile << fileContent;
                outputFile.close();
            }
        }

        cout << "{ \"result\": \"Fuzzed folder: " << folderName << "\" }" << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

int cppFuzzer::cppFuzzerInternals::cleanup()
{
    try
    {
        // Safely shutdown the components and release resources
        cout << "Fuzzer cleanup complete." << endl;
        return 0;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}