#pragma once

#include <cstdio>
#include <string>
#include <string_view>
#include <sys/stat.h>

// TODO
static std::string read_file(std::string_view path)
{
    std::string path_str{path};

    FILE* f = fopen(path_str.c_str(), "rb");

    struct stat st;
    fstat(fileno(f), &st);

    std::string contents;
    contents.resize(st.st_size);

    fread(contents.data(), sizeof(char), st.st_size, f);
    fclose(f);

    return contents;
}