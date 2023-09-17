/**
 * @file setupFuzzer.h
 * @author Adrian Goessl
 * @brief Header file for the setupFuzzer
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifndef SETUPFUZZER_H
#define SETUPFUZZER_H

/// @brief The setupFuzzer namespace
namespace setupFuzzer
{
    /// @brief The setupFuzzerInternals class, which has the public and private members
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