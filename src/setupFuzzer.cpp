#include "../src/includes/setupFuzzer.h"

using namespace std;
using namespace setupFuzzer;


void setupFuzzerInternals::setupFuzzer()
{
    try
    {
        // Initialize a random number generator with a seed based on the current time
        srand(static_cast<unsigned>(time(nullptr)));

        cout << "Fuzzer setup completed." << endl;
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
    }
}
