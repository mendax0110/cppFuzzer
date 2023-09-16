#include <iostream>
#include <cstdlib>
#include <ctime>

#ifndef SETUPFUZZER_H
#define SETUPFUZZER_H


namespace setupFuzzer
{
    class setupFuzzerInternals
    {
    public:

        void setupFuzzer();

        int fuzzerRunning();

    private:

        // TODO: add private members
    };
};

#endif // !CPPPARSER