#include <iostream>
#include "../src/includes/teardownFuzzer.h"

using namespace std;
using namespace teardownFuzzer;

void teardownFuzzer::teardownFuzzerInterals::teardownFuzzer()
{
    try
    {
        /* code */
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
    }
}