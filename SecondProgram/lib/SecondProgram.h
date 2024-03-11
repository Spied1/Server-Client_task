#pragma once
#include "Server.h"

/*
* Class for connecting the server class and checking data with text output.
*/
class SecondProgram
{
private:
    Server reciver;
public:
    SecondProgram();

    void start_program();
    
    bool receive_info();
    
};
