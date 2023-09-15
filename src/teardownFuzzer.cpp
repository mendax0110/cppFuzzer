#include <iostream>
#include "../src/includes/teardownFuzzer.h"
#include "../src/includes/main.h"
#include "../src/includes/parser.h"
#include "../src/includes/fuzzer.h"


using namespace std;
using namespace teardownFuzzer;

void teardownFuzzer::teardownFuzzerInterals::teardownFuzzer()
{
    try
    {
        // safley shutdown the cppFuzzer, cppParser and cppMain
        printf("---------------------------------------------\n");
        printf("Shutting down the cppFuzzer!\n");
        printf("---------------------------------------------\n");
        printf("Shutting down the cppParser!\n");
        printf("---------------------------------------------\n");
        printf("Shutting down the cppMain!\n");
        printf("---------------------------------------------\n");

        // shutdown the modules
        cppFuzzer::cppFuzzerInternals fuzzer;
        cppParser::cppParserInternals parser;
        mainFuzzer::cppMainInternals main;

        // shutdown the cppFuzzer
        fuzzer.~cppFuzzerInternals();

        // shutdown the cppParser
        parser.~cppParserInternals();

        // shutdown the cppMain
        main.~cppMainInternals();

        // check the memory, if there are open memory leaks, allocations 
        // or other memory problems
        printf("---------------------------------------------\n");
        printf("Checking the memory!\n");
        printf("---------------------------------------------\n");

        // check the memory
        _CrtDumpMemoryLeaks();
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
}