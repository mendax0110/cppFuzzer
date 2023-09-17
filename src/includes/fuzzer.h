/**
 * @file fuzzer.h
 * @author Adrian Goessl
 * @brief Header file for the fuzzer
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <filesystem>

#ifndef  FUZZER_H
#define  FUZZER_H

/// @brief The fuzzer namespace
namespace cppFuzzer 
{
    /// @brief The cppFuzzerInternals class, which has the public and private members
    class cppFuzzerInternals
    {
    public:

        int fuzzFile(std::string fileName); // TODO: add fuzzedFile as output

        int fuzzString(std::string fileString); // TODO: add fuzzedString as output

        int fuzzFolder(std::string folderName); // TODO: add fuzzedFolder as output

        int cleanup();
            
    private:

        // TODO: add private members

    };
};

#endif // CPPFUZZER_H