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
#include "../external/Basic-Http-Server-cpp/html_parser.h"
#include "../external/Basic-Http-Server-cpp/main.h"

using namespace std;
using namespace fuzzerAPI;
using namespace html;
using namespace serverHandler;
using namespace atomizes;


/// @brief This is the fuzzerAPI method \name FuzzerAPI
void fuzzerAPIInterals::FuzzerAPI()
{
    try
    {
        int choice;
        int result = -1;
        int postResult = -1;
        string url;
        string postData;

        cout << "Enter 1 for GET and 2 for POST: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the URL for GET request: ";
            cin >> url;

            HttpAdder(url, postData);

            postResult = getRequest(url);

            ResultPost(postResult, choice);

            break;
        case 2:
            cout << "Enter the URL for POST request: ";
            cin >> url;

            HttpAdder(url, postData);

            cout << "Enter the data {\"key\": \"value\"} for POST request: ";
            cin.ignore();
            getline(cin, postData);

            postResult = postRequest(url, postData);

            ResultPost(postResult, choice);

            break;
        }
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
    }
}


/// @brief This is the method to post the result \name ResultPost
/// @param result This is the result of the request
/// @param choice This is the requested operation
void fuzzerAPIInterals::ResultPost(const int result, const int choice)
{
    if(choice == 1)
    {
        if(result == 0)
        {
            cout << "GET Request Response: " << result << endl;
        }
        else
        {
            cerr << "Failed to process GET response." << endl;
        }
    }
    else if(choice == 2)
    {
        if (result == 0)
        {
            cout << "POST Request Response:\n" << result << endl;
        }
        else
        {
            cerr << "Failed to process POST response." << endl;
        }
    }
    else
    {
        cerr << "Invalid choice." << endl;
    }
}

/// @brief This method will add http:// to the URL if it is not present \name HttpAdder
/// @param url This is the url which will be checked
/// @param data This is the data which will be checked
/// @return This method return 0 if the URL is valid and 1 if not
int fuzzerAPIInterals::HttpAdder(std::string& url, const std::string& data)
{
    if(url.empty() || url == "")
    {
        cerr << "URL is required for GET/POST request." << endl;
        return 1;
    }
    else if(url.find("http://") == string::npos && url.find("https://") == string::npos)
    {
        cerr << "Automatically added http:// to the URL." << endl;
        url = "http://" + url;
    }
    else
    {
        cerr << "URL is valid." << endl;
    }

    return 0;
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
        cout << "----------------------------------------------------------\n";
        cout << "StatusMessage: " << request.GetStatusMessage() << endl;
        cout << "StatusCode: " << request.GetStatusCode() << endl;
        cout << "Path: " << request.GetPath() << endl;
        cout << "Version: " << request.GetVersion() << endl;
        cout << "----------------------------------------------------------\n";
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
/// @return This will return 0 if the response was processed successfully and 1 if not
int fuzzerAPIInterals::processResponse(const atomizes::HTTPMessage& response) 
{
    try
    {
        atomizes::HTTPMessageParser parser;
        atomizes::HTTPMessage       request;

        parser.Parse(&request, response.ToString());

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
/// @return This method returns the result of the processResponse method when successful and 1 when not successful
int fuzzerAPIInterals::sendRequest(const std::string& url, const atomizes::MessageMethod method) 
{
    try 
    {
        // Create an HTTP request
        atomizes::HTTPMessage request = createRequest(url, method);

        // request and get the response 
        // Example: atomizes::HTTPMessage response = sendHTTPRequest(request);
        atomizes::HTTPMessage response;
        atomizes::HTTPMessageParser parser;

        parser.Parse(&response, url);

        cout << "GET Request Response: " << response.ToString() << endl;

        // Process the response
        int result = processResponse(response);

        cout << "StatusCode: " << response.GetStatusCode() << endl;
        cout << "StatusMessage: " << response.GetStatusMessage() << endl;

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
/// @return This method returns the sendRequest method when successful and 1 when not successful
int fuzzerAPIInterals::getRequest(const std::string& url) 
{
    try
    {
        atomizes::HTTPMessageParser parser;
        atomizes::HTTPMessage       request;

        parser.Parse(&request, url);

        cout << "GET Request: " << request.ToString() << endl;

        return sendRequest(url, atomizes::MessageMethod::GET);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This is the method to send a POST request \name postRequest
/// @param url This is the url of the request
/// @param data This is the data of the request
/// @return This will return the sendRequest method when successful and 1 when not successful
int fuzzerAPIInterals::postRequest(const std::string& url, const std::string& data) 
{
    try
    {
        atomizes::HTTPMessage request = createRequest(url, atomizes::MessageMethod::POST);
        request.SetMessageBody(data);

        cout << "POST Request" << request.ToString() << endl;
        return sendRequest(url, atomizes::MessageMethod::POST);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
