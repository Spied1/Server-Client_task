#pragma once

/*
* Constants for program operation. If the socket is occupied by another program,
* it is advisable to change the port
*/
namespace constants
{
    constexpr auto length_of_string{64};
    constexpr auto port{8888};
    constexpr auto buffer_size{1024};
    constexpr auto value_to_replace_even_digits{"KB"};
    constexpr auto error_in_server_client{-1};
}
