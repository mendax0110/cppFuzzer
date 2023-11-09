#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <mutex>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <set>
#include <thread>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <condition_variable>

#ifdef __unix__
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#endif

#ifdef _WIN32
#include <winsock2.h>
#endif

#ifdef __APPLE__
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

#include "html_parser.h"

std::mutex QueueLock;
std::condition_variable cv;
std::queue<int> event_queue;
std::mutex DictionaryLock;
std::mutex CoutLock;

class website_handler
{
private:
    std::set<std::string> dictionary;
    std::map<std::string, std::unique_ptr<char[]>> page;

    /// @brief This is the read file method, to read the file \name readFile
    /// @param fileName This is the file name which is to be read
    /// @return This returns the file content
    char *readFile(const char *fileName)
    {
        FILE *file = fopen(fileName, "r");
        if (file == NULL)
        {
            perror("Error opening file");
            return nullptr;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        rewind(file);

        if (fileSize <= 0)
        {
            fclose(file);
            return nullptr;
        }

        char *code = new char[fileSize + 1];
        if (code == nullptr)
        {
            perror("Error allocating memory");
            fclose(file);
            return nullptr;
        }

        size_t bytesRead = fread(code, sizeof(char), fileSize, file);
        if (bytesRead != fileSize)
        {
            perror("Error reading file");
            delete[] code; // Free memory on error
            fclose(file);
            return nullptr;
        }

        code[fileSize] = '\0';

        fclose(file);
        return code;
    }

public:
    website_handler()
    {
    }

    /// @brief This is the load method, to load the file \name load
    /// @param filename 
    /// @return 
    int load(const char *filename)
    {
        if (page.find(filename) != page.end())
        {
            printf("File '%s' is already loaded.\n", filename);
            return 0;
        }

        char *fileContent = readFile(filename);
        if (fileContent == nullptr)
        {
            printf("Error loading file '%s'.\n", filename);
            return 0;
        }

        page[filename] = std::unique_ptr<char[]>(fileContent);
        return 1;
    }

    /// @brief This is the get page method, to get the page \name get_page
    /// @param filename This is the file name, which is to be loaded
    /// @param request_type This is the request type, get => 0 , post => 1 , put=> 2
    /// @param input This is the input string
    /// @param text This is the text string
    /// @return This will return the page
    const char *get_page(const char *filename, int request_type, std::string input, std::string text)
    {
        if (std::filesystem::exists(filename))
        {
            std::string str = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=ISO-8859-1\r\n\r\n" + std::string(page[filename].get());
            if (request_type == 1)
            {
                add_dictionary(text);
            }
            else if (request_type == 0 && !input.empty())
            {
                int is_contains = check_dictionary(input);
                if (is_contains)
                {
                    input += " is found in your Dictionary";
                    size_t pos = str.find("<!Rvalue>");
                    if (pos != std::string::npos)
                    {
                        str.replace(pos, 9, input);
                    }
                }
                else
                {
                    input += " is NOT found in your Dictionary";
                    size_t pos = str.find("<!Rvalue>");
                    if (pos != std::string::npos)
                    {
                        str.replace(pos, 9, input);
                    }
                }
            }

            char *cstr = new char[str.length() + 1];
            strcpy(cstr, str.c_str());
            return cstr;
        }
        else
        {
            std::cerr << filename << " could not be opened! Check if the path is correct\n";
            return "";
        }
    }

    /// @brief This is the add dictionary method, to add the dictionary \name add_dictionary
    /// @param word This is the word, which is to be added
    void add_dictionary(std::string word)
    {
        if (word.empty())
            return;

        DictionaryLock.lock();
        if (dictionary.count(word) == 0)
        {
            dictionary.insert(word);

            int saveResult = saveDataToXMLDatabase("DATABASE.xml");
            if (saveResult == 0)
            {
                std::cout << "Data saved to DATABASE.xml" << std::endl;
            }
            else
            {
                std::cerr << "Failed to save data to DATABASE.xml" << std::endl;
            }

            std::ofstream fDictionary("dictionary.txt", std::ios::app);
            if (fDictionary.good())
            {
                fDictionary << word << "\n";
                fDictionary.close();
            }
            else
            {
                std::cerr << "Failed to open file\n";
            }

            DictionaryLock.unlock();
        }
    }

    /// @brief This is the check dictionary method, to check the dictionary \name check_dictionary
    /// @param word This is the word, which is to be checked
    /// @return This will return the return value
    int check_dictionary(std::string word)
    {
        DictionaryLock.lock();
        int return_value = dictionary.count(word);
        DictionaryLock.unlock();
        return return_value;
    }

    /// @brief This is the init dictionary method, to initialize the dictionary \name init_dictionary
    void init_dictionary()
    {
        DictionaryLock.lock();
        dictionary.insert("");
        std::ifstream fp("dictionary.txt");
        std::ifstream fp2("DATABASE.xml");
        if (!fp.good() && fp2.good())
        {
            std::ofstream created("dictionary.txt");
            std::ofstream created2("DATABASE.xml");
            created.close();
            created2.close();
            fp.close();
            fp2.close();
            DictionaryLock.unlock();
            return;
        }

        std::string word;
        char c;
        while ((c = fp.get()) != EOF && (c = fp2.get()) != EOF)
        {
            if (c == '\n')
            {
                dictionary.insert(word);
                word.clear();
            }
            else
                word.push_back(c);
        }

        if (!word.empty())
            dictionary.insert(word);
        fp.close();
        fp2.close();
        DictionaryLock.unlock();
    }

    /// @brief This is the save data to XML database method, to save the data to XML database \name saveDataToXMLDatabase
    /// @param filename This is the file name, which is to be saved
    /// @return This will 0 if the data is saved, and 1 if the data is not saved
    int saveDataToXMLDatabase(const std::string &filename)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            int entryNumber = 1;
            file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
            file << "<Database>" << std::endl;

            for (const std::string &item : dictionary)
            {
                if (!item.empty() && !std::all_of(item.begin(), item.end(), ::isspace))
                {
                    file << "  <Entry_" << entryNumber << ">" << item << "</Entry_" << entryNumber << ">" << std::endl;
                    entryNumber++;
                }
            }

            file << "</Database>" << std::endl;
            file.close();
            return 0;
        }
        else
        {
            std::cerr << "Error opening file for saving data." << std::endl;
            return 1;
        }
    }

    /// @brief This is the load data from XML database method, to load the data from XML database \name loadDataFromXMLDatabase
    /// @param filename This is the file name, which is to be loaded
    /// @return This will 0 if the data is loaded, and 1 if the data is not loaded
    int loadDataFromXMLDatabase(const std::string &filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::string line;

            while (std::getline(file, line))
            {
                if (line.find("<Entry_") != std::string::npos &&
                    line.find("</Entry_") != std::string::npos)
                {
                    std::string word = line.substr(line.find("<Entry_") + 7, line.find("</Entry_") - 7);
                    dictionary.insert(word);
                }
            }

            file.close();
            return 0;
        }
        else
        {
            std::cerr << "Error opening file for loading data." << std::endl;
            return 1;
        }
    }
};

website_handler website;
website_handler API;

class server
{
private:
    int file_descriptor;
    int sizeof_address;
    int THREAD_COUNT;
    struct sockaddr_in address;
    int server_up;

    /// @brief This is the new socket method, to create a new socket \name new_socket
    /// @return This will return 0 if the socket is created, and -1 if the socket is not created
    int new_socket()
    {
        file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
        if (file_descriptor < 0)
        {
            perror("ERROR: Invalid Socket");
            return -1;
        }
        return 0;
    }

    /// @brief This is the bind address method, to bind the address \name bind_address
    /// @return This will return 0 if the address is binded, and -1 if the address is not binded
    int bind_address()
    {
        int return_value = bind(file_descriptor, (struct sockaddr *)&address, sizeof(address));
        if (return_value < 0)
        {
            perror("ERROR: Couldn't bind");
            return -1;
        }
        return 0;
    }

    /// @brief This is the start listen method, to start listening \name start_listen
    /// @param k This is the number of connections
    /// @return This will return 0 if the listening is started, and -1 if the listening is not started
    int start_listen(int k = 100000)
    {
        int return_value = listen(file_descriptor, k);
        if (return_value < 0)
        {
            perror("ERROR: Couldn't listen");
            return -1;
        }
        return 0;
    }

    /// @brief This is the accept connection method, to accept the connection \name accept_connection
    int accept_connection()
    {
        #if defined(__unix__) || defined(__APPLE__)
        int connection_value = accept(file_descriptor, (struct sockaddr *)&address, (socklen_t *)&sizeof_address);
        #else
        int connection_value = accept(file_descriptor, (struct sockaddr *)&address, &sizeof_address);
        #endif
        if (connection_value < 0)
        {
            perror("ERROR: Connection Accept Failure");
            return -1;
        }
        return connection_value;
    }

public:
    /// @brief This is the constructor for the server \name server
    /// @param internet_address This is the internet address, which is to be used
    /// @param port_number This is the port number, which is to be used
    /// @param THREAD_COUNT This is the thread count, which is to be used
    server(int internet_address, int port_number = 80, int THREAD_COUNT = 10)
    {
        this->THREAD_COUNT = THREAD_COUNT;
        server_up = 0;
        sizeof_address = sizeof(address);
        address.sin_family = AF_INET;
        if (internet_address == 0)
            address.sin_addr.s_addr = INADDR_ANY;
        else
            address.sin_addr.s_addr = internet_address;
        address.sin_port = htons(port_number);
        memset(address.sin_zero, '\0', sizeof address.sin_zero);

        if (new_socket() == -1)
            return;
        if (bind_address() == -1)
            return;
        if (start_listen() == -1)
            return;
        server_up = 1;
    }

    /// @brief This is the destructor for the server \name ~server
    ~server()
    {
        shutdown(file_descriptor, 2);
    }

    /// @brief This is the connection thread method, to create a connection thread \name connection_thread
    /// @param argv This is the argument
    /// @return This will return NULL
    static void *connection_thread(void *argv)
    {
        while (true)
        {
            int socket_num = -1;
            {
                std::unique_lock<std::mutex> lock(QueueLock);
                cv.wait(lock, [] { return !event_queue.empty(); });
                socket_num = event_queue.front();
                event_queue.pop();
            }

            char buffer[1000] = {0};

            memset(buffer, 0, 1000);
            int buffer_length = recv(socket_num, buffer, 1000, 0);
            if (buffer_length < 0)
            {
                perror("ERROR: Receiving Failure");
                #ifdef __win32__
                closesocket(socket_num);
                #else
                close(socket_num);
                #endif
                continue;
            }

            html::html_parser request(buffer, buffer_length);
            const char *message = website.get_page("main.html", request.get_request_type(), request.get_input("name"), request.get_text());

            int length = strlen(message);
            int send_value = send(socket_num, message, length, 0);
            if (send_value < 0)
            {
                perror("ERROR: Sending Failure");
            }
            
            #ifdef __win32__
            closesocket(socket_num);
            #else
            close(socket_num);
            #endif
        }
    }

    /// @brief This is the start method, to start the server \name start
    void start()
    {
        if (server_up == 0)
        {
            std::cerr << "Server failed to start!\n";
            return;
        }

        std::vector<std::thread> ptid;
        for (int i = 0; i < THREAD_COUNT; i++)
        {
            ptid.push_back(std::thread(connection_thread, (void *)NULL));
        }

        while (1)
        {
            int socket_num = accept_connection();
            {
                std::lock_guard<std::mutex> lock(QueueLock);
                event_queue.push(socket_num);
            }
            cv.notify_one();
        }
    }
};

/// @brief This is the main function \name main, this will be used to run the server
/// @param argc This is the argument count
/// @param argv This is the argument
/// @return This will return 0 if the server is started, and 1 if the server is not started
int main(int argc, char **argv)
{
    #ifdef _WIN32
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);
    #endif

    website.init_dictionary();
    website.load("main.html");
    server basic_server(0, 80, 10);
    basic_server.start();

    return 0;
}
