#pragma once

#include <ostream>
#include <cstdarg>
#include <string_view>

class Logger
{
private:
    const char *source_;
    std::ostream &stream_;

public:
    Logger(std::ostream &stream, const char *source) : source_{source}, stream_{stream}
    {
    }

    ~Logger()
    {
        stream_ << std::flush;
    }

    void trace(const char *format, ...) const;
    void debug(const char *format, ...) const;
    void info(const char *format, ...) const;
    void warn(const char *format, ...) const;
    void error(const char *format, ...) const;

    void output(std::string_view level, const char *format, std::va_list args) const;
};
