/**
 * @file fuzzerAPI.h
 * @author Adrian Goessl
 * @brief This is the header file for the fuzzerAPI, uses https://github.com/tinfoilboy/atomizes
 * @version 0.1
 * @date 2023-10-20
 * 
 * @copyright MIT 2023 
 * 
 */
#ifndef FUZZERAPI_H
#define FUZZERAPI_H

#include <iostream>
#include <string>
#include "atomizes.hpp"

/// @brief This is the namespace for the fuzzerAPI \name fuzzerAPI
namespace fuzzerAPI 
{
    /// @brief This is the class for the fuzzerAPI \name fuzzerAPIInterals
    class fuzzerAPIInterals 
    {
    public:
        void FuzzerAPI();
        int sendRequest(const std::string& url, const atomizes::MessageMethod method);
        int getRequest(const std::string& url);
        int postRequest(const std::string& url, const std::string& data);
        int HttpAdder(std::string& url, const std::string& data);
        void ResultPost(const int postResult, const int choice);

    private:
        atomizes::HTTPMessage createRequest(const std::string& url, const atomizes::MessageMethod method);
        int processResponse(const atomizes::HTTPMessage& response);

    };

}  // namespace fuzzerAPI

#endif // FUZZERAPI_H
