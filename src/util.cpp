#include "util.hpp"

#include <cctype>
#include <cstdio>
#include <sys/stat.h>

// #include <algorithm>
// std::string Convert::to_lower(std::string_view value)
// {
//     std::string result{value};

//     std::transform(result.begin(),
//                    result.end(),
//                    result.begin(),
//                    [](unsigned char c) { return std::tolower(c); });

//     return result;
// }

// bool Convert::to_bool(std::string_view value)
// {
//     std::string s = to_lower(value);
//     return s == "true" || s == "yes" || s == "on" || s == "1" || s == "y";
// }

// TODO
std::string read_file(const std::string& path)
{
    FILE* f = fopen(path.c_str(), "rb");

    struct stat st;
    fstat(fileno(f), &st);

    std::string contents;
    contents.resize(st.st_size);

    fread(contents.data(), sizeof(char), st.st_size, f);
    fclose(f);

    return contents;
}