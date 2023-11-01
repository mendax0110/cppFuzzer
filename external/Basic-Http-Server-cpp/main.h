#ifndef MAIN_H
#define MAIN_H

#include <string>

namespace serverHandler
{
    class website_handler
    {
    public:
        website_handler();
        int load(const char *filename);
        const char *get_page(const char *filename, int request_type, std::string input, std::string text);
        void add_dictionary(std::string word);
        int check_dictionary(std::string word);
        void init_dictionary();
    };

    class server
    {
    public:
        server(int internet_address, int port_number = 80, int THREAD_COUNT = 10);
        ~server();
        void start();

    private:
        int new_socket();
        int bind_address();
        int start_listen(int k = 100000);
        int accept_connection();

        static void *connection_thread(void *argv);
    };
};
#endif // MAIN_H



