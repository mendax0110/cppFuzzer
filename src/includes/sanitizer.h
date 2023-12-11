/**
 * @file sanitizer.h
 * @author Adrian Goessl
 * @brief Header file for the sanitizer
 * @version 0.1
 * @date 2023-10-05
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include <memory>
#include <filesystem>
#include <cstring>
#include <cstdlib> 
#include <mutex>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>
#include <string.h>
#include <cstring>


#ifndef SANITIZER_H
#define SANITIZER_H

/// @brief The sanitizer namespace \name sanitizer
namespace sanitizer
{
    /// @brief The sanitizerInternals class, which has the public and private members \class sanitizerInternals
    class sanitizerInternals
    {
    public:
        enum class sanitizerType
        {
            addressSanitizer,
            memorySanitizer,
            threadSanitizer,
            undefinedBehaviorSanitizer,
            customSanitizationRule,
            sanizizeLogicAddress,
            sanitizeLogicMemory,
            sanitizeLogicThread,
            sanitizeLogicUndefinedBehavior
        };

        int runSanitizer(sanitizerType sanitizerType, std::string fileName);
        int runAddressSanitizer(std::string fileName);
        int runMemorySanitizer(std::string fileName);
        int runThreadSanitizer(std::string fileName);
        int runUndefinedBehaviorSanitizer(std::string fileName);

        int sanizizeLogicAddress(std::string fileName);
        int sanitizeLogicMemory(std::string fileName);
        int sanitizeLogicThread(std::string fileName);
        int sanitizeLogicUndefinedBehavior(std::string fileName);
        void customSanitizationRule(const std::string& fileName);

        int cleanUp();
    private:
    };
}

#endif // !SANITIZER_H