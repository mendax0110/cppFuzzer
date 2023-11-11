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
int cppFuzzerInternals::fuzzString(string fileString)
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

        return 0;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief Fuzz a given file, \name fuzzFile
/// @param fileName The file to fuzz
/// @return The fuzzed file
int cppFuzzerInternals::fuzzFile(string fileName)
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
        uniform_int_distribution<int> distribution(0, 25);

        // Perform 10 random mutations
        for (int i = 0; i < 10; ++i)
        {
            string fuzzedString = fileContent;  // Make a copy of the original string

            // Perform a random mutation (e.g., character substitution)
            int position = distribution(gen);
            char mutatedChar = 'A' + position;
            fuzzedString[rand() % fuzzedString.size()] = mutatedChar;

            // Generate a unique filename for the fuzzed file
            stringstream fuzzedFileName;
            fuzzedFileName << "fuzzed_" << setw(4) << setfill('0') << i << "_";
            fuzzedFileName << fs::path(fileName).filename().string();

            // Write the fuzzed content to the new file
            ofstream outputFile(fuzzedFileName.str());

            if (!outputFile.is_open())
            {
                throw runtime_error("Failed to open the output file");
            }

            outputFile << fuzzedString;
            outputFile.close();

            cout << "Fuzzed file created: " << fuzzedFileName.str() << endl;
        }

        // Close the input file
        inputFile.close();

        return 0;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief Fuzz a given folder, \name fuzzFolder
/// @param folderName The folder to fuzz
/// @return The fuzzed folder
int cppFuzzerInternals::fuzzFolder(string folderName)
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
                uniform_int_distribution<int> distribution(0, 25);

                // Perform 10 random mutations
                for (int i = 0; i < 10; ++i)
                {
                    string fuzzedString = fileContent;  // Make a copy of the original string

                    // Perform a random mutation (e.g., character substitution)
                    int position = distribution(gen);
                    char mutatedChar = 'A' + position;
                    fuzzedString[rand() % fuzzedString.size()] = mutatedChar;

                    // Generate a unique filename for the fuzzed file
                    stringstream fuzzedFileName;
                    fuzzedFileName << "fuzzed_" << setw(4) << setfill('0') << i << "_";
                    fuzzedFileName << fs::path(entry.path()).filename().string();

                    // Write the fuzzed content to the new file
                    ofstream outputFile(fs::path(folderName) / fuzzedFileName.str());

                    if (!outputFile.is_open())
                    {
                        throw runtime_error("Failed to open the output file");
                    }

                    outputFile << fuzzedString;
                    outputFile.close();

                    cout << "Fuzzed file created: " << fuzzedFileName.str() << endl;
                }

                // Close the input file
                inputFile.close();
            }
        }

        return 0;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief Cleanup the fuzzer, \name cleanup
/// @return The cleanup result
int cppFuzzerInternals::cleanup()
{
    try
    {
        if (fuzzStringRunning)
        {
            // TODO: Perform cleanup for fuzzing strings (if needed)
            // reset any variables or release resources related to fuzzing strings
            cout << "Cleanup for fuzzing strings completed." << endl;
        }

        if (fuzzFileRunning)
        {
            // TODO: Perform cleanup for fuzzing files (if needed)
            // close any open files or release resources related to fuzzing files
            cout << "Cleanup for fuzzing files completed." << endl;
        }

        if (fuzzFolderRunning)
        {
            // TODO: Perform cleanup for fuzzing folders (if needed)
            // close any open files or release resources related to fuzzing folders
            cout << "Cleanup for fuzzing folders completed." << endl;
        }

        // Reset the flags indicating the status of fuzzing processes
        fuzzStringRunning = false;
        fuzzFileRunning = false;
        fuzzFolderRunning = false;

        cout << "Fuzzer cleanup complete." << endl;
        return 0;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}
