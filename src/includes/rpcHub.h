#ifndef RPCHUB_H
#define RPCHUB_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
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

#if __cplusplus >= 201703L
#include <filesystem>
#else
#include <experimental/filesystem>
#endif

namespace rpcHub 
{
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
        bool sendData(int socket, const std::string& data);
        void mainConnector();
        std::string receiveData(int socket);
        std::string sendRequest(const std::string& methodName, const std::vector<std::string>& arguments);


    private:
        std::unordered_map<std::string, std::string> registeredServices;

    };
}   // namespace rpcHub

#endif // RPCHUB_H
