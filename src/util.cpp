#include "util.hpp"

#include <cstdio>
#include <sys/stat.h>

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