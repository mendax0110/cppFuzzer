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
std::queue<int> event_queue;
std::mutex DictionaryLock;
std::mutex CoutLock;

/// @brief This is the class for the website_handler \name website_handler
class website_handler
{
private:
    std::set<std::string> dictionary;
    std::map<std::string, char *> page;

    /// @brief This is the method to read a file \name readFile
    /// @param fileName This is the name of the file to be read
    /// @return This is the contents of the file, or NULL if failed
    char *readFile(const char *fileName) 
    {
        FILE *file = fopen(fileName, "r");
        if (file == NULL) 
        {
            perror("Error opening file");
            return NULL;
        }

        // Calculate the file size for dynamic memory allocation
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        rewind(file);

        // Check for an empty file
        if (fileSize <= 0) 
        {
            fclose(file);
            return NULL;
        }

        char *code = (char *)malloc(fileSize + 1); // +1 for null terminator
        if (code == NULL) 
        {
            perror("Error allocating memory");
            fclose(file);
            return NULL;
        }

        size_t bytesRead = fread(code, sizeof(char), fileSize, file);
        if (bytesRead != fileSize) 
        {
            perror("Error reading file");
            free(code);
            fclose(file);
            return NULL;
        }

        code[fileSize] = '\0'; // Null-terminate the string

        fclose(file);
        return code;
    }

public:
    website_handler()
    {
    }

    /// @brief This is the method to load a file \name load
    /// @param filename This is the name of the file to be loaded
    /// @return This will return 0 for success and 1 for failure
    int load(const char *filename) 
    {
        // Check if the file is already loaded
        if (page.find(filename) != page.end()) 
        {
            printf("File '%s' is already loaded.\n", filename);
            return 0;
        }

        char *fileContent = readFile(filename);
        if (fileContent == NULL) 
        {
            printf("Error loading file '%s'.\n", filename);
            return 0;
        }

        page[filename] = fileContent;
        return 1;
    }

    /// @brief This is the method to get a page \name get_page
    /// @param filename This is the name of the file to be loaded
    /// @param request_type This is the type of request
    /// @param input This is the input to be added to the dictionary
    /// @param text This is the text to be checked in the dictionary
    /// @return This will return the page
    const char *get_page(const char *filename, int request_type, std::string input, std::string text)
    {
        if (std::fstream(filename).fail())
        {
            std::cerr << filename << " could not be opened! Check if the path is correct\n";
            return "";
        }

        std::string str = "HTTP/1.1 200 Okay\r\nContent-Type: text/html; charset=ISO-8859-4 \r\n\r\n" + std::string(page[filename]);
        if (request_type == 1)
        {
            add_dictionary(text);
        }
        else if (request_type == 0 && input != "")
        {
            int is_contains = check_dictionary(input);
            if (is_contains)
            {
                input += " is found in your Dictionary";
                str.replace(str.find("<!Rvalue>"), 9, input.c_str());
            }
            else
            {
                input += " is NOT found in your Dictionary";
                str.replace(str.find("<!Rvalue>"), 9, input.c_str());
            }
        }

        char *cstr = new char[str.length() + 1];
        strcpy(cstr, str.c_str());
        return cstr;
    }

    /// @brief This is the method to add a word to the dictionary \name add_dictionary
    /// @param word This is the word to be added to the dictionary
    void add_dictionary(std::string word)
    {
        if (word.empty())
            return;
        DictionaryLock.lock();
        if (dictionary.count(word) == 0)
        {
            std::ofstream fDictionary("dictionary.txt", std::ios::app);
            if (!fDictionary.good())
            {
                std::cerr << "Failed to open file\n";
                fDictionary.close();
            }

            fDictionary << word.c_str() << "\n";
            fDictionary.close();
            dictionary.insert(word);
        }

        DictionaryLock.unlock();
    }

    /// @brief This is the method to check if a word is in the dictionary \name check_dictionary
    /// @param word This is the word to be checked in the dictionary
    /// @return This is the return value of the method
    int check_dictionary(std::string word)
    {
        DictionaryLock.lock();
        int return_value = dictionary.count(word);
        DictionaryLock.unlock();
        return return_value;
    }

    /// @brief This is the method to initialize the dictionary \name init_dictionary
    void init_dictionary()
    {
        DictionaryLock.lock();
        dictionary.insert("");
        std::ifstream fp("dictionary.txt");
        if (!fp.good())
        {
            std::ofstream created("dictionary.txt");
            created.close();
            fp.close();
            DictionaryLock.unlock();
            return;
        }

        std::string word;
        char c;
        while ((c = fp.get()) != EOF)
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
        DictionaryLock.unlock();
    }

    // Method to save data to a text file
    int saveDataToFile(const std::string& filename) 
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (const std::string& item : dictionary) 
            {
                file << item << '\n';
            }
            file.close();
            return 0; // Success
        } 
        else 
        {
            std::cerr << "Error opening file for saving data." << std::endl;
            return 1; // Failure
        }
    }

    // Method to load data from a text file
    int loadDataFromFile(const std::string& filename) 
    {
        std::ifstream file(filename);
        if (file.is_open()) 
        {
            dictionary.clear(); // Clear the current dictionary
            std::string line;
            while (std::getline(file, line)) 
            {
                dictionary.insert(line);
            }
            file.close();
            return 0; // Success
        } 
        else 
        {
            std::cerr << "Error opening file for loading data." << std::endl;
            return 1; // Failure
        }
    }
};

website_handler website;

/// @brief This is the class for the server \name server
class server
{
private:
    int file_descriptor;
    int sizeof_address;
    int THREAD_COUNT;
    struct sockaddr_in address;
    int server_up;

    /// @brief This is the method to create a new socket \name new_socket
    /// @return This will return 0 for success and -1 for failure
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

    /// @brief  This is the method to bind the address \name bind_address
    /// @return This will return 0 for success and -1 for failure
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

    /// @brief This is the method to start listening \name start_listen
    /// @param k This is the number of connections to be listened to
    /// @return This will return 0 for success and -1 for failure
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

    /// @brief This is the method to accept a connection \name accept_connection
    /// @return This will return the connection value if successful and -1 for failure
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
    /// @param internet_address This is the internet address
    /// @param port_number This is the port number
    /// @param THREAD_COUNT This is the number of threads
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

    ~server()
    {
        shutdown(file_descriptor, 2);
    }

    /// @brief This is the method to create a new thread \name connection_thread
    /// @param argv This is the argument to the thread
    /// @return This will return NULL if failed, else it will return the thread
    static void *connection_thread(void *argv)
    {
        while (true)
        {
            int socket_num;
            QueueLock.lock();
            if (!event_queue.empty())
            {
                socket_num = event_queue.front();
                event_queue.pop();
                QueueLock.unlock();
            }
            else
            {
                QueueLock.unlock();
                continue;
            }

            char buffer[1000] = {0};

            memset(buffer, 0, 1000);
            int buffer_length = recv(socket_num, buffer, 1000, 0);
            if (buffer_length < 0)
            {
                perror("ERROR: Receiving Failure");
                return NULL;
            }

            html::html_parser request(buffer, buffer_length);
            const char *message = website.get_page("main.html", request.get_request_type(), request.get_input("name"), request.get_text());

            int length = strlen(message);
            int send_value = send(socket_num, message, length, 0);
            if (send_value < 0)
            {
                perror("ERROR: Sending Failure");
                return NULL;
            }
		#if defined(__unix__) || defined(__APPLE__)
            close(socket_num);
		#else
			closesocket(socket_num);
		#endif
        }
    }

    /// @brief This is the method to start the server \name start
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
            QueueLock.lock();
            event_queue.push(socket_num);
            QueueLock.unlock();
        }
    }
};

/// @brief This is the main function \name main
/// @param argc This is the number of command-line arguments
/// @param argv This is an array of command-line arguments
/// @return This will return 0 for success and 1 for failure
int main(int argc, char **argv)
{
    // Get the current working directory
    const std::filesystem::path homeDir = std::getenv("HOME");

    // Specify the relative path to DATABASE.txt
    const std::string relativePath = "cppFuzzer/external/Basic-Http-Server-cpp/DATABASE.txt";

    // Combine the current directory and relative path to create the absolute path
    std::filesystem::path absolutePath = homeDir / relativePath;

    // Convert the absolute path to a string
    const std::string databaseFilePath = absolutePath.string();

    // Save and load data using the absolute path
    website.saveDataToFile(databaseFilePath);
    website.loadDataFromFile(databaseFilePath);

    // The rest of your code remains the same
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
