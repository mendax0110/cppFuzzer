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

    try
    {
        // create small commandline menue, to choose which folder and files to fuzz
        printf("---------------------------------------------\n");
        printf("Welcome to the setupFuzzer menue!\n");
        printf("---------------------------------------------\n");
        printf("Please choose which folder and files to fuzz:\n");
        printf("---------------------------------------------\n");
        printf("1. fuzz all files in a specific folder\n");
        printf("2. fuzz a specific file\n");
        printf("3. Stop the fuzzer\n");
        printf("4. Close the fuzzer\n");
        printf("---------------------------------------------\n");

        // get user input
        int userInput;

        // timer for shutdown
        int timerShutdown = 0;

        // check if user input is valid
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

        // create switch case for different operations
        switch (userInput)
        {
            case 1:
                // fuzz all files in a specific folder
                parser = cppParser::cppParserInternals();
                parser.parseFolder("");

                fuzzer = cppFuzzer::cppFuzzerInternals();
                fuzzer.fuzzFolder("");
                break;
            case 2:
               // fuzz all files in the current folder
                parser = cppParser::cppParserInternals();
                parser.parseFile("");

                fuzzer = cppFuzzer::cppFuzzerInternals();
                fuzzer.fuzzFile("");
                break;
            case 3:
                // stop the fuzzer
                teardownFuzzer::teardownFuzzerInterals();
                break;
            case 4:
                // Close the fuzzer
                teardownFuzzer::teardownFuzzerInterals();
                // count to 5 to give the teardownFuzzer some time to close the fuzzer
                while (timerShutdown < 5)
                {
                    timerShutdown++;
                    printf("Closing the fuzzer in %d seconds\n", timerShutdown);
                }
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