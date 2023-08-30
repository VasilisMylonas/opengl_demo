#pragma once

#include <ctime>
#include <ostream>
#include <iomanip>
#include <cstdarg>

class Logger
{
private:
    std::ostream &stream_;

public:
    explicit Logger(std::ostream &stream)
        : stream_{stream}
    {
    }

    void operator()(const char *source, const char *format, ...) const
    {
        std::va_list args;
        va_start(args, format);

        char *message;
        vasprintf(&message, format, args);

        std::time_t time = std::time(NULL);
        std::tm local = *std::localtime(&time);

        stream_ << std::put_time(&local, "%H:%M:%S") << " [" << source << "] " << message << "\n";

        free(message);
        va_end(args);
    }

    ~Logger()
    {
        stream_ << std::flush;
    }
};
