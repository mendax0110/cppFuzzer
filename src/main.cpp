/*! \mainpage C++ Fuzzer
 *
 * \section intro_sec Introduction:
 *
 * This is a simple C/C++ fuzzer, which is used to fuzz C/C++ programs.
 * There are two main components of the fuzzer: the parser and the fuzzer.
 * The parser is used to parse the C/C++ program, and the fuzzer is used to fuzz the C/C++ program.
 * The setupFuzzer and teardownFuzzer are used to setup and teardown the fuzzer.
 * The main function is used to call the other functions.
 *
 * \section usage HowtoUse:
 *
 * \subsection arguments Command-line arguments and examples 
 * 
 * 1. Fuzz all files in a specific folder
 * 2. Fuzz a specific file
 * 3. Stop the fuzzer
 * 4. Close the fuzzer
 * 
 * Example:
 * ./cppFuzzer 1 /home/user/folder
 * 
 * @file main.cpp
 * @author Adrian Goessl
 * @brief Main function, which calls the other functions
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
*/
#include "../src/includes/main.h"
#include "../src/includes/parser.h"
#include "../src/includes/fuzzer.h"
#include "../src/includes/setupFuzzer.h"
#include "../src/includes/teardownFuzzer.h"

using namespace std;
using namespace mainFuzzer;

/// @brief This is the main function, which calls the other functions
/// @param argc This is the number of command-line arguments
/// @param argv This is an array of command-line arguments
/// @return This method returns 0 for success and 1 for failure
int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "----------------------------------------------------------\n";
        cerr << "Usage: " << argv[0] << " <operation> [file_or_folder_path]" << endl;
        cerr << "----------------------------------------------------------\n";
        cerr << "Operations:\n";
        cerr << "----------------------------------------------------------\n";
        cerr << "1. Fuzz all files in a specific folder\n";
        cerr << "2. Fuzz a specific file\n";
        cerr << "3. Stop the fuzzer\n";
        cerr << "4. Close the fuzzer\n";
        cerr << "----------------------------------------------------------\n";
        return 1;
    }

    int operation = atoi(argv[1]);

    // Callable functions from cppMain, cppFuzzer, cppParser, setupFuzzer, teardownFuzzer
    mainFuzzer::cppMainInternals main;
    cppFuzzer::cppFuzzerInternals fuzzer;
    cppParser::cppParserInternals parser;
    setupFuzzer::setupFuzzerInternals setupFuzzer;
    teardownFuzzer::teardownFuzzerInterals teardownFuzzer;

    // Declare parser instances here to avoid jumping over variable initialization
    cppParser::FolderParser folderParser;
    cppParser::FileParser fileParser;

    try
    {
        // Create variables for file or folder path
        string filePath;

        if (argc > 2)
        {
            filePath = argv[2];
        }

        if (!setupFuzzer.isRunning()) 
        {
            cerr << "Fuzzer setup failed. Exiting." << std::endl;
            return 1;
        }

        switch (operation)
        {
            case 1:
                // Initialize any necessary resources
                setupFuzzer.setupFuzzer();

                // Parse a specific folder using the FolderParser
                parser = cppParser::cppParserInternals();
                parser.parse(folderParser, filePath);

                // Fuzz all files in a specific folder
                fuzzer = cppFuzzer::cppFuzzerInternals();
                fuzzer.fuzzFolder(filePath);

                // Cleanup resources and stop the fuzzer
                teardownFuzzer.teardownFuzzer();
                break;
            case 2:
                // Initialize any necessary resources
                setupFuzzer.setupFuzzer();

                // Parse a specific file using the FileParser
                parser = cppParser::cppParserInternals();
                parser.parse(fileParser, filePath);

                // Fuzz a specific file
                fuzzer = cppFuzzer::cppFuzzerInternals();
                fuzzer.fuzzFile(filePath);

                // Cleanup resources and stop the fuzzer
                teardownFuzzer.teardownFuzzer();
                break;
            case 3:
                // Stop the fuzzer if it's running
                teardownFuzzer.stopFuzzer();
                break;
            case 4:
                // Close the fuzzer, cleanup resources, and exit the program
                teardownFuzzer.teardownFuzzer();
                break;
            default:
                cerr << "Invalid operation: " << operation << endl;
                break;
        }
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
    return 0;
}

/// @brief This is the cleanup method
/// @return This will return 0 for success and 1 for failure
int mainFuzzer::cppMainInternals::cleanup()
{
    try
    {
        // Cleanup resources
        if (fileHandle != nullptr)
        {
            fclose(fileHandle);
            fileHandle = nullptr;
        }

        // Cleanup dynamic memory
        if (dynamicArray != nullptr)
        {
            delete[] dynamicArray;
            dynamicArray = nullptr;
        }

        cout << "Cleanup complete." << endl;

        return 0;
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}
