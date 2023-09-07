#pragma once

#include <string>
#include <string_view>

class Convert
{
public:
    static std::string to_lower(std::string_view value);
    static bool to_bool(std::string_view value);
    static int to_int(std::string_view value);
};

std::string read_file(std::string_view path);
