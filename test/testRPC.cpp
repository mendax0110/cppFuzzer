/**
 * @file testRPC.cpp
 * @author Adrian Goessl
 * @brief Simple test for the RPC
 * @version 0.1
 * @date 2023-12-12
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include "../src/includes/rpcHub.h"

using namespace std;
using namespace rpcHub;


/// @brief The testStartRPC function \name testStartRPC, this will be used to test the RPC
/// @return This will return 0 if the test passed, 1 if the test failed
int testStartRPC()
{
    string ipAddress = "";
    int port = 0;

    try
    {
        rpcHubInternals rpc;
        rpc.startRPC(ipAddress, port);

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief The testSendData function \name testSendData, this will be used to test the RPC
/// @return This will return 0 if the test passed, 1 if the test failed
int testSendData()
{
    int socket = 0;
    string data = "";
    try
    {
        rpcHubInternals rpc;
        rpc.sendData(socket, data);

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief The testReceiveData function \name testReceiveData, this will be used to test the RPC
/// @return This will return 0 if the test passed, 1 if the test failed
int testReceiveData()
{
    int socket = 0;
    try
    {
        rpcHubInternals rpc;
        rpc.receiveData(socket);

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief The testStopRPC function \name testStopRPC, this will be used to test the RPC
/// @return This will return 0 if the test passed, 1 if the test failed
int testStopRPC()
{
    try
    {
        rpcHubInternals rpc;
        rpc.stopRPC();

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief The testAddService function \name testAddService, this will be used to test the RPC
/// @return This will return 0 if the test passed, 1 if the test failed
int testAddService()
{
    string serviceName = "";
    string serviceDescription = "";
    int servicePort = 0;
    try
    {
        rpcHubInternals rpc;
        rpc.addService(serviceName, serviceDescription);

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief The testRemoveService function \name testRemoveService, this will be used to test the RPC
/// @return This will return 0 if the test passed, 1 if the test failed
int testRemoveService()
{
    string serviceName = "";
    try
    {
        rpcHubInternals rpc;
        rpc.removeService(serviceName);

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief The main function \name main, this will be used to run the tests
/// @return This will return 0 if the test passed, 1 if the test failed
int main()
{
    int result = 0;

    result += testStartRPC();
    result += testSendData();
    result += testReceiveData();
    result += testAddService();
    result += testRemoveService();
    result += testStopRPC();

    if (result == 0)
    {
        cout << "All tests passed." << endl;
        return 0;
    }
    else
    {
        cerr << "One or more tests failed." << endl;
        return 1;
    }
}
