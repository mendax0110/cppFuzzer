/**
 * @file pyIPC.h
 * @author Adrian Goessl
 * @brief This is the header file for the pyIPC
 * @version 0.1
 * @date 2024-01-03
 * @copyright MIT 2023
 */
#ifndef PYIPC_H
#define PYIPC_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#ifdef _WIN32
#include <io.h>
#include <process.h>
#include <fcntl.h>
#include <sys/types.h>
#include <Windows.h>
#else
#include <unistd.h>
#endif

/// @brief The pyIPC namespace \name pyIPC
namespace pyIPC
{
    /// @brief The IPCInterface class, which has the public and private members \class IPCInterface
    class IPCInterface 
    {
    public:
        virtual ~IPCInterface() {}
        virtual bool sendMessageToPython(const std::string& message) = 0;
        virtual std::string receiveMessageFromPython() = 0;
    };

    /// @brief This is the pyIPCInternals class, which derives from the IPCInterface class \class pyIPCInternals
    class pyIPCInternals : public IPCInterface
    {
    public:
        pyIPCInternals();
        ~pyIPCInternals() override;

        bool sendMessageToPython(const std::string& message) override;
        std::string receiveMessageFromPython() override;
        void usePyIPC();

    private:
        int pipefd[2]; // Declare pipefd as a private member
    };

    /// @brief This is the pyIPCFactory class, which has the public and private members \class pyIPCFactory
    class pyIPCFactory
    {
    public:
        static IPCInterface* createIPCInstance();
    };

} // namespace pyIPC

#endif // PYIPC_H
