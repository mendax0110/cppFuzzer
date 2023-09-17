/**
 * @file teardownFuzzer.cpp
 * @author Adrian Goessl
 * @brief Teardown the fuzzer
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/teardownFuzzer.h"
#include "../src/includes/fuzzer.h"
#include "../src/includes/parser.h"
#include "../src/includes/main.h"

using namespace std;
using namespace teardownFuzzer;

/// @brief Teardown the fuzzer
void teardownFuzzerInterals::teardownFuzzer()
{
    try
    {
        // Shutdown the cppFuzzer
        cppFuzzer::cppFuzzerInternals fuzzer;
        fuzzer.cleanup(); // Add a cleanup function in cppFuzzer to release resources

        // Shutdown the cppParser
        cppParser::cppParserInternals parser;
        parser.cleanup(); // Add a cleanup function in cppParser to release resources

        // Shutdown the cppMain
        mainFuzzer::cppMainInternals main;
        main.cleanup(); // Add a cleanup function in cppMain to release resources

        // Print messages to indicate the shutdown process, memory leaks, allocations, or other memory problems
        cout << "---------------------------------------------\n";
        cout << "Shutting down the components!" << endl;
        cout << "Checking for memory issues!" << endl;
        cout << "---------------------------------------------\n";

        cout << "Shutdown completed." << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
    }
}

/// @brief Stop the fuzzer
void teardownFuzzerInterals::stopFuzzer()
{
    int stopFuzzer = 0;

    try
    {
        // TODO: This method should stop the fuzzer
        cout << "Stopping the fuzzer...\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}