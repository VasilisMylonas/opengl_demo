#include "logger.hpp"

#include <ctime>
#include <iomanip>
#include <cstdarg>

static void output(std::ostream &stream, const char *source, const char *level, const char *format, std::va_list args)
{
    char *message;
    vasprintf(&message, format, args);

    std::time_t time = std::time(NULL);
    std::tm local = *std::localtime(&time);

    stream << std::put_time(&local, "%H:%M:%S") << " [" << source << "] (" << level << ") " << message << "\n";

    free(message);
}

#define LOG_FUNCTION(function)                             \
    void Logger::function(const char *format, ...) const   \
    {                                                      \
        std::va_list args;                                 \
        va_start(args, format);                            \
        output(stream_, source_, #function, format, args); \
        va_end(args);                                      \
    }

LOG_FUNCTION(error)
LOG_FUNCTION(warn)
LOG_FUNCTION(info)
LOG_FUNCTION(debug)
LOG_FUNCTION(trace)

#undef LOG_FUNCTION
