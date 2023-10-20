/**
 * @file fuzzerAPI.cpp
 * @author Adrian Goessl
 * @brief This is the implementation of the fuzzerAPI
 * @version 0.1
 * @date 2023-10-20
 * 
 * @copyright MIT 2023
 * 
 */
#include <iostream>
#include <stdexcept>
#include "../src/includes/fuzzerAPI.h"

using namespace std;
using namespace fuzzerAPI;

/// @brief This is the fuzzerAPI method \name FuzzerAPI
void fuzzerAPIInterals::FuzzerAPI() 
{
    try
    {
        // Get the user input, the URL and the data
        cout << "Enter the URL: ";
        

        // read the command-line arguments
        string url;
        cin >> url;

        // send the request
        int result = getRequest(url);

        // build the reqest using create request
        atomizes::HTTPMessage request = createRequest(url, atomizes::MessageMethod::GET);

        // send the request
        result = sendRequest(url, atomizes::MessageMethod::GET);

        // build the request using create request
        request = createRequest(url, atomizes::MessageMethod::POST);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

/// @brief This is the method to create the HTTP request \name createRequest
/// @param url This is the url of the request
/// @param method This is the method of the request
/// @return This method returns the HTTP request, if successful and an empty HTTP request if not successful
atomizes::HTTPMessage fuzzerAPIInterals::createRequest(const std::string& url, const atomizes::MessageMethod method) 
{
    try
    {
        atomizes::HTTPMessage request;
        request.SetMethod(method);
        request.SetPath(url);
        request.SetVersion(atomizes::HTTPVersion11);
        return request;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return atomizes::HTTPMessage();
    }
}

/// @brief This is the method to process the HTTP response \name processResponse
/// @param response This is the HTTP response
/// @return This 
int fuzzerAPIInterals::processResponse(const atomizes::HTTPMessage& response) 
{
    try
    {
        // Process the HTTP response
        // ccess response headers and body using response.GetHeader() and response.GetMessageBody()
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This is the method to send the HTTP request \name sendRequest
/// @param url This is the url of the request
/// @param method This is the method of the request
/// @return This method returns 0 for success and 1 for failure
int fuzzerAPIInterals::sendRequest(const std::string& url, const atomizes::MessageMethod method) 
{
    try 
    {
        // Create an HTTP request
        atomizes::HTTPMessage request = createRequest(url, method);

        // request and get the response 
        // Example: atomizes::HTTPMessage response = sendHTTPRequest(request);
        atomizes::HTTPMessage response;

        // Process the response
        int result = processResponse(response);
        if (result != 0) 
        {
            std::cerr << "Failed to process response" << std::endl;
        }

        return result;
    } 
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

/// @brief This is the method to send a GET request \name getRequest
/// @param url This is the url of the request
/// @return This method returns 0 for success and 1 for failure
int fuzzerAPIInterals::getRequest(const std::string& url) 
{
    return sendRequest(url, atomizes::MessageMethod::GET);
}

/// @brief This is the method to send a POST request \name postRequest
/// @param url This is the url of the request
/// @param data This is the data of the request
/// @return 
int fuzzerAPIInterals::postRequest(const std::string& url, const std::string& data) 
{
    try
    {
        atomizes::HTTPMessage request = createRequest(url, atomizes::MessageMethod::POST);
        request.SetMessageBody(data);
        // add headers if needed with request.SetHeader("Header-Name", "Header-Value");
        return sendRequest(url, atomizes::MessageMethod::POST);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
