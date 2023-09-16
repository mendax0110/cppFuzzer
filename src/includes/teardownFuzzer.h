#include <iostream>

#ifndef TEARDOWNFUZZER_H
#define TEARDOWNFUZZER_H

namespace teardownFuzzer
{
    class teardownFuzzerInterals
    {
    public:

        void teardownFuzzer();

        void stopFuzzer();

        int cleanup();

    private:

        // TODO: add private members
    };
};

#endif // !CPPPARSER