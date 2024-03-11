#include <iostream>
#include "SecondProgram.h"
#include "../../utility/CommonConstants.h"


SecondProgram::SecondProgram() = default;

/*
* The function for receiving and displaying messages. 
* The function constantly waits for a connection, checks the flag for client connection. 
* If the client is connected, it waits for a message, 
* checks for the fulfillment/non-fulfillment of conditions, and displays the text accordingly.
*/
bool SecondProgram::receive_info() 
{
    while (true) 
    {
        if (!reciver.is_connected()) 
        {
            continue;
        }

        std::string received_message = reciver.read_message();
        if (received_message.empty())
        {
            continue;
        } 

        if(std::stoi(received_message) % 32 == 0 && received_message.length() > 2)
        {    
            std::cout << "Data satisfying the condition has been received: " << received_message << "\n";
            received_message.clear();
        }
        else
        {
            std::cout << "Error: the conditions were not met: " << received_message << "\n";
        }
    }
}

/*
* Initializes the server and waits for information.
*/
void SecondProgram::start_program()
{
    reciver.initialization();
    receive_info();
}
