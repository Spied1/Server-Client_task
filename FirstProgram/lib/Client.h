#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include "../../utility/Utils.h"

/*
* Сlass for assembling the client and establishing its connection.
*/
class Client
{
private:
    sockaddr_in server_adress;
    int client_socket;

public:

    void server_set();

    void make_connect();

    bool send_message(const std::string& text) const;

    void close_socket();

    void initialization();

    ~Client();
};

