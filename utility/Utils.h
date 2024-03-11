#pragma once
#include <string>
#include "CommonConstants.h"

/*
* Implemented functions for program's operation.
*/
namespace utils
{
    bool is_number(const std::string& text);

    bool is_length_valid(const std::string& text);

    std::string transform_symbol(char symbol);

    std::string transform_even_digits(const std::string& text);

    int get_buffer_sum(const std::string& text);
}


