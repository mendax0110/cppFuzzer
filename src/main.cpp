/**
 * @file main.cpp
 * @author Adrian Goessl
 * @brief Main function, which calls the other functions
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/main.h"
#include "../src/includes/parser.h"
#include "../src/includes/fuzzer.h"
#include "../src/includes/setupFuzzer.h"
#include "../src/includes/teardownFuzzer.h"

using namespace std;
using namespace mainFuzzer;

/// @brief The main function for the fuzzer, which calls the other functions
/// @return The result of the main function
int main()
{
    // Callable function from cppMain, cppFuzzer, cppParser
    mainFuzzer::cppMainInternals main;
    cppFuzzer::cppFuzzerInternals fuzzer;
    cppParser::cppParserInternals parser;
    setupFuzzer::setupFuzzerInternals setupFuzzer;
    teardownFuzzer::teardownFuzzerInterals teardownFuzzer;

    try
    {
        // Create a small command-line menu to choose which folder and files to fuzz
        cout << "---------------------------------------------\n";
        cout << "Welcome to the Fuzzer Control Menu!\n";
        cout << "---------------------------------------------\n";
        cout << "Please choose an option:\n";
        cout << "---------------------------------------------\n";
        cout << "1. Fuzz all files in a specific folder\n";
        cout << "2. Fuzz a specific file\n";
        cout << "3. Stop the fuzzer\n";
        cout << "4. Close the fuzzer\n";
        cout << "---------------------------------------------\n";

        // Get user input
        int userInput;

        // Timer for shutdown
        int timerShutdown = 0;

        // Check if user input is valid
        while (true)
        {
            cin >> userInput;

            if (userInput < 1 || userInput > 4)
            {
                cout << "Please enter a valid number!\n";
            }
            else
            {
                break;
            }
        }

        // Create variables for file or folder path
        string filePath;

        // Create switch case for different operations
        switch (userInput)
        {
            case 1:
            case 2:
                // Prompt the user for the file or folder path
                cout << "Enter the file or folder path: ";
                cin >> filePath;
                break;
            case 3:
                // Stop the fuzzer
                teardownFuzzer.stopFuzzer();
                break;
            case 4:
                // Close the fuzzer, cleanup resources, and exit the program
                teardownFuzzer.teardownFuzzer();
                exit(0);
                break;
            default:
                break;
        }

        // Perform the selected operation based on userInput
        switch (userInput)
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
                break;
            case 4:
                // The fuzzer is already closed above
                break;
            default:
                break;
        }
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
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
