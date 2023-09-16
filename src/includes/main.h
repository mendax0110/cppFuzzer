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

#ifndef MAINFUZZER_H
#define MAINFUZZER_H

namespace mainFuzzer
{
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