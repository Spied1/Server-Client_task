#include <algorithm>
#include <thread>
#include <iostream>
#include "FirstProgram.h"
#include "../../utility/Utils.h"


FirstProgram::FirstProgram()
    : sum_of_nums(0)
    , buffer_of_program("")
    , is_clear(false)
{}

/*
* The first thread continuously waits for data, 
* checks if it contains only numbers and has a length less than 64.
* If true, it sorts the text, applies utils::transform_even_digits(), 
* and saves the data into a mutex-protected buffer.
*/
void FirstProgram::first_thread() 
{
    while(true)
    {
        if(is_clear)
        {
            continue;
        }
        std::string text;
        std::cin >> text;
        if(utils::is_number(text) && utils::is_length_valid(text))
        {
            std::sort(text.rbegin(), text.rend());
            std::lock_guard<std::mutex> lock(mutex);
            buffer_of_program += utils::transform_even_digits(text);
            is_clear = true;
        }   
    }
}

/*
* Consists of three steps, sends a message through send_message(). 
* After sending, initializes the server, resets the buffer, 
* and sets a flag indicating that the buffer has been cleared.
*/
void FirstProgram::send_message()
{
    first_client.send_message(std::to_string(sum_of_nums));
    first_client.initialization();
    buffer_of_program = "0";
    is_clear = false;
}

/*
* The second thread, upon noticing that the buffer is not empty,
* calculates the sum of all numbers excluding 'KB' and sends a message to the server.
*/
void FirstProgram::second_thread() 
{
    send_message();
    while(true)
    {
        sum_of_nums = 0;
        if(!is_clear)
        {
            continue;
        }
        std::lock_guard<std::mutex> lock(mutex);
        sum_of_nums = utils::get_buffer_sum(buffer_of_program);
        std::cout << "The data of the buffer: " << buffer_of_program.substr(1) << " current sum: " << sum_of_nums << "\n";
        send_message();
    }
}

/*
* Using lambda functions, call the functions of Thread 1 and Thread 2.
*/
void FirstProgram::thread_start() 
{
    auto lambda_of_first = [this]()
    {
        first_thread();
    };
    auto lambda_of_second = [this]()
    {
        second_thread();
    };
        
    std::thread thread1(lambda_of_first);
    std::thread thread2(lambda_of_second);
    thread1.join();
    thread2.join();
}