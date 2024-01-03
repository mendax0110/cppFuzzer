#ifndef RPCHUB_H
#define RPCHUB_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include <cstdint> 
#include <cstring> 
#include <stdexcept>
#include <unordered_map>
#include <signal.h>

#if __cplusplus >= 201703L
#include <filesystem>
#endif

/// @brief The rpcHub namespace \name rpcHub
namespace rpcHub 
{
    /// @brief The rpcHubInternals class, which has the public and private members \class rpcHubInternals
    class rpcHubInternals 
    {
    public:
        rpcHubInternals() 
        {
            
        }

        ~rpcHubInternals() 
        {
            
        }

        void startRPC(const std::string& ipAddress, int port);
        void stopRPC();
        void addService(const std::string& serviceName, const std::string& serviceDescription);
        void removeService(const std::string& serviceName);
        void listServices();
        bool sendData(int socket, const std::string& data);
        void mainConnector();
        std::string receiveData(int socket);
        std::string sendRpcRequest(const std::string& methodName, const std::vector<std::string>& arguments);


    private:
        std::unordered_map<std::string, std::string> registeredServices;

    };
}   // namespace rpcHub

#endif // RPCHUB_H
