#include "convert.hpp"

#include <algorithm>
#include <cctype>

std::string Convert::to_lower(std::string_view value)
{
    std::string result{value};

    std::transform(result.begin(),
                   result.end(),
                   result.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    return result;
}

template <>
bool Convert::to<bool>(std::string_view value)
{
    std::string s = to_lower(value);
    return s == "true" || s == "yes" || s == "on" || s == "1" || s == "y";
}
