#include "../src/includes/main.h"
#include "../src/includes/parser.h"
#include "../src/includes/fuzzer.h"
#include "../src/includes/setupFuzzer.h"
#include "../src/includes/teardownFuzzer.h"

using namespace std;
using namespace mainFuzzer;

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
        printf("---------------------------------------------\n");
        printf("Welcome to the Fuzzer Control Menu!\n");
        printf("---------------------------------------------\n");
        printf("Please choose an option:\n");
        printf("---------------------------------------------\n");
        printf("1. Fuzz all files in a specific folder\n");
        printf("2. Fuzz a specific file\n");
        printf("3. Stop the fuzzer\n");
        printf("4. Close the fuzzer\n");
        printf("---------------------------------------------\n");

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
                printf("Please enter a valid number!\n");
            }
            else
            {
                break;
            }
        }

        // Create variables for file or folder path
        string filePath;

        // Prompt the user for the file or folder path
        cout << "Enter the file or folder path: ";
        cin >> filePath;

        // Create switch case for different operations
        switch (userInput)
        {
            case 1:
                // Fuzz all files in a specific folder
                setupFuzzer.setupFuzzer(); // Initialize any necessary resources
                parser = cppParser::cppParserInternals();
                parser.parseFolder(filePath);

                fuzzer = cppFuzzer::cppFuzzerInternals();
                fuzzer.fuzzFolder(filePath);

                teardownFuzzer.teardownFuzzer(); // Cleanup resources and stop the fuzzer
                break;
            case 2:
                // Fuzz a specific file
                setupFuzzer.setupFuzzer(); // Initialize any necessary resources
                parser = cppParser::cppParserInternals();
                parser.parseFile(filePath);

                fuzzer = cppFuzzer::cppFuzzerInternals();
                fuzzer.fuzzFile(filePath);

                teardownFuzzer.teardownFuzzer(); // Cleanup resources and stop the fuzzer
                break;
            case 3:
                // Stop the fuzzer
                // Add logic to stop the fuzzer if it's running
                break;
            case 4:
                // Close the fuzzer
                teardownFuzzer.teardownFuzzer(); // Cleanup resources and stop the fuzzer
                printf("Closing the fuzzer...\n");
                exit(0);
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

int mainFuzzer::cppMainInternals::cleanup()
{
    try
    {
        if (fileHandle != nullptr)
        {
            fclose(fileHandle);
            fileHandle = nullptr;
        }

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
