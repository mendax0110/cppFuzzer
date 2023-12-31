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

/// @brief The setupFuzzer namespace \name setupFuzzer
namespace setupFuzzer
{
    /// @brief The setupFuzzerInternals class, which has the public and private members \class setupFuzzerInternals
    class setupFuzzerInternals
    {
    public:
        void setupFuzzer();
        int fuzzerRunning();
        bool isRunning() const;

    private:
        bool isFuzzerRunning = true;
    };
};

#endif // !CPPPARSER