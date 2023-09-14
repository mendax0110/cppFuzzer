#include <iostream>
#include "../src/includes/setupFuzzer.h"

using namespace std;
using namespace setupFuzzer;

void setupFuzzerInternals::setupFuzzer()
{
    try
    {
        // setup everything for the fuzzer   

    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
}

