/**
 * @file pyIPC.cpp
 * @author Adrian Goessl
 * @brief This is the implementation of the pyIPC
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright MIT 2023
 * 
 */
#include "../src/includes/pyIPC.h"

using namespace std;
using namespace pyIPC;

pyIPCInternals::pyIPCInternals()
{
    if (pipe(pipefd) == -1) 
    {
        cerr << "Failed to create pipe" << endl;
    }
}

pyIPCInternals::~pyIPCInternals()
{
    close(pipefd[0]);
    close(pipefd[1]);
}

bool pyIPCInternals::sendMessageToPython(const string& message)
{
    ssize_t bytes_written = write(pipefd[1], message.c_str(), message.size());
    return bytes_written > 0;
}

std::string pyIPCInternals::receiveMessageFromPython()
{
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(pipefd[0], buffer, BUFFER_SIZE);
        
    if (bytes_read > 0)
    {
        return string(buffer, bytes_read);
    }
    
    return "";
}

IPCInterface* pyIPCFactory::createIPCInstance()
{
    return new pyIPCInternals();
}

void pyIPCInternals::usePyIPC()
{
    cout << "Please enter the path to the Python script: ";
    string pythonScriptPath;
    getline(cin, pythonScriptPath);

    if (access(pythonScriptPath.c_str(), F_OK) == -1)
    {
        cerr << "Invalid path to Python script" << endl;
        return;
    }

    string command = "python3 " + pythonScriptPath;
    FILE* file = popen(command.c_str(), "r+");
    
    if (!file)
    {
        cerr << "Failed to open Python process" << endl;
        return;
    }

    IPCInterface* ipcInstance = pyIPCFactory::createIPCInstance();

    if (ipcInstance)
    {
        cout << "IPC instance created successfully." << endl;
        cout << "Please enter a message to send to Python: ";
        string messageToSend;
        getline(cin, messageToSend);

        if (ipcInstance->sendMessageToPython(messageToSend))
        {
            cout << "Message sent successfully." << endl;

            string receivedMessage = ipcInstance->receiveMessageFromPython();
            cout << "Received message from Python: " << receivedMessage << endl;
        }
        else
        {
            cout << "Failed to send message." << endl;
        }

        delete ipcInstance;

    }
    else
    {
        cout << "Failed to create IPC instance." << endl;
    }

    pclose(file);
}
