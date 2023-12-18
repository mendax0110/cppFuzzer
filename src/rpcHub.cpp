/**
 * @file rpcHub.cpp
 * @author Adrian Goessl
 * @brief This is the implementation of the rpcHub
 * @version 0.1
 * @date 2023-12-12
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/rpcHub.h"

using namespace std;
using namespace rpcHub;

/// @brief This is the send data method \name sendData
/// @param socket This is the socket 
/// @param data This is the data
/// @return This will return the bytes sent
bool rpcHubInternals::sendData(int socket, const string& data) 
{
    const char* buffer = data.c_str();
    int bytesSent = send(socket, buffer, data.length(), 0);

    return bytesSent == static_cast<int>(data.length());
}

/// @brief This is the receive data method \name receiveData
/// @param socket This is the socket
/// @return This is the data received
string rpcHubInternals::receiveData(int socket)
{
    const int bufferSize = 1024;
    char buffer[bufferSize];
    int bytesReceived = recv(socket, buffer, bufferSize - 1, 0);

    if (bytesReceived <= 0) 
    {
        return "";
    }
    buffer[bytesReceived] = '\0';

    return string(buffer);
}

/// @brief This is the start RPC method \name startRPC
/// @param ipAddress This is the IP address
/// @param port This is the used port
void rpcHubInternals::startRPC(const string& ipAddress, int port) 
{
    static int clientSocket = -1;

    try 
    {
        if (clientSocket != -1) 
        {
            cout << "RPC communication is already active." << endl;
            return;
        }

        #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
        {
            throw runtime_error("WSAStartup failed");
        }
        #else
        if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) 
        {
            throw runtime_error("Failed to ignore SIGPIPE");
        }
        #endif

        // Create socket
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1) 
        {
            throw runtime_error("Socket creation failed");
        }

        // Connect to the server
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(port);

        #ifdef _WIN32
        // For Windows, use inet_addr to convert IPv4 address
        unsigned long addr = inet_addr(ipAddress.c_str());
        if (addr == INADDR_NONE) 
        {
        #else
        // For non-Windows platforms, use inet_pton
        if (inet_pton(AF_INET, ipAddress.c_str(), &(serverAddress.sin_addr)) <= 0) 
        {
        #endif
            // Handle the error condition
            #ifdef _WIN32
            closesocket(clientSocket);
            #else
            close(clientSocket);
            #endif
            clientSocket = -1;
            throw std::runtime_error("Invalid address or address not supported");
        }

        if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) != 0) 
        {
            #ifdef _WIN32
            closesocket(clientSocket);
            #else
            close(clientSocket);
            #endif
            clientSocket = -1;
            throw runtime_error("Connection failed");
        }

        cout << "Connected to " << ipAddress << " on port " << port << endl;
    } 
    catch (const exception& e) 
    {
        cerr << "Error: " << e.what() << endl;
        if (clientSocket != -1) 
        {
            #ifdef _WIN32
            closesocket(clientSocket);
            #else
            close(clientSocket);
            #endif
            clientSocket = -1;
            #ifdef _WIN32
            WSACleanup();
            #endif
        }
    }
}

/// @brief This is the stop RPC method \name stopRPC
void rpcHubInternals::stopRPC() 
{
    cout << "RPC communication stopped" << endl;

#ifdef _WIN32
    WSACleanup();
#endif
}

/// @brief This is the add service method \name addService
/// @param serviceName This will be the service name
/// @param serviceDescription This is the service description
void rpcHubInternals::addService(const string& serviceName, const string& serviceDescription) 
{
    registeredServices[serviceName] = serviceDescription;
    cout << "Added service: " << serviceName << " - Description: " << serviceDescription << endl;
}

/// @brief This is the remove service method \name removeService
/// @param serviceName This will be the service name
void rpcHubInternals::removeService(const string& serviceName) 
{
    auto it = registeredServices.find(serviceName);

    if (it != registeredServices.end()) 
    {
        registeredServices.erase(it);
        cout << "Removed service: " << serviceName << endl;
    } 
    else 
    {
        cout << "Service " << serviceName << " not found." << endl;
    }
}

/// @brief This is the main connector method, which will be called in main to start the RPC communication \name mainConnector
void rpcHubInternals::mainConnector() 
{
    try 
    {
        string userInput;

        cout << "Enter 'start' to begin RPC communication or 'stop' to stop RPC: ";
        cin >> userInput;

        if(userInput != "start" && userInput != "stop")
        {
            throw runtime_error("Invalid input. Please enter 'start' or 'stop'.");
        }

        if (userInput == "start") 
        {
            cout << "Enter the IP Address: ";
            string ipAddress;
            cin >> ipAddress;

            if (ipAddress.empty() || ipAddress == "\n") 
            {
                cout << "IP Address is invalid. Please enter the IP Address again." << endl;
                return;
            }

            cout << "Enter the port: ";
            int port;
            cin >> port;

            if (port <= 0  || ipAddress == "\n") 
            {
                cout << "Port is invalid. Please enter the port again." << endl;
                return;
            }

            startRPC(ipAddress, port);
        } 
        else if (userInput == "stop") 
        {
            stopRPC();
        } 
        else 
        {
            cout << "Invalid input. Please enter 'start' or 'stop'." << endl;
        }
    } 
    catch (const exception& e) 
    {
        cerr << "Error: " << e.what() << endl;
    }
}

