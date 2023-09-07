#include "logger.hpp"

#include <ctime>
#include <iomanip>

void Logger::output(std::string_view level, const char* format, std::va_list args) const
{
    char* message;
    vasprintf(&message, format, args);

    std::time_t time = std::time(NULL);
    std::tm local = *std::localtime(&time);

    stream_ << std::put_time(&local, "%H:%M:%S") << " [" << source_ << "] (" << level << ") "
            << message << "\n";

    free(message);
}

#define LOG_FUNCTION(function)                                                                     \
    void Logger::function(const char* format, ...) const                                           \
    {                                                                                              \
        std::va_list args;                                                                         \
        va_start(args, format);                                                                    \
        output(#function, format, args);                                                           \
        va_end(args);                                                                              \
    }

LOG_FUNCTION(error)
LOG_FUNCTION(warn)
LOG_FUNCTION(info)
LOG_FUNCTION(debug)
LOG_FUNCTION(trace)

#undef LOG_FUNCTION

Logger::Logger(std::ostream& stream, std::string_view source) : source_{source}, stream_{stream}
{
}

Logger::~Logger()
{
    stream_ << std::flush;
}

Logger::Logger(Logger&& other) : source_{std::move(other.source_)}, stream_{other.stream_}
{
}
