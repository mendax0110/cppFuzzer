/**
 * @file hostDeterminator.cpp
 * @author Adrian Goessl
 * @brief This is the implementation of the hostDeterminator
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/hostDeterminator.h"

using namespace std;
using namespace hostDeterminator;

/// @brief This is the get general information method \name getGeneralInformation
/// @return This will return the general information
string hostDeterminatorInternals::getGeneralInformation()
{
    string generalInformation = "General information: \n";

    try 
    {
        envVariables = {
            {"HOSTNAME", "Hostname"},
            {"USER", "Username"},
            {"HOME", "Home directory"},
            {"PWD", "Current working directory"},
            {"OSTYPE", "Operating system"},
            {"NUMBER_OF_PROCESSORS", "Number of CPU cores"},
            {"NUMBER_OF_LOGICAL_PROCESSORS", "Number of logical CPU cores"},
            {"NUMBER_OF_PHYSICAL_PROCESSORS", "Number of physical CPU cores"},
            {"PROCESSOR_ARCHITECTURE", "Processor architecture"},
            {"PROCESSOR_IDENTIFIER", "Processor identifier"},
            {"PROCESSOR_LEVEL", "Processor level"},
            {"PROCESSOR_REVISION", "Processor revision"},
            {"PROCESSOR_TYPE", "Processor type"},
            #ifdef _WIN32
            {"OS", "System version"},
            #else
            {"SYSTEM_VERSION", "System version"},
            #endif
            {"SYSTEM_MANUFACTURER", "System manufacturer"}
        };

        for (auto& envVariable : envVariables)
        {
            for (const auto& entry : envVariables) 
            {
                char* envValue = getenv(entry.first.c_str());
                
                if (envValue != nullptr && printedInfo.find(entry.second) == printedInfo.end()) 
                {
                    generalInformation += entry.second + ": " + string(envValue) + "\n";
                    printedInfo.insert(entry.second);
                }
            }
        }
    } 
    catch (const exception& e) 
    {
        generalInformation += "Exception occurred while fetching information.\n";
        cerr << e.what() << '\n';
    }

    return generalInformation;
}

/// @brief This is the set cpp fuzzer environment method \name setCppFuzzerEnvironment
/// @return This will return 0 if successful, and 1 if not
int hostDeterminatorInternals::setCppFuzzerEnvironment()
{
    try
    {
        #ifdef _WIN32
        string cppFuzzerPath = filesystem::current_path().string() + "\\builds\\cppFuzzer.exe";
        _putenv_s("cppFuzzer", cppFuzzerPath.c_str());
        #else
        string cppFuzzerPath = filesystem::current_path().string() + "/builds/cppFuzzer";
        setenv("cppFuzzer", cppFuzzerPath.c_str(), 1);
        #endif

        char* cppFuzzer = getenv("cppFuzzer");
        if (cppFuzzer == nullptr)
        {
            throw runtime_error("Failed to set cppFuzzer environment variable");
        }

        cout << "cppFuzzer environment variable set to: " << cppFuzzer << endl;

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This is the set server environment method \name setServerEnvironment
/// @return This will return 0 if successful, and 1 if not
int hostDeterminatorInternals::setServerEnvironment()
{
    try
    {
        #ifdef _WIN32
        string serverPath = filesystem::current_path().string() + "\\builds\\server.exe";
        _putenv_s("server", serverPath.c_str());
        #else
        string serverPath = filesystem::current_path().string() + "/builds/server";
        setenv("server", serverPath.c_str(), 1);
        #endif

        char* server = getenv("server");
        if (server == nullptr)
        {
            throw runtime_error("Failed to set server environment variable");
        }

        cout << "server environment variable set to: " << server << endl;

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This is the show general information method \name showGeneralInformation
/// @return This will return 0 if successful, and 1 if not
int hostDeterminatorInternals::showGeneralInformation()
{
    try
    {
        string generalInformation = getGeneralInformation();

        cout << "-------------------------------------------------------------------------\n";
        cout << generalInformation;
        cout << "-------------------------------------------------------------------------\n";

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

