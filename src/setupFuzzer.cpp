/**
 * @file setupFuzzer.cpp
 * @author Adrian Goessl
 * @brief Setup the fuzzer
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/setupFuzzer.h"

using namespace std;
using namespace setupFuzzer;

/// @brief Setup the fuzzer, \name setupFuzzer
void setupFuzzer::setupFuzzerInternals::setupFuzzer()
{
    try
    {
        // Initialize a random number generator with a seed based on the current time
        srand(static_cast<unsigned>(time(nullptr)));

        cout << "Fuzzer setup completed." << endl;
    }
    catch (const exception& e)
    {
        cerr << "Fuzzer setup failed: " << e.what() << '\n';

        isFuzzerRunning = false;
    }
}

/// @brief Check if the fuzzer is running, \name isRunning
/// @return Fuzzer status
bool setupFuzzer::setupFuzzerInternals::isRunning() const 
{
    return isFuzzerRunning;
}
