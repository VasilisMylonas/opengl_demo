#pragma once

#include <string>
#include <string_view>

// TODO: remove
class Convert
{
public:
    static std::string to_lower(std::string_view value);
    static bool to_bool(std::string_view value);
};

std::string read_file(const std::string& path);
