#include <cstring>
#include <unistd.h>
#include "Client.h"
#include "../../utility/CommonConstants.h"

/*
* Configures the client's socket and server address.
*/
void Client::server_set()
    {
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(constants::port);
    server_adress.sin_addr.s_addr = INADDR_ANY;
    }

/*
* Connects to the server using the specified address and port 
* in the server_set().
*/
void Client::make_connect() 
{
    if (client_socket == constants::error_in_server_client) 
    {
        return;
    }

    if (connect(client_socket, (struct sockaddr*)&server_adress, sizeof(server_adress)) == constants::error_in_server_client) 
    {
        close_socket();
    }
}

/*
* The function takes a std::string and, upon receiving it, 
* sends it to the server.
*/
bool Client::send_message(const std::string& text) const
{
    if (client_socket == constants::error_in_server_client) 
    {
        return false;
    }   

    const char* message = text.c_str();
    return client_socket != constants::error_in_server_client && send(client_socket, message, strlen(text.c_str()), 0) != constants::error_in_server_client;
}

/*
* The function is used to disconnect the client socket.
*/
void Client::close_socket() 
{
    if (client_socket != constants::error_in_server_client) 
    {
        close(client_socket);
        client_socket = constants::error_in_server_client;
    }
}

/*
* The function performs three steps.
* Disconnects sockets in case their creation was unsuccessful.
* Sets the port and IP.
* Connects to the server.
*/
void Client::initialization() 
{
    close_socket();
    server_set();
    make_connect();
}

Client::~Client()
{
    close_socket();
}
