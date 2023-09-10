#include "logger.hpp"

#include <cassert>
#include <ctime>
#include <iomanip>

std::string_view Logger::level_to_str(Level level)
{
    switch (level)
    {
    case Level::TRACE:
        return "TRACE";
    case Level::DEBUG:
        return "DEBUG";
    case Level::INFO:
        return "INFO";
    case Level::WARN:
        return "WARN";
    case Level::ERROR:
        return "ERROR";
    }

    assert(false);
}

void Logger::log(Level level, const char* format, std::va_list args) const
{
    if (level < level_)
    {
        return;
    }

    char* message;
    vasprintf(&message, format, args);

    std::time_t time = std::time(NULL);
    std::tm local = *std::localtime(&time);

    *stream_ << std::put_time(&local, "%H:%M:%S") << " [" << source_ << "] (" << level_to_str(level)
             << ") " << message << "\n";

    free(message);
}

void Logger::trace(const char* format, ...) const
{
    std::va_list args;
    va_start(args, format);
    log(Level::TRACE, format, args);
    va_end(args);
}

void Logger::debug(const char* format, ...) const
{
    std::va_list args;
    va_start(args, format);
    log(Level::DEBUG, format, args);
    va_end(args);
}

void Logger::info(const char* format, ...) const
{
    std::va_list args;
    va_start(args, format);
    log(Level::INFO, format, args);
    va_end(args);
}

void Logger::warn(const char* format, ...) const
{
    std::va_list args;
    va_start(args, format);
    log(Level::WARN, format, args);
    va_end(args);
}

void Logger::error(const char* format, ...) const
{
    std::va_list args;
    va_start(args, format);
    log(Level::ERROR, format, args);
    va_end(args);
}

Logger::Logger(std::ostream& stream, std::string_view source, Level level)
    : source_{source}, stream_{&stream}, level_{level}
{
}

Logger::~Logger()
{
    *stream_ << std::flush;
}

Logger::Logger(Logger&& other)
    : source_{std::move(other.source_)}, stream_{other.stream_}, level_{other.level_}
{
}

Logger& Logger::operator=(Logger&& other)
{
    source_ = std::move(other.source_);
    stream_ = other.stream_;
    level_ = other.level_;
    return *this;
}

void Logger::set_level(Level level)
{
    level_ = level;
}

Logger::Level Logger::level() const
{
    return level_;
}