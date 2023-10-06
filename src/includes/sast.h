/**
 * @file sast.h
 * @author Adrian Goessl
 * @brief Header file for the static analyzer
 * @version 0.1
 * @date 2023-10-05
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <regex>
#include <memory>
#include <cstring>
#include <cstdlib> 
#include <mutex>
#include <thread>
#include <sstream>
#include <stdexcept>

#ifndef SAST_H
#define SAST_H

/// @brief The sast namespace \name sast
namespace sast
{
    /// @brief The sastInternals class, which has the public and private members \class sastInternals
    class sastInternals
    {
    public:
        int runSast(std::string fileName);
        int cleanUp();

    private:
    };
};

#endif // !SAST_H