#include <string>
#include "CommonConstants.h"
#include <algorithm>
#include <numeric>
#include "Utils.h"

namespace utils
{
    /*
    * Validates if all characters in std::string are digits.
    */
    bool is_number(const std::string& text)
    {
        return std::all_of(text.begin(), text.end(), isdigit);
    }

    /*
    * Validates if length of string is <= than 64.
    */
    bool is_length_valid(const std::string& text)
    {
        return text.length() <= constants::length_of_string;
    }

    /*
    * If symbol % 2 == 0 then changes symbol to "KB".
    */
    std::string transform_symbol(char symbol)
    {
        if(symbol % 2 == 0)
        {
            return constants::value_to_replace_even_digits;
        }
        return std::string(1, symbol);
    }

    /*
    * Validates std::string text, if symbol % 2 == 0 then changes it to "KB"
    * in other situation keeps it as it is.
    */
    std::string transform_even_digits(const std::string& text)
    {   
        return std::accumulate(text.begin(), text.end(), std::string{},
            [](std::string result, char symbol)
            {
                return std::move(result) + utils::transform_symbol(symbol);
            });
    }

    /*
    * Counts the sum from the received string from transform_even_digits().
    */
    int get_buffer_sum(const std::string& text)
    {
        return std::accumulate(text.begin(), text.end(), int{},
            [](int sum, char symbol)
            {
                symbol = (symbol == 'K' || symbol == 'B') ? 0 : symbol  - '0';
                return std::move(sum) + (symbol);
            });
    }
}