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
#include "../src/includes/macroBase.h"

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
        serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str());
        if (serverAddress.sin_addr.s_addr == INADDR_NONE)
        {
            // Handle the error condition for Windows
            closesocket(clientSocket);
            clientSocket = -1;
            throw std::runtime_error("Invalid address or address not supported");
        }
        #else
        if (inet_pton(AF_INET, ipAddress.c_str(), &(serverAddress.sin_addr)) <= 0) 
        {
            
            // Handle the error condition for non-Windows platforms
            close(clientSocket);
            clientSocket = -1;
            throw std::runtime_error("Invalid address or address not supported");
        }
        #endif


        if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) != 0) 
        {
            #ifdef _WIN32
            int error = WSAGetLastError();
            cerr << "Connection failed with error: " << error << endl;
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
            WSACleanup();
            #else
            close(clientSocket);
            #endif
            clientSocket = -1;
        }
    }
}

/// @brief This is the stop RPC method \name stopRPC
void rpcHubInternals::stopRPC() 
{
    static int clientSocket = -1;

    #ifdef _WIN32
    WSACleanup();
    closesocket(clientSocket);
    #else
    close(clientSocket);
    #endif

    cout << "RPC communication stopped" << endl;
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

/// @brief This is the list services method \name listServices
void rpcHubInternals::listServices() 
{
    cout << "Registered services:" << endl;
    for (const auto& service : registeredServices) 
    {
        cout << service.first << " - " << service.second << endl;
    }
}

/// @brief This is the main connector method, which will be called in main to start the RPC communication \name mainConnector
void rpcHubInternals::mainConnector() 
{
    try 
    {
        string userInput;

        cout << "Enter 'start' to begin RPC communication, 'stop' to stop RPC or 'request' to make a rpc request: ";
        cin >> userInput;

        if(userInput != "start" && userInput != "stop" && userInput != "request")
        {
            throw runtime_error("Invalid input. Please enter 'start', 'stop', 'request'.");
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
        else if(userInput == "request")
        {
            // prepare a request, start the rpc service and send the request with the data
            string ipAddress = "";
            string request = "";
            string methodName = "";
            int port = -1;

            cout << "Enter the method name: ";
            cin >> methodName;

            cout << "Enter the request: ";
            cin >> request;

            vector<string> arguments;

            if (request.empty() || request == "\n") 
            {
                cout << "Request is invalid. Please enter the request again." << endl;
                return;
            }

            arguments.push_back(request);

            if(methodName.empty() || methodName == "\n")
            {
                cout << "Method name is invalid. Please enter the method name again." << endl;
                return;
            }

            string response = sendRpcRequest(methodName, arguments);

            cout << "Response: " << response << endl;
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


/// @brief This is the send RPC request method \name sendRpcRequest
/// @param methodName This is the method name
/// @param arguments This is the arguments
/// @return This is the response
string rpcHubInternals::sendRpcRequest(const string& methodName, const vector<string>& arguments) 
{
    static int clientSocket = -1;

    try 
    {
        if (clientSocket == -1) 
        {
            throw runtime_error("RPC communication is not active.");
        }

        // Send the request
        string request = methodName + " ";
        for (const string& argument : arguments) 
        {
            request += argument + " ";
        }
        request += "\n";

        if (!sendData(clientSocket, request)) 
        {
            throw runtime_error("Failed to send request");
        }

        // Receive the response
        string response = receiveData(clientSocket);
        if (response.empty()) 
        {
            throw runtime_error("Failed to receive response");
        }

        return response;
    } 
    catch (const exception& e) 
    {
        cerr << "Error: " << e.what() << endl;
        return "";
    }
}

/// @brief This is the TCP traffic data analyzer method \name tcpTraficDataAnalyzer
/// @param data This is the data
/// @return This is the analyzed data
vector<std::byte> rpcHubInternals::tcpTraficDataAnalyzer(const string& data) 
{
    vector<std::byte> analyzedData;

    for (const char& character : data) 
    {
        analyzedData.push_back(static_cast<std::byte>(character));
    }

    LOG_STACK_TRACE_WITH_RETURN(analyzedData);

    return analyzedData;
}