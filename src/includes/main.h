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