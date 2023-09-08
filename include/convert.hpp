#pragma once

#include <string>
#include <string_view>

class Convert
{
public:
    static std::string to_lower(std::string_view value);

    template <typename T>
    static T to(std::string_view value)
    {
        std::size_t pos;
        return std::stoi(std::string{value}, &pos, 0);
    }
};
