#include "../src/includes/setupFuzzer.h"

using namespace std;
using namespace setupFuzzer;

/// @brief Setup the fuzzer
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

/// @brief Check if the fuzzer is running
/// @return Fuzzer status
int setupFuzzerInternals::fuzzerRunning()
{
    bool fuzzerRunning = true;

    // TODO: Implement a method to check if the setup was successful/running
    return 1;
}
