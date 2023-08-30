#pragma once

#include <ctime>
#include <ostream>
#include <iomanip>
#include <cstdarg>

template <std::ostream &Stream>
class Logger
{
private:
    const char *source_;

public:
    explicit Logger(const char *source) : source_{source}
    {
    }

#define LOG_FUNCTION(function)                   \
    void function(const char *format, ...) const \
    {                                            \
        std::va_list args;                       \
        va_start(args, format);                  \
        (*this)(#function, format, args);        \
        va_end(args);                            \
    }

    LOG_FUNCTION(error)
    LOG_FUNCTION(warn)
    LOG_FUNCTION(info)
    LOG_FUNCTION(debug)
    LOG_FUNCTION(trace)

#undef LOG_FUNCTION

    void operator()(const char *level, const char *format, std::va_list args) const
    {
        char *message;
        vasprintf(&message, format, args);

        std::time_t time = std::time(NULL);
        std::tm local = *std::localtime(&time);

        Stream << std::put_time(&local, "%H:%M:%S") << " [" << source_ << "] (" << level << ") " << message << "\n";

        free(message);
    }

    ~Logger()
    {
        Stream << std::flush;
    }
};
