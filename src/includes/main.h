/**
 * @file main.h
 * @author Adrian Goessl
 * @brief  Header file for the main fuzzer
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include <cstring>

#ifndef MAINFUZZER_H
#define MAINFUZZER_H

/// @brief The main fuzzer namespace \name mainFuzzer
namespace mainFuzzer
{
    /// @brief The cppMainInternals class, which has the public and private members \class cppMainInternals
    class cppMainInternals
    {
    public:
        int cleanup();
        cppMainInternals() : fileHandle(nullptr), dynamicArray(nullptr) {} // Initialize in the constructor
        
    private:
        FILE* fileHandle; // Define fileHandle
        int* dynamicArray; // Define dynamicArray
    };
};

#endif // !CPPMAIN