/**
 * @file testWebservice.cpp
 * @author Adrian Goessl
 * @brief This is the test to test the webservice
 * @version 0.1
 * @date 2023-11-24
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include "../external/Basic-Http-Server-cpp/html_parser.h"
#include "../external/Basic-Http-Server-cpp/main.h"

using namespace std;
using namespace html;
using namespace serverHandler;

/// @brief This is the method to set the findExecutablePath, \name findExecutablePath
string FindExecutablePath()
{
    return "../cppFuzzer/build/server";
}

int RunExternalProcess(const vector<char*>& args)
{
    int exitCode = 0;

    return exitCode;
}

int testWebservice()
{
    //serverHandler::website_handler websiteHandler;
    server server(0, 8080, 10);
    server.start();

    // ping 127.0.0.1
    string commandline = "ping 127.0.0.1";

    try
    {
        // put the string into commandline
        system(commandline.c_str());
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

int main()
{
    if(testWebservice() == 0)
    {
        cout << "Test passed" << endl;
    }
    else
    {
        cout << "Test failed" << endl;
    }
}


