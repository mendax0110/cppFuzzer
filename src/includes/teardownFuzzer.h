/**
 * @file teardownFuzzer.h
 * @author Adrian Goessl
 * @brief Header file for the teardownFuzzer
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
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