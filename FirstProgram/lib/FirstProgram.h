#pragma once
#include <mutex>
#include <atomic>
#include "Client.h"

/*
* The first program's class is used for assembling, receiving, and checking text,
* and connecting the client class with server.
*/
class FirstProgram
{
private:
    int sum_of_nums; 
    std::string buffer_of_program;
    std::atomic<bool> is_clear;
    std::mutex mutex;
    Client first_client;
public:
    FirstProgram();

    void first_thread();

    void send_message();

    void second_thread();

    void thread_start();
};