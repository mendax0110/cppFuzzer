/**
 * @file fuzzer.cpp
 * @author Adrian Goessl
 * @brief Functions for the fuzzer
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/fuzzer.h"

using namespace std;
using namespace cppFuzzer;
namespace fs = std::filesystem;

/// @brief Fuzz the given string, \name fuzzString
/// @param fileString This string will be fuzzed
/// @return The fuzzed string
int cppFuzzer::cppFuzzerInternals::fuzzString(string fileString)
{
    fuzzStringRunning = true;

    try
    {
        if (fileString.empty())
        {
            throw runtime_error("File string is empty");
        }

        // Initialize a random number generator
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distribution(0, 25);

        // Create a vector to store fuzzed strings
        vector<string> fuzzedStrings;

        // Perform 10 random mutations
        for (int i = 0; i < 10; ++i)
        {
            string fuzzedString = fileString;  // Make a copy of the original string

            // Perform a random mutation (e.g., character substitution)
            int position = distribution(gen);
            char mutatedChar = 'A' + position;
            fuzzedString[rand() % fuzzedString.size()] = mutatedChar;

            // Add the fuzzed string to the vector
            fuzzedStrings.push_back(fuzzedString);
        }

        cout << "Fuzzing the string:" << endl;

        // Print the fuzzed strings
        for (const string& fuzzedString : fuzzedStrings)
        {
            cout << fuzzedString << endl;
        }
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

/// @brief Fuzz a given file, \name fuzzFile
/// @param fileName The file to fuzz
/// @return The fuzzed file
int cppFuzzer::cppFuzzerInternals::fuzzFile(string fileName)
{
    fuzzFileRunning = true;

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

        // Initialize a random number generator
        random_device rd;
        mt19937 gen(rd());
        shuffle(fileContent.begin(), fileContent.end(), gen);

        // Close the input file
        inputFile.close();

        // Write the modified content back to the same file
        ofstream outputFile(fileName);

        if (!outputFile.is_open())
        {
            throw runtime_error("Failed to open the output file");
        }

        outputFile << fileContent;
        outputFile.close();

        cout << "-------------------------------------------------------------------------\n";
        cout << "Fuzzing the file: " << fileName << endl;
        cout << "{ \"result\": \"Fuzzed file: " << fileName << "\" }" << endl;
        cout << "-------------------------------------------------------------------------\n";
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

/// @brief Fuzz a given folder, \name fuzzFolder
/// @param folderName The folder to fuzz
/// @return The fuzzed folder
int cppFuzzer::cppFuzzerInternals::fuzzFolder(string folderName)
{
    fuzzFolderRunning = true;

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

                // Initialize a random number generator
                random_device rd;
                mt19937 gen(rd());
                shuffle(fileContent.begin(), fileContent.end(), gen);

                // Close the input file
                inputFile.close();

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

        cout << "-------------------------------------------------------------------------\n";
        cout << "Fuzzing the folder: " << folderName << endl;
        cout << "{ \"result\": \"Fuzzed folder: " << folderName << "\" }" << endl;
        cout << "-------------------------------------------------------------------------\n";
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

/// @brief Cleanup the fuzzer, \name cleanup
/// @return The cleanup result
int cppFuzzer::cppFuzzerInternals::cleanup()
{
    try
    {
        if(fuzzStringRunning || fuzzFileRunning || fuzzFolderRunning)
        {
            // TODO: Cleanup the methods
        }
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