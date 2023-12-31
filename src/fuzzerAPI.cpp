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
using namespace rpcHub;


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
        //serverHandler::website_handler& website = serverHandler::website_handler::get_instance();

        cout << "Enter 1 for GET and 2 for POST: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the URL for GET request: ";
            cin >> url;

            HttpAdder(url, postData);

            postResult = getRequest(url);
            resultPost(postResult, choice);

            break;
        case 2:
            cout << "Enter the URL for POST request: ";
            cin >> url;

            HttpAdder(url, postData);

            cout << "Enter the data {\"key\": \"value\"} for POST request: ";
            cin.ignore();
            getline(cin, postData);

            postResult = postRequest(url, postData);
            resultPost(postResult, choice);

            break;
        case 3:
            //fuzzerAPIInterals::handleCommands();
            break;
        }
    }
    catch (const exception& e)
    {
        cerr << e.what() << '\n';
    }
}


/// @brief This is the method to post the result \name resultPost
/// @param result This is the result of the request
/// @param choice This is the requested operation
void fuzzerAPIInterals::resultPost(const int result, const int choice)
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

/// @brief This is the method to post the result \name resultGet
/// @param result This is the result of the request
/// @param choice This is the requested operation
void fuzzerAPIInterals::resultGet(const int result, const int choice)
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
int fuzzerAPIInterals::HttpAdder(string& url, const string& data)
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
atomizes::HTTPMessage fuzzerAPIInterals::createRequest(const string& url, const atomizes::MessageMethod method) 
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
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
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
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This is the method to send the HTTP request \name sendRequest
/// @param url This is the url of the request
/// @param method This is the method of the request
/// @return This method returns the result of the processResponse method when successful and 1 when not successful
int fuzzerAPIInterals::sendRequest(const string& url, const atomizes::MessageMethod method) 
{
    try 
    {
        // Create an HTTP request
        atomizes::HTTPMessage request = createRequest(url, method);

        // request and get the response 
        atomizes::HTTPMessage response;
        atomizes::HTTPMessageParser parser;

        parser.Parse(&response, url);

        cout << "GET Request Response: " << response.ToString() << endl;

        // Process the response
        int result = processResponse(response);

        if (result != 0) 
        {
            cerr << "Failed to process response" << endl;
            return 1;
        }

        cout << "StatusCode: " << response.GetStatusCode() << endl;
        cout << "StatusMessage: " << response.GetStatusMessage() << endl;

        return result;
    } 
    catch (const exception& e) 
    {
        cerr << e.what() << endl;
        return 1;
    }
}

/// @brief This is the method to send a GET request \name getRequest
/// @param url This is the url of the request
/// @return This method returns the sendRequest method when successful and 1 when not successful
int fuzzerAPIInterals::getRequest(const string& url) 
{
    try
    {
        atomizes::HTTPMessageParser parser;
        atomizes::HTTPMessage       request;

        parser.Parse(&request, url);

        cout << "GET Request: " << request.ToString() << endl;

        return sendRequest(url, atomizes::MessageMethod::GET);
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}

/// @brief This is the method to send a POST request \name postRequest
/// @param url This is the url of the request
/// @param data This is the data of the request
/// @return This will return the sendRequest method when successful and 1 when not successful
int fuzzerAPIInterals::postRequest(const string& url, const string& data) 
{
    try
    {
        atomizes::HTTPMessage request = createRequest(url, atomizes::MessageMethod::POST);
        request.SetMessageBody(data);

        cout << "POST Request" << request.ToString() << endl;

        return sendRequest(url, atomizes::MessageMethod::POST);
    }
    catch(const exception& e)
    {
        cerr << e.what() << '\n';
        return 1;
    }
}

/*void fuzzerAPIInterals::handleCommands() 
{
    serverHandler::website_handler& website = serverHandler::website_handler::get_instance();
    string command;

    while (true) 
    {
        cout << "Enter a command ('add <word>', 'search <word>', 'exit'): ";
        getline(cin, command);

        istringstream iss(command);
        vector<string> tokens{ istream_iterator<string>{iss},
                                         istream_iterator<string>{} };

        if (tokens.empty())
        {
            cout << "Invalid command. Please try again.\n";
            continue;
        }

        if (tokens[0] == "add" && tokens.size() == 2)
        {
            website.add_dictionary(tokens[1]);
            cout << tokens[1] << " added to the dictionary.\n";
        }
        else if (tokens[0] == "search" && tokens.size() == 2)
        {
            int is_found = website.check_dictionary(tokens[1]);
            if (is_found)
            {
                cout << tokens[1] << " is found in the dictionary.\n";
            }
            else
            {
                cout << tokens[1] << " is NOT found in the dictionary.\n";
            }
        }
        else if (tokens[0] == "exit")
        {
            break;
        } 
        else
        {
            cout << "Invalid command. Please try again.\n";
        }
    }
}*/

/// @brief This is the method to connect to the RPC service \name rpcConnector
/// @param url This is the url of the RPC service
/// @param data This is the data of the RPC service
/// @param choice This is the choice of the RPC service
/// @return This will return 0 for success and 1 for failure
int fuzzerAPIInterals::rpcConnector(const string& url, const string& data, const int& choice)
{
    try
    {
        rpcHub::rpcHubInternals rpcHub;

        if(choice == 1)
        {
            rpcHub.addService(url, data);
        }
        else if(choice == 2)
        {
            rpcHub.removeService(url);
        }
        else if(choice == 3)
        {
            rpcHub.listServices();
        }
        else
        {
            cerr << "Invalid service." << endl;
        }

        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}