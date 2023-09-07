#pragma once

#include <cstdarg>
#include <ostream>
#include <string_view>

class Logger
{
private:
    std::string_view source_;
    std::ostream& stream_;

public:
    Logger(std::ostream& stream, std::string_view source);
    ~Logger();
    Logger(Logger&& other);
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    // TODO: move assignment

    void trace(const char* format, ...) const;
    void debug(const char* format, ...) const;
    void info(const char* format, ...) const;
    void warn(const char* format, ...) const;
    void error(const char* format, ...) const;

    void output(std::string_view level, const char* format, std::va_list args) const;
};
