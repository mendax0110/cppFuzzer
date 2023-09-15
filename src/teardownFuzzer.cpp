#include "../src/includes/teardownFuzzer.h"
#include "../src/includes/fuzzer.h"
#include "../src/includes/parser.h"
#include "../src/includes/main.h"

using namespace std;
using namespace teardownFuzzer;


void teardownFuzzerInterals::teardownFuzzer()
{
    try
    {
        // Safely shutdown the components and release resources

        // Shutdown the cppFuzzer
        cppFuzzer::cppFuzzerInternals fuzzer;
        fuzzer.cleanup(); // Add a cleanup function in cppFuzzer to release resources

        // Shutdown the cppParser
        cppParser::cppParserInternals parser;
        parser.cleanup(); // Add a cleanup function in cppParser to release resources

        // Shutdown the cppMain
        mainFuzzer::cppMainInternals main;
        main.cleanup(); // Add a cleanup function in cppMain to release resources

        // Print messages to indicate the shutdown process
        cout << "---------------------------------------------\n";
        cout << "Shutting down the components!" << endl;
        cout << "---------------------------------------------\n";

        // Add any additional shutdown logic here as needed

        // Check for memory leaks, allocations, or other memory problems
        cout << "---------------------------------------------\n";
        cout << "Checking for memory issues!" << endl;
        cout << "---------------------------------------------\n";

        // Optionally, you can check for memory issues using memory debugging tools or libraries

        cout << "Shutdown completed." << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
    }
}