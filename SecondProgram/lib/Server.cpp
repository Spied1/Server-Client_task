#include <iostream>
#include <cstring>
#include <unistd.h>
#include "Server.h"


Server::Server()
    : server_socket(0)
    , client_socket(0)
    , connected(false)
{
    connected = create_descriptor();
}

/*
* Creates a descriptor for the server
*/
bool Server::create_descriptor() 
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == constants::error_in_server_client) 
    {   
        return false;
    }

    int reuse = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    return true;
}

/*
* Sets the IP and port for the server
*/
void Server::server_set()
{
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(constants::port);
    server_address.sin_addr.s_addr = INADDR_ANY;
}

/*
* Function binds the address to the socket.
*/
bool Server::bind_to_adress() 
{
    int bind_result = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (bind_result == constants::error_in_server_client) 
    {
        close(server_socket);
        return false;
    }

    return true;   
}

/*
* Function waits for a connection from the client.
* If an error occurs, return false and write an error message.
*/
bool Server::listen_for_connections() 
{
    if (listen(server_socket, 10) == constants::error_in_server_client) 
    {
        std::cerr << "Error when listening on the port" << "\n";
        close(server_socket);
        return false;
    }
    return true;
}

/*
* Function accepts new connections.
* If an error occurs, return false and write an error message.
*/
bool Server::accept_new_connection()
{
    if (client_socket != 0) 
    {
        close(client_socket);
    }

    client_socket = accept(server_socket, nullptr, nullptr);
    if (client_socket == constants::error_in_server_client) 
    {
        int error = errno;
        if (!(error == ECONNABORTED)) 
        {
            close_socket();
        } 
        return false;
    }

    return true;
}

/*
* "The function receives a message. If an error occurs, 
* it writes an error message and resets the buffer. Otherwise, 
* it attempts to establish a new connection or receive a message and returns it."
*/
std::string Server::read_message() 
{
    char buffer[constants::buffer_size];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytesRead = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytesRead == constants::error_in_server_client) 
    {
        std::cerr << "Error while reading data from the socket" << "\n";
        return std::string{};
    } 
    else if (bytesRead == 0) 
    {
        connected = false;
        if (!accept_new_connection()) 
        {
            close_socket();
            return std::string{};
        }
        connected = true;
        return read_message();
    } 
    else 
    {
        std::string temp(buffer);
        return temp;
    }
}

/*
* Closes the sockets, resets the descriptor, and sets the flag to false.
*/
void Server::close_socket() 
{
    close(client_socket);
    close(server_socket);
    client_socket = 0;
    connected = false;
}

/*
* The function initializes the server, sets the 'connected' 
* flag based on create_descriptor(), sets the IP and port, 
* binds to the address, and waits for a connection.
*/
void Server::initialization() 
{
    connected = create_descriptor();
    server_set();
    bind_to_adress();
    listen_for_connections();
    if (accept_new_connection()) 
    {
        connected = true;
    }
}

/*
* Returs connected flag.
*/
bool Server::is_connected() const 
{
    return connected;
}

Server::~Server()
{
    close_socket();
}