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
 * \section Usage of the cppFuzzer:
 *
 * \subsection Command-line arguments and examples: 
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

/// @brief The main function for the fuzzer, which calls the other functions
/// @param argc This is the number of arguments
/// @param argv This is the array of arguments
/// @return This returns the result of the main function
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

    // Callable function from cppMain, cppFuzzer, cppParser
    mainFuzzer::cppMainInternals main;
    cppFuzzer::cppFuzzerInternals fuzzer;
    cppParser::cppParserInternals parser;
    setupFuzzer::setupFuzzerInternals setupFuzzer;
    teardownFuzzer::teardownFuzzerInterals teardownFuzzer;

    try
    {
        // Create variables for file or folder path
        string filePath;

        if (argc > 2)
        {
            filePath = argv[2];
        }

        // Perform the selected operation based on the command-line argument
        switch (operation)
        {
            case 1:
                // Initialize any necessary resources
                setupFuzzer.setupFuzzer();
                parser = cppParser::cppParserInternals();
                parser.parseFolder(filePath);
                // Fuzz all files in a specific folder
                fuzzer = cppFuzzer::cppFuzzerInternals();
                fuzzer.fuzzFolder(filePath);
                // Cleanup resources and stop the fuzzer
                teardownFuzzer.teardownFuzzer();
                break;
            case 2:
                // Initialize any necessary resources
                setupFuzzer.setupFuzzer();
                // Parse a specific file
                parser = cppParser::cppParserInternals();
                parser.parseFile(filePath);
                // Fuzz a specific file
                fuzzer = cppFuzzer::cppFuzzerInternals();
                fuzzer.fuzzFile(filePath);
                // Cleanup resources and stop the fuzzer
                teardownFuzzer.teardownFuzzer();
                break;
            case 3:
                // Add logic to stop the fuzzer if it's running
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

/// @brief Cleanup the Main
/// @return The cleanup result
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
