#pragma once
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../../utility/CommonConstants.h"

/*
* Сlass for assembling the server and establishing its connection to client.
*/
class Server
{
private:
    int server_socket;
    sockaddr_in server_address;
    int client_socket;
    bool connected;
public:
    Server();

    bool create_descriptor();

    void server_set();

    bool bind_to_adress();
    
    bool listen_for_connections();

    bool accept_new_connection();

    std::string read_message();

    void close_socket();

    void initialization();

    bool is_connected() const;

    ~Server();
};
