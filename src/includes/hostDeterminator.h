/**
 * @file hostDeterminator.h
 * @author Adrian Goessl
 * @brief This is the header file for the hostDeterminator
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright MIT 2023
 * 
 */
#ifndef HOSTDETERMINATOR_H
#define HOSTDETERMINATOR_H

#include <iostream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>

namespace hostDeterminator
{
    class hostDeterminatorInternals
    {
    public:
        std::string getGeneralInformation();
        int showGeneralInformation();
        int setCppFuzzerEnvironment();
        int setServerEnvironment();
    private:
        std::unordered_map<std::string, std::string> envVariables;
        std::unordered_set<std::string> printedInfo;

    };
}

#endif // !HOSTDETERMINATOR_H